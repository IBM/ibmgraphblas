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

#include "algo_sssp_path.h"
#include "sr_path.h"

#undef MIN
#undef MAX
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#undef OK
#define OK(method)                                          \
{                                                           \
    info = method;                                         \
    if (! (info == GrB_SUCCESS || info == GrB_NO_VALUE))    \
    {                                                       \
        printf ("file %s line %d\n", __FILE__, __LINE__);  \
        printf ("%s\n", GrB_error ( ));                    \
        FREE_ALL;                                          \
        FREE_INNER;                                        \
        return (info);                                     \
    }                                                       \
}

#undef FREE_ALL
#define FREE_ALL     \
    GrB_free (&A);  \
    GrB_free (&d);


#undef FREE_INNER
#define FREE_INNER

GrB_Info algo_sssp_path         // compute SSSP for source
(
    const GrB_Matrix A_in,      // adjacency matrix (IN/OUT)
    GrB_Index source,           // index of source vertex (IN)
    GrB_Vector* p_d,            // vector loaded w/ result (OUT)
    bool* p_no_neg_cycle        // negative cycle (OUT)
)
{
    GrB_Info info;
    GrB_Index n;

    GrB_Matrix A = GrB_NULL;
    GrB_Vector d = GrB_NULL;

    bool DEBUG = true;

    // Path_init();
    // TODO How to ensure Path has been initialized?

    // n = # of nodes in graph
    OK(GrB_Matrix_nrows (&n, A_in));

    OK(GrB_Matrix_new (&A, Path, n, n));

    // transform matrix to correct type, UGLY! TODO
    {
#undef FREE_INNER
#define FREE_INNER                         \
                if (I != NULL) free (I);  \
                if (J != NULL) free (J);  \
                if (X_in != NULL) free (X_in);

        // USE OF NULL OK TODO?
        GrB_Index nrows, ncols, nentries;
        GrB_Index *I = NULL, *J = NULL;
        float *X_in = NULL;

        OK (GrB_Matrix_nvals (&nentries, A_in));
        OK (GrB_Matrix_nrows (&nrows, A_in));
        OK (GrB_Matrix_ncols (&ncols, A_in));
        I = malloc (MAX (nentries,1) * sizeof (GrB_Index));
        J = malloc (MAX (nentries,1) * sizeof (GrB_Index));
        X_in = malloc (MAX (nentries,1) * sizeof (float));
        OK (GrB_Matrix_extractTuples(I, J, X_in, &nentries, A_in));

//        // Use GrB_Matrix_build
//        // target
//        path *X = malloc (nentries * sizeof (path));
//        for (int64_t k = 0; k < nentries; k++)
//            X[k]= (path) {X_in[k], 1L, I[k]};
//        free (X_in);
//        // NULL for duplicates? TODO
//        GrB_Matrix_build (A, I, J, (void*) X, nentries, sr_path_first);
        //        free (X);

        for (int64_t k = 0; k < nentries; k++) {
//            printf("i: >%" PRIu64 "<, j: >%" PRIu64 "<, x: >%f<\n", I[k], J[k], X_in[k]);
            const path p = (path) {
                X_in[k], 1L, I[k]
            };
            OK (GrB_Matrix_setElement (A, (void *)&p, J[k], I[k])); // note transpose
        }
        free (I);
        I = NULL;
        free (J);
        J = NULL;
        free (X_in);
        X_in = NULL;

        // distance to self
        for (int64_t k = 0; k < n; k++)
            OK( GrB_Matrix_setElement (A, (void *)&PathMinPlusSr_ZERO, k, k));

#undef FREE_INNER
    }
    if (DEBUG) sr_path_print_matrix (A, "Ainit");

    // Now that Adjacency matrix is all set,
    // use designated source (input), to initialize vector
    {
#define FREE_INNER
        OK(GrB_Vector_new (&d, Path, n));
        OK(GrB_Vector_setElement (d, (void *)&PathMinPlusSr_ZERO, source));
#undef FREE_INNER
    }
    if (DEBUG) sr_path_print_vector(d, "d_init");

    // iterate
    {
#define FREE_INNER
        for( GrB_Index i = 0; i < n; i += 1 ) {
            OK(GrB_mxv (d, GrB_NULL, GrB_NULL, Path_min_plus, A, d, GrB_NULL));
            if (DEBUG) sr_path_print_vector(d, "d_next");
        }
#undef FREE_INNER
    }


    // check for negative weight cycle
    bool no_neg_cycle;
    {
#undef FREE_INNER
#define FREE_INNER                    \
                GrB_free (&d_check);  \
                GrB_free (&d_eq);
        GrB_Vector d_check = GrB_NULL;
        GrB_Vector d_eq = GrB_NULL;

        OK(GrB_Vector_new (&d_check, Path, n));
        // one more iteration
        OK(GrB_mxv (d_check, GrB_NULL, GrB_NULL, Path_min_plus, A, d, GrB_NULL));
        if (DEBUG) sr_path_print_vector(d_check, "d_check");
        // compare the two results
        // shouldn't spec contain an easy more efficient way to test
        // equivalence of two vectors (or matrices)? TODO
        OK(GrB_Vector_new (&d_eq, Path, n));
        OK(GrB_eWiseAdd (d_eq, GrB_NULL, GrB_NULL, Path_eq, d, d_check, GrB_NULL));
        if (DEBUG) sr_path_print_vector(d_eq, "d_eq");

        path sum = PathMinPlusSr_ZERO;
        OK(GrB_reduce (&sum, GrB_NULL, Path_plus_monoid, d_eq, GrB_NULL));
        no_neg_cycle = (sum.hops == 0L);

        if (DEBUG) {
            if ( no_neg_cycle) printf ("no neg cycle\n");
            else printf("neg cycle\n");
        }

        OK(GrB_free (&d_check));
        OK(GrB_free (&d_eq));
    }
    *p_no_neg_cycle = no_neg_cycle;

    // return result
    *p_d = d;

    return (GrB_SUCCESS);
}
