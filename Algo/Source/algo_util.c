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

#include <inttypes.h>
#include "sr_dist.h"

#undef MIN
#undef MAX
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#define OK(method)                                          \
{                                                           \
    info = method;                                          \
    if (! (info == GrB_SUCCESS || info == GrB_NO_VALUE))    \
    {                                                       \
        printf ("file %s line %d\n", __FILE__, __LINE__);   \
        printf ("%s\n", GrB_error ( ));                     \
        FREE_ALL;                                           \
        return (info);                                      \
    }                                                       \
}


#undef FREE_ALL
#define FREE_ALL                 \
    if (I  != NULL) free (I);    \
    if (J  != NULL) free (J);    \
    if (X  != NULL) free (X);    \
    if (I2 != NULL) free (I2);   \
    if (J2 != NULL) free (J2);   \
    if (X2 != NULL) free (X2);   \
    GrB_free (&C);

//------------------------------------------------------------------------------
// read a matrix from a file
//------------------------------------------------------------------------------

GrB_Info algo_util_read_matrix        // read a float matrix
(
    GrB_Matrix *A_output,   // handle of matrix to create
    FILE *f
)
{

    int64_t len = 256;
    int64_t ntuples = 0;
    int64_t i, j;
    float x;

    //--------------------------------------------------------------------------
    // set all pointers to NULL so that FREE_ALL can free everything safely
    //--------------------------------------------------------------------------

    GrB_Matrix C = NULL, A = NULL, B = NULL;

    //--------------------------------------------------------------------------
    // allocate initial space for tuples
    //--------------------------------------------------------------------------

    GrB_Index *I = malloc (len * sizeof (int64_t)), *I2 = NULL;
    GrB_Index *J = malloc (len * sizeof (int64_t)), *J2 = NULL;
    float     *X = malloc (len * sizeof (float  )), *X2 = NULL;
    if (I == NULL || J == NULL || X == NULL)
    {
        // out of memory
        printf ("out of memory for initial tuples\n");
        FREE_ALL;
        return (GrB_OUT_OF_MEMORY);
    }

    //--------------------------------------------------------------------------
    // read in the tuples from file, one per line
    //--------------------------------------------------------------------------

    while (fscanf (f, "%" PRIu64 " %" PRIu64 " %g\n", &i, &j, &x) != EOF)
    {
        if (ntuples >= len)
        {
            I2 = realloc (I, 2 * len * sizeof (int64_t));
            J2 = realloc (J, 2 * len * sizeof (int64_t));
            X2 = realloc (X, 2 * len * sizeof (float ));
            if (I2 == NULL || J2 == NULL || X2 == NULL)
            {
                printf ("out of memory for tuples\n");
                FREE_ALL;
                return (GrB_OUT_OF_MEMORY);
            }
            I = I2;
            I2 = NULL;
            J = J2;
            J2 = NULL;
            X = X2;
            X2 = NULL;
            len = len * 2;
        }
        I [ntuples] = i;
        J [ntuples] = j;
        X [ntuples] = x;
        ntuples++;
    }

    //--------------------------------------------------------------------------
    // find the dimensions
    //--------------------------------------------------------------------------

    printf ("ntuples: %" PRIu64 "\n", ntuples);
    int64_t nrows = 0;
    int64_t ncols = 0;
    for (int64_t k = 0; k < ntuples; k++)
    {
        nrows = MAX (nrows, I [k]);
        ncols = MAX (ncols, J [k]);
    }
    nrows++;
    ncols++;

    int64_t n = MAX (nrows, ncols);
    printf ("n %" PRIu64 "\n", n);

    double tic [2], t1, t2;

    //--------------------------------------------------------------------------
    // build the matrix, summing up duplicates, and then free the tuples
    //--------------------------------------------------------------------------

    GrB_Info info;
    OK (GrB_Matrix_new (&C, GrB_FP32, n, n));
    OK (GrB_Matrix_build (C, I, J, X, ntuples, GrB_PLUS_FP32));

    free (I);
    I = NULL;
    free (J);
    J = NULL;
    free (X);
    X = NULL;

    //--------------------------------------------------------------------------
    // create the output matrix
    //--------------------------------------------------------------------------


    //----------------------------------------------------------------------
    // return the matrix as-is
    //----------------------------------------------------------------------

    printf ("leave A as-is\n");
    *A_output = C;
    // set C to NULL so the FREE_ALL macro does not free *A_output
    C = NULL;

    //--------------------------------------------------------------------------
    // success: free everything except the result, and return it to the caller
    //--------------------------------------------------------------------------

    FREE_ALL;
    return (GrB_SUCCESS);
}
// INPUT
#undef FREE_ALL
#define FREE_ALL    \
    GrB_free (&A);
