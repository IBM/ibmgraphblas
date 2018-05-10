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

#ifndef ALGO_SR_DIST_H
#define ALGO_SR_DIST_H
#include "GraphBLAS.h"
#include <math.h>  // for INFINITY
#include <stdlib.h> // for malloc/free
#include <stdio.h>  // for print stuff

// OUTPUT
void sr_dist_print_matrix (GrB_Matrix A, char *name);
void sr_dist_print_vector (GrB_Vector v, char *name);

GrB_Info Dist_init ( );
GrB_Info Dist_finalize ( );

extern GrB_Monoid   Dist_min_monoid;
extern GrB_Semiring Dist_min_plus;
extern GrB_Monoid   dist_LAND_BOOL;

#endif

