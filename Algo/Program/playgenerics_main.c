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

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#define typename(x) _Generic((x),        /* Get the name of a type */             \
                                                                                  \
        _Bool:                  "_Bool",                                          \
        unsigned char:          "unsigned char",                                  \
        char:                   "char",                                           \
        signed char:            "signed char",                                    \
        short int:              "short int",                                      \
        unsigned short int:     "unsigned short int",                             \
        int:                    "int",                                            \
        unsigned int:           "unsigned int",                                   \
        long int:               "long int",                                       \
        unsigned long int:      "unsigned long int",                              \
        long long int:          "long long int",                                  \
        unsigned long long int: "unsigned long long int",                         \
        float:                  "float",                                          \
        double:                 "double",                                         \
        long double:            "long double",                                    \
        char *:                 "pointer to char",                                \
        void *:                 "pointer to void",                                \
        int *:                  "pointer to int",                                 \
        default:                "other")

#define fmt "%20s is '%s'\n"
int main() {

    size_t s;
    ptrdiff_t p;
    intmax_t i;
    int ai[3] = {0};

    printf( fmt fmt fmt fmt fmt fmt fmt fmt,
            "size_t", typename(s),               "ptrdiff_t", typename(p),
            "intmax_t", typename(i),      "character constant", typename('0'),
            "0x7FFFFFFF", typename(0x7FFFFFFF),     "0xFFFFFFFF", typename(0xFFFFFFFF),
            "0x7FFFFFFFU", typename(0x7FFFFFFFU),  "array of int", typename(ai));
}
