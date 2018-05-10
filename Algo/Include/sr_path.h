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

#ifndef ALGO_SR_PATH_H
#define ALGO_SR_PATH_H
#include "GraphBLAS.h"
#include <math.h>  // for INFINITY
#include <stdlib.h> // for malloc/free
#include <stdio.h>  // for print stuff

void sr_path_print_matrix (GrB_Matrix A, char *name);
void sr_path_print_vector (GrB_Vector v, char *name);

GrB_Info Path_init ( );
GrB_Info Path_finalize ( );

typedef struct path {
    float      distance;
    GrB_Index  hops;
    GrB_Index  penultimate;
} path;

extern GrB_Type Path;
extern GrB_BinaryOp Path_min, Path_plus;
extern GrB_Monoid   Path_min_monoid;
extern GrB_Monoid   Path_plus_monoid;
extern GrB_Semiring Path_min_plus;
extern GrB_BinaryOp Path_eq;

extern const path PathMinPlusSr_ONE;
extern const path PathMinPlusSr_ZERO;
extern const GrB_Index PathNodeNil;
#endif

