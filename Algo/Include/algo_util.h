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

#ifndef ALGO_ALGO_UTIL_H
#define ALGO_ALGO_UTIL_H
#include "GraphBLAS.h"

// INPUT
GrB_Info algo_util_get_matrix    // get a matrix from stdin
(
    GrB_Matrix *A_output,        // matrix to create
    char *f                      // file to read the tuples from
);
GrB_Info algo_util_read_matrix   // read a float matrix
(
    GrB_Matrix *A,          // handle of matrix to create
    FILE *f                 // file to read the tuples from
);
// OUTPUT
void algo_util_print_matrix (GrB_Matrix A, char *name);
void algo_util_print_vector (GrB_Vector v, char *name);

#endif

