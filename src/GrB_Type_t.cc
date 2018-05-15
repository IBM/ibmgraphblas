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
    return false;
}

bool GrB_Type_t::compatible
(
    GrB_Type    T
) const
{
    if (this->predefined() && T->predefined()) return true;
    if (this == T) return true;
    return false;
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
    assert(type == this);
    return clone(x);
}

void GrB_Type_t::clone
(
    bool       *y,
    const void *x
) const
{
    assert(0 == 1);
}

void GrB_Type_t::clone
(
    int8_t     *y,
    const void *x
) const
{
    assert(0 == 1);
}

void GrB_Type_t::clone
(
    uint8_t    *y,
    const void *x
) const
{
    assert(0 == 1);
}

void GrB_Type_t::clone
(
    int16_t    *y,
    const void *x
) const
{
    assert(0 == 1);
}

void GrB_Type_t::clone
(
    uint16_t   *y,
    const void *x
) const
{
    assert(0 == 1);
}

void GrB_Type_t::clone
(
    int32_t    *y,
    const void *x
) const
{
    assert(0 == 1);
}

void GrB_Type_t::clone
(
    uint32_t   *y,
    const void *x
) const
{
    assert(0 == 1);
}

void GrB_Type_t::clone
(
    int64_t    *y,
    const void *x
) const
{
    assert(0 == 1);
}

void GrB_Type_t::clone
(
    uint64_t   *y,
    const void *x
) const
{
    assert(0 == 1);
}

void GrB_Type_t::clone
(
    float      *y,
    const void *x
) const
{
    assert(0 == 1);
}

void GrB_Type_t::clone
(
    double     *y,
    const void *x
) const
{
    assert(0 == 1);
}

template<typename T>
Type<T>::Type
(
) : GrB_Type_t(sizeof(T))
{
}

template<typename T>
Type<T>::~Type
(
)
{
}

template<typename T>
bool Type<T>::predefined
(
) const
{
    return true;
}

template<typename T>
bool Type<T>::compatible
(
    GrB_Type D
) const
{
    if (predefined() && D->predefined()) return true;
    if (this == D) return true;
    return false;
}

template<typename T>
void *Type<T>::clone
(
    void const      *x,
    const GrB_Type   type
) const
{
    T *y = new T;
    type->clone(y,x);
    return y;
}

template<typename T>
void Type<T>::clone
(
    bool       *y,
    const void *x
) const
{
    *y = *((T*)x);
}

template<typename T>
void Type<T>::clone
(
    int8_t     *y,
    const void *x
) const
{
    *y = *((T*)x);
}

template<typename T>
void Type<T>::clone
(
    uint8_t    *y,
    const void *x
) const
{
    *y = *((T*)x);
}

template<typename T>
void Type<T>::clone
(
    int16_t    *y,
    const void *x
) const
{
    *y = *((T*)x);
}

template<typename T>
void Type<T>::clone
(
    uint16_t   *y,
    const void *x
) const
{
    *y = *((T*)x);
}

template<typename T>
void Type<T>::clone
(
    int32_t    *y,
    const void *x
) const
{
    *y = *((T*)x);
}

template<typename T>
void Type<T>::clone
(
    uint32_t   *y,
    const void *x
) const
{
    *y = *((T*)x);
}

template<typename T>
void Type<T>::clone
(
    int64_t    *y,
    const void *x
) const
{
    *y = *((T*)x);
}

template<typename T>
void Type<T>::clone
(
    uint64_t   *y,
    const void *x
) const
{
    *y = *((T*)x);
}

template<typename T>
void Type<T>::clone
(
    float      *y,
    const void *x
) const
{
    *y = *((T*)x);
}

template<typename T>
void Type<T>::clone
(
    double     *y,
    const void *x
) const
{
    *y = *((T*)x);
}

template class Type<bool>;
template class Type<int8_t>;
template class Type<uint8_t>;
template class Type<int16_t>;
template class Type<uint16_t>;
template class Type<int32_t>;
template class Type<uint32_t>;
template class Type<int64_t>;
template class Type<uint64_t>;
template class Type<float>;
template class Type<double>;
