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

// Read a graph from a file and find SSSP. Usage:
//
//  sr_path_main < infile
//
// Where infile has one line per edge in the graph; these have the form
//
//  i j x
//
// where A(i,j)=x is performed by GrB_Matrix_build, to construct the matrix.
// The dimensions of A are assumed to be the max of (largest row index, largest
// column index)and column indices plus one (in sr_path_read_matrix.c).

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "algo_util.h"
#include "algo_sssp_path.h"
#include "sr_path.h"

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

#define FREE_ALL     \
    GrB_free (&A);   \
    GrB_free (&p_d);

int main (int argc, char **argv)
{
    // process command line input
    int aflag = 0;
    int bflag = 0;
    char *cvalue = NULL;
    int index;
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "abc:")) != -1)
        switch (c)
        {
        case 'a':
            aflag = 1;
            break;
        case 'b':
            bflag = 1;
            break;
        case 'c':
            cvalue = optarg;
            break;
        case '?':
            if (optopt == 'c')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Unknown option character `\\x%x'.\n",
                         optopt);
            return 1;
        default:
            abort ();
        }

    printf ("aflag = %d, bflag = %d, cvalue = %s\n",
            aflag, bflag, cvalue);

    if (optind < 1)
        printf ("please specify file");

    char * fin = argv[optind];
    printf("Processing matrix from: >%s<\n", fin);
    GrB_Matrix A = NULL;
    GrB_Vector p_d = NULL;
    GrB_Info info;
    OK (GrB_init (GrB_NONBLOCKING));

    // get adjacency matrix for DiGraph
    OK (algo_util_get_matrix (&A, fin));

    // print input
    algo_util_print_matrix (A, "A(input)");

    GrB_Index n;
    OK (GrB_Matrix_nrows (&n, A));

    // initialize Path Semiring
    OK (Path_init());

    // compute SSSP
    GrB_Index source = 0;
    bool no_neg_cycle;
    OK (algo_sssp_path(A, source, &p_d, &no_neg_cycle));

    // print results
    sr_path_print_vector (p_d, "d(result)");
    if (no_neg_cycle) printf ("no neg cycle\n");
    else printf("neg cycle\n");

    OK (Path_finalize());
    GrB_finalize ( );
}