GrB_Info algo_util_get_matrix    // get a matrix from f
(
    GrB_Matrix *A_output,   // matrix to create
    char *fin               // input file
)
{

    GrB_Info info;
    GrB_Index nrows = 1, ncols = 1, nvals;
    GrB_Matrix A = NULL;
    //----------------------------------------------------------------------
    // read a matrix from fin
    //----------------------------------------------------------------------

    // usage:  ./main fspec
    FILE *finp;

    finp = fopen(fin, "r");

    OK (algo_util_read_matrix (&A, finp));
    fclose(finp);

    OK (GrB_Matrix_nrows (&nrows, A));
    OK (GrB_Matrix_ncols (&ncols, A));
    OK (GrB_Matrix_nvals (&nvals, A));

    printf ("matrix %" PRIu64 " by %" PRIu64 ", %" PRIu64 " entries, from >%s<\n",
            nrows, ncols, nvals, fin);

    *A_output = A;
    A = NULL;
    return (GrB_SUCCESS);
}

// OUTPUT
#undef FREE_ALL
//------------------------------------------------------------------------------
// print a vector
//------------------------------------------------------------------------------

void algo_util_print_vector (GrB_Vector v, char *name)
{
    GrB_Index nrows, ncols, nentries;

    GrB_Vector_nvals (&nentries, v);
    GrB_Vector_size (&nrows, v);

    printf ("\n%% GraphBLAS vector %s: nrows: %" PRIu64 " entries: %" PRIu64 "\n",
            name, nrows, nentries);

    GrB_Index *I = malloc (MAX (nentries,1) * sizeof (GrB_Index));
    float *X = malloc (MAX (nentries,1) * sizeof (float));
    GrB_Vector_extractTuples_FP32 (I, X, &nentries, v);

    printf ("%s = sparse (%" PRIu64 ");\n", name, nrows);
    for (int64_t k = 0; k < nentries; k++)
    {
        printf ("    %s (%" PRIu64 ") =  (%6.2f);\n",
                name, I [k], X [k]);
    }
    printf ("%s\n", name);

    free (I);
    free (X);
}

//------------------------------------------------------------------------------
// print a matrix
//------------------------------------------------------------------------------

void algo_util_print_matrix (GrB_Matrix A, char *name)
{
    GrB_Index nrows, ncols, nentries;

    GrB_Matrix_nvals (&nentries, A);
    GrB_Matrix_nrows (&nrows, A);
    GrB_Matrix_ncols (&ncols, A);

    printf ("\n%% GraphBLAS matrix %s: nrows: %" PRIu64 " ncols %" PRIu64 " entries: %" PRIu64 "\n",
            name, nrows, ncols, nentries);

    GrB_Index *I = malloc (MAX (nentries,1) * sizeof (GrB_Index));
    GrB_Index *J = malloc (MAX (nentries,1) * sizeof (GrB_Index));
    float *X = malloc (MAX (nentries,1) * sizeof (float));

//    GrB_Info GrB_Matrix_extractTuples_FP32      // [I,J,X] = find (A)
//    (
//        GrB_Index *I,               // array for returning row indices of tuples
//        GrB_Index *J,               // array for returning col indices of tuples
//        float *X,                   // array for returning values of tuples
//        GrB_Index *nvals,           // I,J,X size on input; # tuples on output
//        const GrB_Matrix A          // matrix to extract tuples from
//    );
//    GrB_Matrix_extractTuples_UDT (I, J, X, &nentries, A);
    GrB_Matrix_extractTuples_FP32 (I, J, X, &nentries, A);

    printf ("%s = sparse (%" PRIu64 ",%" PRIu64 ");\n", name, nrows, ncols);
    for (int64_t k = 0; k < nentries; k++)
    {
//        printf ("    %s (%" PRIu64 ",%" PRIu64 ") =  (%20.16g) + (%20.16g)*1i;\n",
        printf ("    %s (%" PRIu64 ",%" PRIu64 ") =  (%6.2f);\n",
                name, I [k], J [k], X [k]);
//                name, 1 + I [k], 1 + J [k], creal (X [k]), cimag (X [k]));
    }
    printf ("%s\n", name);

    free (I);
    free (J);
    free (X);
}

