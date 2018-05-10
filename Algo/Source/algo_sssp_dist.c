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

//------------------------------------------------------------------------------
// GraphBLAS/Demos/sr_dist.c: bellman-ford for floats
//------------------------------------------------------------------------------

// Adaptation of Fineman, Jeremy T., and Eric Robinson.
// "Fundamental graph algorithms."
// Graph Algorithms in the Language of Linear Algebra 22 (2011): 45.

#include "algo_sssp_dist.h"
#include "sr_dist.h"

#undef OK
#define OK(method)                                          \
{                                                           \
    info = method;                                         \
    if (! (info == GrB_SUCCESS || info == GrB_NO_VALUE))    \
    {                                                       \
        printf ("file %s line %d\n", __FILE__, __LINE__);  \
        printf ("%s\n", GrB_error ( ));                    \
        FREE_ALL;                                          \
        FREE_INNER;                                        \
        return (info);                                     \
    }                                                       \
}

#undef FREE_ALL
#define FREE_ALL     \
    GrB_free (&A);  \
    GrB_free (&d);


#undef FREE_INNER
#define FREE_INNER

//------------------------------------------------------------------------------
// sr_dist: Bellman-Ford for floats
//------------------------------------------------------------------------------

GrB_Info algo_sssp_dist               // compute SSSP for source
(
    const GrB_Matrix A_in,      // adjacency matrix (IN/OUT)
    GrB_Index source,           // index of source vertex (IN)
    GrB_Vector* p_d,            // vector loaded w/ result (OUT)
    bool* p_no_neg_cycle        // negative cycle (OUT)
)
{
    GrB_Info info;
    bool DEBUG = false;

    // Dist_init();
    // TODO How to ensure Path has been initialized?

    GrB_Matrix A = GrB_NULL;
    GrB_Vector d = GrB_NULL;

    // n = # of nodes in graph
    GrB_Index n;
    GrB_Matrix_nrows (&n, A_in);

    // Some semiring constants ...
    // Does graphBLAS provide these? It should.
    // since it depends on C11 Spec should mention INFINITY? TODO
    float FloatMinPlusSr_ONE = 0.0;
    float FloatMinPlusSr_ZERO = INFINITY;

    // construct a new adjacency matrix from input adjacency matrix
    // note implicit change of sparsity from 0.0 to INFINITY
    // also, set self loop distance to 0.0
    OK (GrB_Matrix_new (&A, GrB_FP32, n, n));

    {
#undef FREE_INNER
#define FREE_INNER                  \
                GrB_free (&Diag);  \
                GrB_free (&desc);
        GrB_Matrix Diag = GrB_NULL;
        GrB_Descriptor desc = GrB_NULL;

        OK( GrB_Matrix_new (&Diag, GrB_FP32, n, n) );
        for (int64_t i = 0; i < n; i++)
            GrB_Matrix_setElement (Diag, FloatMinPlusSr_ONE, i, i);

        OK( GrB_Descriptor_new (&desc) );
        OK( GrB_Descriptor_set (desc, GrB_INP1, GrB_TRAN) );
        OK( GrB_eWiseAdd (A, GrB_NULL, GrB_NULL, GrB_FIRST_FP32, Diag, A_in, desc));

        OK(GrB_free (&Diag));
        OK(GrB_free (&desc));
#undef FREE_INNER
    }
    if (DEBUG) sr_dist_print_matrix (A, "A+diag");

    // Now that Adjacency matrix is all set,
    // use designated source (input), to initialize vector
    {
        GrB_Vector_new (&d, GrB_FP32, n);
        GrB_Vector_setElement (d, FloatMinPlusSr_ONE, source);
    }
    if (DEBUG) sr_dist_print_vector(d, "d_init");

    // iterate
    {
        for( GrB_Index i = 0; i < n; i += 1 ) {
            GrB_mxv (d, GrB_NULL, GrB_NULL, Dist_min_plus, A, d, GrB_NULL);
            if (DEBUG) sr_dist_print_vector(d, "d_next");
        }
    }


    // check for negative weight cycle
    bool no_neg_cycle = true;
    {
#undef FREE_INNER
#define FREE_INNER                     \
                GrB_free (&d_check);   \
                GrB_free (&d_eq);
        GrB_Vector d_check = GrB_NULL;
        GrB_Vector d_eq = GrB_NULL;

        OK(GrB_Vector_new (&d_check, GrB_FP32, n));
        // one more iteration
        OK(GrB_mxv (d_check, GrB_NULL, GrB_NULL, Dist_min_plus, A, d, GrB_NULL));
        if (DEBUG) sr_dist_print_vector(d_check, "d_check");

        // compare the two results
        // shouldn't spec contain an easy more efficient way to test
        // equivalence of two vectors (or matrices)? TODO
        OK(GrB_Vector_new (&d_eq, GrB_BOOL, n));
        OK(GrB_eWiseAdd (d_eq, GrB_NULL, GrB_NULL, GrB_EQ_FP32, d, d_check, GrB_NULL));

        OK(GrB_reduce (&no_neg_cycle, GrB_NULL, dist_LAND_BOOL, d_eq, GrB_NULL));

        if (DEBUG) {
            if ( no_neg_cycle) printf ("no neg cycle\n");
            else printf("neg cycle\n");
        }

        OK(GrB_free (&d_check));
        OK(GrB_free (&d_eq));
#undef FREE_INNER
    }
    *p_no_neg_cycle = no_neg_cycle;

    // return result
    *p_d = d;

    return (GrB_SUCCESS);
}

