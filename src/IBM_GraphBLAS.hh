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

#ifndef IBM_GRAPHBLAS_H
#define IBM_GRAPHBLAS_H

#include <GraphBLAS.h>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <utility>
#include <assert.h>

#define uset std::unordered_set
#define umap std::unordered_map
#define vector std::vector

void uset_intersection(uset<GrB_Index>&, const uset<GrB_Index>&, const uset<GrB_Index>&);
void uset_union       (uset<GrB_Index>&, const uset<GrB_Index>&, const uset<GrB_Index>&);
void uset_difference  (uset<GrB_Index>&, const uset<GrB_Index>&, const uset<GrB_Index>&);
uset<GrB_Index> operator*(const uset<GrB_Index>&  , const uset<GrB_Index>&  );
uset<GrB_Index> operator*(const vector<GrB_Index>&, const uset<GrB_Index>&  );
uset<GrB_Index> operator*(const uset<GrB_Index>&  , const vector<GrB_Index>&);
uset<GrB_Index> operator-(const uset<GrB_Index>&  , const uset<GrB_Index>&  );
uset<GrB_Index> operator+(const uset<GrB_Index>&  , const uset<GrB_Index>&  );

#include "Exception.hh"
#include "Scalar.hh"
#include "GrB_Mask_t.hh"
#include "GrB_Vector_t.hh"
#include "GrB_Matrix_t.hh"
#include "GrB_Monoid_t.hh"
#include "GrB_Semiring_t.hh"
#include "GrB_UnaryOp_t.hh"
#include "GrB_BinaryOp_t.hh"
#include "GrB_Descriptor_t.hh"
#include "GrB_Type_t.hh"

#endif // IBM_GRAPHBLAS_H
