/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <GraphBLAS.h>
#include "gtest/gtest.h"

namespace {

class GrBt_Operations: public ::testing::Test {
    protected:
    // Any of the following functions can be removed if its body is empty
    GrBt_Operations() {
        // Do set-up work for each test here.
    }

    virtual ~GrBt_Operations() {
        // Do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test then define the following methods:

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for this class.
    static double vectors_dot_prod(const double *x, const double *y, int n)
    {
        double res = 0.0;
        int i;
        for (i = 0; i < n; i++)
        {
            res += x[i] * y[i];
        }
        return res;
    }

    static void matrix_vector_mult(const double **mat, const double *vec,
            double *result, int rows, int cols) { // in matrix form: result = mat * vec;
        int i;
        for (i = 0; i < rows; i++) {
            result[i] = vectors_dot_prod(mat[i], vec, cols);
        }
    }
};
// Tests that the Foo::Bar() method does Abc.
TEST_F(GrBt_Operations, mTv) {
    ASSERT_EQ(GrB_init (GrB_NONBLOCKING), GrB_SUCCESS);
    const GrB_Index nv = 3;

    // ****
    // setup test matricies
    GrB_Index r;
    GrB_Index c;

    int **mv = (int **) malloc(nv * sizeof(int*));
    for (r = 0; r < nv; r++) {
        mv[r] = (int *) malloc(nv * sizeof(int));
    }
    for (r = 0; r < nv; r++) {
        for (c = 0; c < nv; c++) {
            int32_t val = c * nv + r;
            mv[r][c] = val;
        }
    }


    // GrB Matrix
    GrB_Matrix m;
    ASSERT_EQ(GrB_Matrix_new (&m, GrB_INT32, nv, nv), GrB_SUCCESS);
    for (r = 0; r < nv; r++) {
        for (c = 0; c < nv; c++) {
            int32_t val = mv[r][c];
            ASSERT_EQ(GrB_Matrix_setElement_INT32(m, val, r, c), GrB_SUCCESS);
        }
    }
    //  check test matrix assignments
    for (r = 0; r < nv; r++) {
        for (c = 0; c < nv; c++) {
            int32_t eval;
            ASSERT_EQ(GrB_Matrix_extractElement_INT32(&eval, m, r, c), GrB_SUCCESS);
            ASSERT_EQ(eval, mv[r][c]);
        }
    }

    // ****
    // setup test vectors
//    int *v = (int *) malloc(nv * sizeof(int));
    // GrB Vector
    GrB_Vector v;
    ASSERT_EQ(GrB_Vector_new (&v, GrB_INT32, nv), GrB_SUCCESS);
    for (r = 0; r < nv; r++) {
        int32_t val = r;
        ASSERT_EQ(GrB_Vector_setElement_INT32(v, val, r), GrB_SUCCESS);
    }
    //  check vector assignments
    for (r = 0; r < nv; r++) {
        int32_t eval;
        ASSERT_EQ(GrB_Vector_extractElement_INT32(&eval, v, r), GrB_SUCCESS);
    }

    // set up semiring
    GrB_Monoid f;
    ASSERT_EQ(GrB_Monoid_new_INT32(&f, GrB_PLUS_INT32, 0), GrB_SUCCESS);
    GrB_Semiring sr;
    ASSERT_EQ(GrB_Semiring_new(&sr, f, GrB_TIMES_INT32), GrB_SUCCESS);

    // descriptor
    GrB_Descriptor desc;
    ASSERT_EQ(GrB_Descriptor_new (&desc), GrB_SUCCESS);
    ASSERT_EQ(GrB_Descriptor_set (desc, GrB_OUTP, GrB_REPLACE), GrB_SUCCESS);
//    ASSERT_EQ(GrB_Descriptor_set (desc, GrB_MASK, GrB_SCMP), GrB_SUCCESS);
//    ASSERT_EQ(GrB_Descriptor_set (desc, GrB_INP0, GrB_TRAN), GrB_SUCCESS);

    // target vector
    GrB_Vector u;
    ASSERT_EQ(GrB_Vector_new (&u, GrB_INT32, nv), GrB_SUCCESS);

    // multiplication
    ASSERT_EQ(GrB_mxv (u, (const GrB_Vector)GrB_NULL, (const GrB_BinaryOp)GrB_NULL, sr, m, v, desc), GrB_SUCCESS);

    // result
    static int32_t ua[3] = {15, 18, 21};
    //  check result
    for (r = 0; r < nv; r++) {
        int32_t eval;
        ASSERT_EQ(GrB_Vector_extractElement_INT32(&eval, u, r), GrB_SUCCESS);
        EXPECT_EQ(ua[r], eval);
    }

    // ****
    // set up semiring using polymorphic interface
    GrB_Monoid fPoly;
    ASSERT_EQ(GrB_Monoid_new(&fPoly, GrB_PLUS_INT32, 0), GrB_SUCCESS);
    GrB_Semiring srPoly;
    ASSERT_EQ(GrB_Semiring_new(&srPoly, fPoly, GrB_TIMES_INT32), GrB_SUCCESS);
    // multiplication
    ASSERT_EQ(GrB_mxv (u, (const GrB_Vector)GrB_NULL, (const GrB_BinaryOp)GrB_NULL, sr, m, v, desc), GrB_SUCCESS);
    //  check result
    for (r = 0; r < nv; r++) {
        int32_t eval;
        ASSERT_EQ(GrB_Vector_extractElement_INT32(&eval, u, r), GrB_SUCCESS);
        EXPECT_EQ(ua[r], eval);
    }

//    const std::string input_filepath = "this/package/testdata/myinputfile.dat";
//    const std::string output_filepath = "this/package/testdata/myoutputfile.dat";
//    Foo f;
//    EXPECT_EQ(0, f.Bar(input_filepath, output_filepath));
//    EXPECT_EQ(0, 0);
}

//// Tests that Foo does Xyz.
//TEST_F(GrBt_Operations, DoesXyz) {
//    // Exercises the Xyz feature of Foo.
//}

} // namespace
//test("LagSmpContext.mTv") {
//  val nv = 3
//  val hc: LagContext = LagContext.getLagSmpContext(nv)
//  val sparseValueInt = 0
//  val mv = Vector.tabulate(nv, nv)((r, c) => c * nv + r)
//  val m = hc.mFromMap(LagContext.mapFromSeqOfSeq(mv, sparseValueInt), sparseValueInt)
//  val v = hc.vFromSeq(Range(0, nv).toVector, sparseValueInt)
//  //    object add_mul extends LagSemiring[Int] {
//  //      override val addition = (x: Int, y: Int) => x + y
//  //      val multiplication = (x: Int, y: Int) => x * y
//  //      val zero = 0
//  //      val one = 1
//  //    }
//  val add_mul = LagSemiring.plus_times[Int]
//  val u = hc.mTv(add_mul, m, v)
//  val ua = Vector(15, 18, 21)
//  assert(ua.corresponds(hc.vToVector(u))(_ == _))
//}

