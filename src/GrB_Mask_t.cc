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

GrB_mask_t::GrB_mask_t
(
    bool                scmp,
    const GrB_Vector_t  *m,
    const GrB_Vector_t  &v
)
{
    if (m == GrB_NULL)
    {
        _size = v.size();
        _ind = new uset<GrB_Index>;
        if (!scmp) for (GrB_Index i = 0; i<_size; i++) _ind->insert(i);
    }
    else
    {
	_size = m->size();
	_ind = new uset<GrB_Index>;
	if (scmp)
	{
	    for (GrB_Index i = 0; i<_size; i++) _ind->insert(i);
	    for (auto k : *(m->ind())) _ind->erase(k);
	}
	else
	{
	    for (auto k : *(m->ind())) _ind->insert(k);
	}
    }
}

GrB_mask_t::~GrB_mask_t
(
)
{
    delete _ind;
}

const uset<GrB_Index>*  GrB_mask_t::ind
(
) const
{
    return _ind;
}

GrB_Index GrB_mask_t::size
(
) const
{
    return _size;
}

GrB_Mask_t::GrB_Mask_t
(
   bool                 scmp,
   const GrB_Matrix     M,
   const GrB_Matrix_t&  C
)
{
    _nrows = (M == GrB_NULL) ? C.nrows() : M->nrows();
    _ncols = (M == GrB_NULL) ? C.ncols() : M->ncols();

    _rows.resize(_nrows); 
    for (GrB_Index i=0; i<_nrows; i++) 
    {
        _rows[i] = new GrB_mask_t(scmp,(M == GrB_NULL) ? (GrB_Vector)GrB_NULL : &((*M)[i]), C[i]);
    }

    _cols.resize(_ncols); 
    for (GrB_Index j=0; j<_ncols; j++) 
    {
        _cols[j] = new GrB_mask_t(scmp,(M == GrB_NULL) ? (GrB_Vector)GrB_NULL : &((*M)(j)), C(j));
    }
}

GrB_Mask_t::~GrB_Mask_t
(
)
{
    for (GrB_Index i=0; i<nrows(); i++) delete _rows[i];
    for (GrB_Index j=0; j<ncols(); j++) delete _cols[j];
}

GrB_Index GrB_Mask_t::nrows
(
) const
{
    return _nrows;
}

GrB_Index GrB_Mask_t::ncols
(
) const
{
    return _ncols;
}

const GrB_mask_t& GrB_Mask_t::operator[]
(
    GrB_Index i
) const
{
    assert(i<nrows());
    return *(_rows[i]);
}

const GrB_mask_t& GrB_Mask_t::operator()
(
    GrB_Index j
) const
{
    assert(j<ncols());
    return *(_cols[j]);
}
