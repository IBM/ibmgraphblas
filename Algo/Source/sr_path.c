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
// GraphBLAS/Demos/sr_path.c: bellman-ford for floats
//------------------------------------------------------------------------------

// Adaptation of Fineman, Jeremy T., and Eric Robinson.
// "Fundamental graph algorithms."
// Graph Algorithms in the Language of Linear Algebra 22 (2011): 45.

#include <string.h>
#include <limits.h>
#include <inttypes.h>
#include "sr_path.h"

#undef MIN
#undef MAX
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

// INPUT
// NONE

// OUTPUT
void sr_path_print_vector (GrB_Vector v, char *name)
{
    GrB_Index nrows, ncols, nentries;

    GrB_Vector_nvals (&nentries, v);
    GrB_Vector_size (&nrows, v);

    printf ("\n%% GraphBLAS vector %s: nrows: %" PRIu64 " entries: %" PRIu64 "\n",
            name, nrows, nentries);

    GrB_Index *I = malloc (MAX (nentries,1) * sizeof (GrB_Index));
    path *X = malloc (MAX (nentries,1) * sizeof (path));
    GrB_Vector_extractTuples_UDT (I, X, &nentries, v);

    printf ("%s = sparse (%" PRIu64 ");\n", name, nrows);
    for (int64_t k = 0; k < nentries; k++)
    {
        char str[40];
        if (X[k].penultimate == PathNodeNil)
            strcpy(str,"Nil");
        else
            sprintf(str, "%" PRIu64 "", X[k].penultimate);
        printf ("    %s (%" PRIu64 ") =  (%6.2f, %" PRIu64 ", %1s);\n",
                name, I[k], X[k].distance, X[k].hops, str);
    }
    printf ("%s\n", name);

    free (I);
    free (X);
}

void sr_path_print_matrix (GrB_Matrix A, char *name)
{
    GrB_Index nrows, ncols, nentries;

    GrB_Matrix_nvals (&nentries, A);
    GrB_Matrix_nrows (&nrows, A);
    GrB_Matrix_ncols (&ncols, A);

    printf ("\n%% GraphBLAS matrix %s: nrows: %" PRIu64 " ncols %" PRIu64 " entries: %" PRIu64 "\n",
            name, nrows, ncols, nentries);

    GrB_Index *I = malloc (MAX (nentries,1) * sizeof (GrB_Index));
    GrB_Index *J = malloc (MAX (nentries,1) * sizeof (GrB_Index));
    path *X = malloc (MAX (nentries,1) * sizeof (path));

//    GrB_Info GrB_Matrix_extractTuples_FP32      // [I,J,X] = find (A)
//    (
//        GrB_Index *I,               // array for returning row indices of tuples
//        GrB_Index *J,               // array for returning col indices of tuples
//        float *X,                   // array for returning values of tuples
//        GrB_Index *nvals,           // I,J,X size on input; # tuples on output
//        const GrB_Matrix A          // matrix to extract tuples from
//    );
    GrB_Matrix_extractTuples_UDT (I, J, X, &nentries, A);
//    GrB_Matrix_extractTuples_FP32 (I, J, X, &nentries, A);

    printf ("%s = sparse (%" PRIu64 ",%" PRIu64 ");\n", name, nrows, ncols);
    for (int64_t k = 0; k < nentries; k++)
    {
//        printf ("    %s (%" PRIu64 ",%" PRIu64 ") =  (%20.16g) + (%20.16g)*1i;\n",
        char str[40];
        if (X[k].penultimate == PathNodeNil)
            strcpy(str,"Nil");
        else
            sprintf(str, "%" PRIu64 "", X[k].penultimate);
        printf ("    %s (%" PRIu64 ",%" PRIu64 ") =  (%6.2f, %" PRIu64 ", %1s);\n",
                name, I[k], J[k], X[k].distance, X[k].hops, str);
//                name, 1 + I [k], 1 + J [k], creal (X [k]), cimag (X [k]));
    }
    printf ("%s\n", name);

    free (I);
    free (J);
    free (X);
}


// Semirings
GrB_Type Path = NULL;
GrB_BinaryOp Path_min = NULL, Path_plus = NULL;
GrB_Monoid   Path_min_monoid = NULL, Path_plus_monoid = NULL;
GrB_Semiring Path_min_plus = NULL;
const GrB_Index PathNodeNil = ULONG_MAX - 1L;
const path PathMinPlusSr_ONE = {INFINITY, ULONG_MAX, ULONG_MAX};
const path PathMinPlusSr_ZERO = {0.0, 0L, ULONG_MAX - 1L};

GrB_BinaryOp Path_eq = NULL;

// for convenience
#define P struct path
#define X *x
#define Y *y
#define Z *z

//------------------------------------------------------------------------------
// sr_path: Bellman-Ford with path
//------------------------------------------------------------------------------

