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

#ifndef GRB_MASK_T_H
#define GRB_MASK_T_H

struct GrB_mask_t
{
private:

    GrB_Index           _size;
    uset<GrB_Index>     *_ind;

public:

   GrB_mask_t(bool, const GrB_Vector_t*, const GrB_Vector_t&);
    ~GrB_mask_t();

    GrB_Index                   size() const;
    const uset<GrB_Index>       *ind() const;
};

struct GrB_Mask_t
{
private:

    GrB_Index           _nrows;
    GrB_Index           _ncols;
    vector<GrB_mask_t*> _rows;
    vector<GrB_mask_t*> _cols;

public:

    GrB_Mask_t(bool, const GrB_Matrix, const GrB_Matrix_t&);
    ~GrB_Mask_t();

    GrB_Index           nrows() const;
    GrB_Index           ncols() const;
    const GrB_mask_t&   operator[](GrB_Index) const;
    const GrB_mask_t&   operator()(GrB_Index) const;
};

#endif // GRB_MASK_T_H
