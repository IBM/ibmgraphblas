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

#include "IBM_GraphBLAS.hh"
#include <assert.h>
#include <string.h>

GrB_Semiring_t::GrB_Semiring_t
(
    GrB_Type    D_out,
    GrB_Type    D_in_1,
    GrB_Type    D_in_2,
    void (*add)(void*, const void*, const void*),
    void (*mul)(void*, const void*, const void*),
    const void* zero,
    size_t      len
)
{
    _valid = true;
    _D_out = D_out;
    _D_in_1 = D_in_1;
    _D_in_2 = D_in_2;
    _add = add;
    _mul = mul;
    _zero = malloc(len);
    assert(_zero);              // (JEM) need a better error handling
    memcpy(_zero,zero,len);
    _len = len;
}

GrB_Semiring_t::~GrB_Semiring_t
(
)
{
    free(_zero);
}

bool GrB_Semiring_t::valid
(
) const
{
    return _valid;
}

GrB_Type GrB_Semiring_t::D_in_1
(
) const
{
    return _D_in_1;
}

GrB_Type GrB_Semiring_t::D_in_2
(
) const
{
    return _D_in_2;
}

GrB_Type GrB_Semiring_t::D_out
(
) const
{
    return _D_out;
}

void GrB_Semiring_t::add
(
    void	*out,
    const void	*in1,
    const void	*in2
) const
{
    return _add(out,in1,in2);
}

void GrB_Semiring_t::mul
(
    void	*out,
    const void	*in1,
    const void	*in2
) const
{
    return _mul(out,in1,in2);
}

Scalar GrB_Semiring_t::zero
(
) const
{
   Scalar z(_D_out,_zero);
   return z;
}