void sr_path_min (P Z, const P X, const P Y)
{
//    printf("sr_path_min: X.distance: >%f<, X.hops: >%" PRIu64 "<, X.penultimate: >%" PRIu64 "<\n", x->distance, x->hops, x->penultimate);
//    printf("sr_path_min: Y.distance: >%f<, Y.hops: >%" PRIu64 "<, Y.penultimate: >%" PRIu64 "<\n", y->distance, y->hops, y->penultimate);
    if (x->distance < y->distance)
        Z = X;
    else if ((x->distance == y->distance) && (x->hops < y->hops))
        Z = X;
    else if ((x->distance == y->distance) && (x->hops == y->hops) && ((y->penultimate != PathNodeNil) && (x->penultimate < y->penultimate)))
        Z = X;
    else
        Z = Y;
//    printf("sr_path_min: Z.distance: >%f<, Z.hops: >%" PRIu64 "<, Z.penultimate: >%" PRIu64 "<\n", z->distance, z->hops, z->penultimate);
}

void sr_path_eq (P Z, const P X, const P Y)
{
    if (x->distance != y->distance)
        Z = PathMinPlusSr_ONE;
    else if (x->hops != y->hops)
        Z = PathMinPlusSr_ONE;
    else if (x->penultimate < y->penultimate)
        Z = PathMinPlusSr_ONE;
    else
        Z = PathMinPlusSr_ZERO;
}

static GrB_Index sr_path_g(GrB_Index x, GrB_Index y)
{
    if (x == ULONG_MAX || y == ULONG_MAX)
        return ULONG_MAX;
    else
        return x + y;
}

void sr_path_plus (P Z, const P Y, const P X)
{
    float w1 = x->distance;
    GrB_Index h1 = x->hops;
    GrB_Index p1 = x->penultimate;
    float w2 = y->distance;
    GrB_Index h2 = y->hops;
    GrB_Index p2 = y->penultimate;
//    printf("sr_path_plus: w1: >%f<, h1: >%" PRIu64 "<, p1: >%" PRIu64 "<\n", w1, h1, p1);
//    printf("sr_path_plus: w2: >%f<, h2: >%" PRIu64 "<, p2: >%" PRIu64 "<\n", w2, h2, p2);
    if (p2 != PathMinPlusSr_ZERO.penultimate)
        if (p1 == PathMinPlusSr_ZERO.penultimate) {
            z->distance = w1 + w2;
            z->hops = sr_path_g(h1, h2);
            z->penultimate = p2;
        } // Z = (path){w1 + w2, sr_path_g(h1, h2), p2};
        else if (p2 != PathNodeNil) {
            z->distance = w1 + w2;
            z->hops = sr_path_g(h1, h2);
            z->penultimate = p2;
        } // Z = (path){w1 + w2, sr_path_g(h1, h2), p2};
        else {
            z->distance = w1 + w2;
            z->hops = sr_path_g(h1, h2);
            z->penultimate = p1;
        } // Z = (path){w1 + w2, sr_path_g(h1, h2), p1}; // original
    else {
        z->distance = w1 + w2;
        z->hops = sr_path_g(h1, h2);
        z->penultimate = p1;
    } // Z = (path){w1 + w2, sr_path_g(h1, h2), p1};
//    printf("sr_path_plus: Z.distance: >%f<, Z.hops: >%" PRIu64 "<, Z.penultimate: >%" PRIu64 "<\n", z->distance, z->hops, z->penultimate);
}

#undef OK
#define OK(method)            \
    info = method;           \
    if (info != GrB_SUCCESS)  \
    {                         \
        Path_finalize ( );   \
        return (info);       \
    }
GrB_Info Path_init ( )
{
    GrB_Info info;
    OK (GrB_Type_new (&Path, sizeof(path)));

    OK (GrB_BinaryOp_new (&Path_min, (void (*)(void*,const void*,const void*))sr_path_min, Path, Path, Path));
    OK (GrB_Monoid_new_UDT (&Path_min_monoid, Path_min, &PathMinPlusSr_ONE));
    OK (GrB_BinaryOp_new (&Path_plus, (void (*)(void*,const void*,const void*))sr_path_plus, Path, Path, Path));
    OK (GrB_Monoid_new_UDT (&Path_plus_monoid, Path_min, &PathMinPlusSr_ONE));

    OK (GrB_BinaryOp_new (&Path_eq, (void (*)(void*,const void*,const void*))sr_path_eq, Path, Path, Path));

    // the semiring
    OK (GrB_Semiring_new
        (&Path_min_plus, Path_min_monoid, Path_plus));

    return (GrB_SUCCESS);
}
GrB_Info Path_finalize ( )
{
    //--------------------------------------------------------------------------
    // free the Path Type
    //--------------------------------------------------------------------------

    GrB_free (&Path);

    //--------------------------------------------------------------------------
    // free the Path min-plus semiring
    //--------------------------------------------------------------------------

    // TODO what happens if you free monoids before semiring
    GrB_free (&Path_min_plus);

    //--------------------------------------------------------------------------
    // free the Path monoids
    //--------------------------------------------------------------------------

    GrB_free (&Path_min_monoid );

    //--------------------------------------------------------------------------
    // free the Path binary operators, CxC->C
    //--------------------------------------------------------------------------

    GrB_free (&Path_min );
    GrB_free (&Path_plus);
    GrB_free (&Path_eq);

    return (GrB_SUCCESS);
}
