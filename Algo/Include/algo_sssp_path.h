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

#ifndef ALGO_ALGO_SSSP_PATH_H
#define ALGO_ALGO_SSSP_PATH_H
#include "GraphBLAS.h"

GrB_Info algo_sssp_path         // compute SSSP for source
(
    const GrB_Matrix A,         // adjacency matrix (IN/OUT)
    GrB_Index source,           // index of source vertex (IN)
    GrB_Vector* p_d,            // vector loaded w/ result (IN/OUT)
    bool* p_no_neg_cycle        // existence of negative cycle?
);

#endif

