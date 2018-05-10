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

#ifndef GRB_VECTOR_T_H
#define GRB_VECTOR_T_H

struct GrB_Vector_t
{
private:

    GrB_Type                    _D;
    GrB_Index                   _size;
    uset<GrB_Index>             *_ind;
    umap<GrB_Index,void*>       *_map;
    bool                        _valid;

public:

    GrB_Vector_t();
    GrB_Vector_t(const GrB_Vector_t&);
    ~GrB_Vector_t();
    GrB_Vector_t(GrB_Type,GrB_Index);

    bool                  valid() const;                        // object is valid
    GrB_Index             nvals() const;                        // number of elements (nonzeros)
    GrB_Type              D() const;                            // type of elements
    GrB_Index             size() const;                         // size of vector
    const uset<GrB_Index> *ind() const;                         // set of element indices (structure)
    const umap<GrB_Index,void*> *map() const;                   // map of indices to elements
    Scalar                operator[](GrB_Index) const;          // element access (read-only)
    bool                  init(GrB_Type,GrB_Index);             // initialize vector
    bool                  copy(const GrB_Vector_t&);            // copy from another vector
    bool                  clear();                              // clear all elements
    bool                  clear(GrB_Index);                     // clear element at index
    void                  addElement(GrB_Index,const Scalar&);  // add element to vector
    void                  addElement(GrB_Index,const Scalar&,const GrB_BinaryOp_t&);      // add element with accumulation
    bool                  add(const GrB_BinaryOp_t*,const GrB_Vector_t&,const GrB_Vector_t&); // element-wise addition
    bool                  add(const GrB_Monoid_t*  ,const GrB_Vector_t&,const GrB_Vector_t&); // element-wise addition
    bool                  add(const GrB_Semiring_t*,const GrB_Vector_t&,const GrB_Vector_t&); // element-wise addition
    bool                  mul(const GrB_BinaryOp_t*,const GrB_Vector_t&,const GrB_Vector_t&); // element-wise multiplication
    bool                  mul(const GrB_Monoid_t*  ,const GrB_Vector_t&,const GrB_Vector_t&); // element-wise multiplication
    bool                  mul(const GrB_Semiring_t*,const GrB_Vector_t&,const GrB_Vector_t&); // element-wise multiplication
    bool                  replace(const GrB_mask_t&,const GrB_Vector_t&);                 // replace with another vector
    bool                  merge(const GrB_mask_t&,const GrB_Vector_t&);                   // merge with another vector
    void                  axB(const GrB_Semiring,const GrB_Vector_t&,const GrB_Matrix_t&);// vector-matrix multiplication
    void                  Axb(const GrB_Semiring,const GrB_Matrix_t&,const GrB_Vector_t&);// matrix-vector multiplication
};

#endif // GRB_VECTOR_T_H
