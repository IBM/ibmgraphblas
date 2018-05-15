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

#ifndef GRB_MATRIX_T_H
#define GRB_MATRIX_T_H

struct GrB_Matrix_t
{
private:

    GrB_Type                    _D;
    GrB_Index                   _nrows;
    GrB_Index                   _ncols;
    GrB_Index                   _nvals;
    vector<GrB_Vector>          _rows;
    vector<GrB_Vector>          _cols;
    bool                        _valid;
    bool			_copy;

public:

    GrB_Matrix_t();
    GrB_Matrix_t(const GrB_Matrix_t&);
    ~GrB_Matrix_t();
    GrB_Matrix_t(GrB_Type,GrB_Index,GrB_Index);
    GrB_Matrix_t(bool, const GrB_Matrix_t&);

    bool                valid() const;                          // object is valid
    GrB_Type            D() const;                              // type of elements
    GrB_Index           nrows() const;                          // number of rows of matrix
    GrB_Index           ncols() const;                          // number of columns of matrix
    GrB_Index           nvals() const;                          // number of elements (nonzeros)
    bool                copy(const GrB_Matrix_t&);              // copy from another matrix
    bool                init(GrB_Type,GrB_Index,GrB_Index);     // initialize matrix
    bool                transpose(const GrB_Matrix_t&);         // transpose matrix
    bool                clear();                                // clear all elements
    bool                clear(GrB_Index,GrB_Index);             // clear element at row,column indices
    const GrB_Vector_t& operator[](GrB_Index) const;            // row of matrix (read-only)
    const GrB_Vector_t& operator()(GrB_Index) const;            // column of matrix (read-only)
    void                AxB(const GrB_Semiring,const GrB_Matrix_t&,const GrB_Matrix_t&);     // matrix multiplication
    bool                add(const GrB_BinaryOp_t*,const GrB_Matrix_t&,const GrB_Matrix_t&);  // element-wise addition
    bool                add(const GrB_Monoid_t*  ,const GrB_Matrix_t&,const GrB_Matrix_t&);  // element-wise addition
    bool                add(const GrB_Semiring_t*,const GrB_Matrix_t&,const GrB_Matrix_t&);  // element-wise addition
    bool                mul(const GrB_BinaryOp_t*,const GrB_Matrix_t&,const GrB_Matrix_t&);  // element-wise multiply
    bool                mul(const GrB_Monoid_t*  ,const GrB_Matrix_t&,const GrB_Matrix_t&);  // element-wise multiply
    bool                mul(const GrB_Semiring_t*,const GrB_Matrix_t&,const GrB_Matrix_t&);  // element-wise multiply
    bool                replace(const GrB_Mask_t&,const GrB_Matrix_t&);                      // replace with new matrix
    bool                merge(const GrB_Mask_t&,const GrB_Matrix_t&);                        // merge with new matrix
    void                addElement(GrB_Index,GrB_Index,const Scalar&);                       // add element to matrix
    void                addElement(GrB_Index,GrB_Index,const Scalar&,const GrB_BinaryOp_t&); // add element with accumulation
};

#endif // GRB_MATRIX_T_H
