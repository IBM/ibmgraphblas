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

GrB_Type_t::GrB_Type_t
(
    size_t      size
)
{
    _size = size;
    _valid = true;
}

GrB_Type_t::~GrB_Type_t
(
)
{
}

bool GrB_Type_t::valid
(
) const
{
    return _valid;
}

size_t GrB_Type_t::size
(
) const
{
    return _size;
}

bool GrB_Type_t::predefined
(
) const
{
    if (this == GrB_BOOL  ) return true;
    if (this == GrB_INT8  ) return true;
    if (this == GrB_UINT8 ) return true;
    if (this == GrB_INT16 ) return true;
    if (this == GrB_UINT16) return true;
    if (this == GrB_INT32 ) return true;
    if (this == GrB_UINT32) return true;
    if (this == GrB_INT64 ) return true;
    if (this == GrB_UINT64) return true;
    if (this == GrB_FP32  ) return true;
    if (this == GrB_FP64  ) return true;
    return false;
}

bool GrB_Type_t::compatible
(
    GrB_Type    T
) const
{
    if (this->predefined() && T->predefined()) return true;
    return false;
}

template<class OUT, class IN>
static
void *clone(OUT dummy, IN x)
{
    OUT *y = (OUT*)malloc(sizeof(OUT));
    *y = x;
    return y;
}

template<class T>
static
void *clone(const GrB_Type_t *type, T x)
{
    if (type == GrB_BOOL)   { bool      y; return ::clone(y, x); }
    if (type == GrB_INT8)   { int8_t    y; return ::clone(y, x); }
    if (type == GrB_UINT8)  { uint8_t   y; return ::clone(y, x); }
    if (type == GrB_INT16)  { int16_t   y; return ::clone(y, x); }
    if (type == GrB_UINT16) { uint16_t  y; return ::clone(y, x); }
    if (type == GrB_INT32)  { int32_t   y; return ::clone(y, x); }
    if (type == GrB_UINT32) { uint32_t  y; return ::clone(y, x); }
    if (type == GrB_INT64)  { int64_t   y; return ::clone(y, x); }
    if (type == GrB_UINT64) { uint64_t  y; return ::clone(y, x); }
    if (type == GrB_FP32)   { float     y; return ::clone(y, x); }
    if (type == GrB_FP64)   { double    y; return ::clone(y, x); }
    assert(0 > 1);
}

template<class IN>
void *GrB_Type_t::clone
(
    IN x
) const
{
    return ::clone(this,x);
}

void *GrB_Type_t::clone
(
    const void *x
) const
{
    void *y = malloc(size());
    memcpy(y,x,size());
    return y;
}

void *GrB_Type_t::clone
(
    const void          *x,
    const GrB_Type      type
) const
{
    if (type == GrB_BOOL  ) return clone(*((bool    *)x));
    if (type == GrB_INT8  ) return clone(*((int8_t  *)x));
    if (type == GrB_UINT8 ) return clone(*((uint8_t *)x));
    if (type == GrB_INT16 ) return clone(*((int16_t *)x));
    if (type == GrB_UINT16) return clone(*((uint16_t*)x));
    if (type == GrB_INT32 ) return clone(*((int32_t *)x));
    if (type == GrB_UINT32) return clone(*((uint32_t*)x));
    if (type == GrB_INT64 ) return clone(*((int64_t *)x));
    if (type == GrB_UINT64) return clone(*((uint64_t*)x));
    if (type == GrB_FP32  ) return clone(*((float   *)x));
    if (type == GrB_FP64  ) return clone(*((double  *)x));
    assert(type == this);
    return clone(x);
}
