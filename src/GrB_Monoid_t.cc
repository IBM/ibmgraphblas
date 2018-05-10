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

GrB_Monoid_t::GrB_Monoid_t
(
    GrB_Type	D,
    void (*op)(void*, const void*, const void*),
    const void* zero,
    size_t	len
)
{
    _valid = true;
    _D = D;
    _op = op;
    _zero = malloc(len);
    assert(_zero);		// (JEM) need a better error handling
    memcpy(_zero,zero,len);
    _len = len;
    assert(D->size() == len);
}

GrB_Monoid_t::~GrB_Monoid_t
(
)
{
    free(_zero);
}

bool GrB_Monoid_t::valid
(
) const
{
    return _valid;
}

GrB_Type GrB_Monoid_t::D
(
) const
{
    return _D;
}

GrB_Type GrB_Monoid_t::D_in_1
(
) const
{
    return _D;
}

GrB_Type GrB_Monoid_t::D_in_2
(
) const
{
    return _D;
}

GrB_Type GrB_Monoid_t::D_out
(
) const
{
    return _D;
}

size_t GrB_Monoid_t::len
(
) const
{
    return _len;
}

void (*GrB_Monoid_t::op() const)(void*, const void*, const void*)
{
    return _op;
}

void GrB_Monoid_t::f
(
    void        *out,
    const void  *in1,
    const void  *in2
) const
{
    return _op(out,in1,in2);
}

Scalar GrB_Monoid_t::zero
(
) const
{
   Scalar z(_D,_zero);
   return z;
}
