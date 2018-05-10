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

Scalar::~Scalar
(
)
{
    free(_data);
}

Scalar::Scalar
(
    const Scalar& s
)
{
    _D = s._D;
    _data = malloc(_D->size());
    memcpy(_data,s._data,_D->size());
}

Scalar::Scalar
(
    GrB_Type D,
    const void *data
)
{ 
    _D = D;
    _data = malloc(_D->size());
    memcpy(_data, data, D->size());
}

Scalar::Scalar
(
    GrB_Type D
)
{ 
    _D = D;
    _data = malloc(_D->size());
}

Scalar& Scalar::operator=(
    const Scalar& s
)
{
    if (this == &s) return *this;
    free(_data);
    _D = s._D;
    _data = malloc(_D->size());
    memcpy(_data,s._data,_D->size());
    return *this;
}

Scalar::operator void*
(
)
{
    return _data;
}

Scalar::operator const void*
(
) const
{
    return _data;
}

Scalar Scalar::operator()
(
    GrB_Type type
) const
{
    void *temp = type->clone(_data,_D); assert(temp);
    Scalar a(type,temp);
    free(temp);
    return a;
}

const GrB_Type Scalar::D
(
) const
{
    return _D;
}
