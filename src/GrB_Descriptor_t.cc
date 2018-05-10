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

GrB_Descriptor_t::GrB_Descriptor_t
(
)
{
    _valid = true;
    _replace = false;
    _scmp = false;
    _tran0 = false;
    _tran1 = false;
}

GrB_Descriptor_t::~GrB_Descriptor_t
(
)
{
}

bool GrB_Descriptor_t::valid
(
) const
{
    return _valid;
}

bool GrB_Descriptor_t::outp_replace
(
) const
{
    return _replace;
}

bool GrB_Descriptor_t::mask_scmp
(
) const
{
    return _scmp;
}

bool GrB_Descriptor_t::inp0_tran
(
) const
{
    return _tran0;
}

bool GrB_Descriptor_t::inp1_tran
(
) const
{
    return _tran1;
}

void GrB_Descriptor_t::setReplace
(
)
{
    _replace = true;
}

void GrB_Descriptor_t::setSCMP
(
)
{
    _scmp = true;
}

void GrB_Descriptor_t::setTran0
(
)
{
    _tran0 = true;
}

void GrB_Descriptor_t::setTran1
(
)
{
    _tran1 = true;
}
