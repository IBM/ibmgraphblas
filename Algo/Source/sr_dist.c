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

#include "sr_dist.h"
#include "algo_util.h"

#undef MIN
#undef MAX
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

// OUTPUT
//------------------------------------------------------------------------------
// print a vector
//------------------------------------------------------------------------------

void sr_dist_print_vector (GrB_Vector v, char *name)
{
    algo_util_print_vector(v, name);
}

//------------------------------------------------------------------------------
// print a matrix
//------------------------------------------------------------------------------

void sr_dist_print_matrix (GrB_Matrix A, char *name)
{
    algo_util_print_matrix(A, name);
}

// Semirings
GrB_Monoid Dist_min_monoid = NULL; // Min monoid
GrB_Semiring Dist_min_plus ; // min.plus semiring

// Monoid for compare
GrB_Monoid dist_LAND_BOOL = NULL;

#undef OK
#define OK(method)            \
    info = method;           \
    if (info != GrB_SUCCESS)  \
    {                         \
        Dist_finalize ( );   \
        return (info);       \
    }
GrB_Info Dist_init ( )
{
    GrB_Info info;
    OK (GrB_Monoid_new(&Dist_min_monoid ,GrB_MIN_FP32, INFINITY ));
    OK (GrB_Semiring_new(&Dist_min_plus , Dist_min_monoid ,GrB_PLUS_FP32));

    OK (GrB_Monoid_new_BOOL(&dist_LAND_BOOL ,GrB_LAND, true));
    return (GrB_SUCCESS);
}
GrB_Info Dist_finalize ( )
{
    //--------------------------------------------------------------------------
    // free the Dist min-plus semiring
    //--------------------------------------------------------------------------

    // TODO what happens if you free monoids before semiring
    GrB_free (&Dist_min_plus);

    //--------------------------------------------------------------------------
    // free the Dist monoid
    //--------------------------------------------------------------------------

    GrB_free (&Dist_min_monoid );

    //--------------------------------------------------------------------------
    // free the compare binaryOp
    //--------------------------------------------------------------------------

    GrB_free (&dist_LAND_BOOL );

    return (GrB_SUCCESS);
}
