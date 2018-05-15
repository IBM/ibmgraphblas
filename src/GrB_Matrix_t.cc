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

GrB_Matrix_t::GrB_Matrix_t
(
)
{
    _valid = false;
    _copy = false;
    _D = 0;
    _nrows = 0;
    _ncols = 0;
}

GrB_Matrix_t::GrB_Matrix_t
(
    const GrB_Matrix_t& A
)
{
    _valid = true;
    _copy = true;
    _D = A.D();
    _nrows = A._nrows;
    _ncols = A._ncols;
    _rows.resize(_nrows); for (GrB_Index i=0; i<_nrows; i++) _rows[i] = A._rows[i];
    _cols.resize(_ncols); for (GrB_Index j=0; j<_ncols; j++) _cols[j] = A._cols[j];
    _nvals = A.nvals();
}

GrB_Matrix_t::GrB_Matrix_t
(
    bool                transpose,
    const GrB_Matrix_t& A
)
{
    _valid = true;
    _copy = true;
    _D = A.D();
    if (transpose)
    {
        _nrows = A._ncols;
        _ncols = A._nrows;
        _rows.resize(_nrows); for (GrB_Index i=0; i<_nrows; i++) _rows[i] = A._cols[i];
        _cols.resize(_ncols); for (GrB_Index j=0; j<_ncols; j++) _cols[j] = A._rows[j];
    }
    else
    {
        _nrows = A._nrows;
        _ncols = A._ncols;
        _rows.resize(_nrows); for (GrB_Index i=0; i<_nrows; i++) _rows[i] = A._rows[i];
        _cols.resize(_ncols); for (GrB_Index j=0; j<_ncols; j++) _cols[j] = A._cols[j];
    }
    _nvals = A.nvals();
}

GrB_Matrix_t::GrB_Matrix_t
(
    GrB_Type    D,
    GrB_Index   nrows,
    GrB_Index   ncols
)
{
    _valid = true;
    _copy = false;
    _D = D;
    _nrows = nrows;
    _ncols = ncols;
    _nvals = 0;
    _rows.resize(nrows); for (GrB_Index i=0; i<nrows; i++) _rows[i] = new GrB_Vector_t(D,ncols);
    _cols.resize(ncols); for (GrB_Index j=0; j<ncols; j++) _cols[j] = new GrB_Vector_t(D,nrows);
}

GrB_Matrix_t::~GrB_Matrix_t
(
)
{
    if (_copy) return;
    for (GrB_Index i=0; i<nrows(); i++) delete _rows[i];
    for (GrB_Index j=0; j<ncols(); j++) delete _cols[j];
}

bool GrB_Matrix_t::copy
(
   const GrB_Matrix_t&  A
)
{
    assert(!_copy);

    if (_valid)
    {
        clear();
        for (GrB_Index i=0; i<nrows(); i++) delete _rows[i];
        for (GrB_Index j=0; j<ncols(); j++) delete _cols[j];
    }

    _valid = true;
    _copy = false;
    _D = A.D();
    _nrows = A._nrows;
    _ncols = A._ncols;
    _rows.resize(_nrows); for (GrB_Index i=0; i<_nrows; i++) _rows[i] = new GrB_Vector_t(A.D(),_ncols);
    _cols.resize(_ncols); for (GrB_Index j=0; j<_ncols; j++) _cols[j] = new GrB_Vector_t(A.D(),_nrows);
    for (GrB_Index i=0; i<_nrows; i++) _rows[i]->copy(A[i]);
    for (GrB_Index j=0; j<_ncols; j++) _cols[j]->copy(A(j));
    _nvals = A.nvals();

    return true;
}

bool GrB_Matrix_t::clear
(
)
{
    assert(!_copy);

    _nvals = 0;
    for (GrB_Index i=0; i<nrows(); i++) _rows[i]->clear();
    for (GrB_Index j=0; j<ncols(); j++) _cols[j]->clear();

    return true;
}

bool GrB_Matrix_t::init
(
   GrB_Type     D,
   GrB_Index    nrows,
   GrB_Index    ncols
)
{
    assert(!_copy);

    _valid = true;
    _copy = false;
    _D = D;
    _nrows = nrows;
    _ncols = ncols;
    _nvals = 0;
    _rows.resize(nrows); for (GrB_Index i=0; i<nrows; i++) _rows[i] = new GrB_Vector_t(D,ncols);
    _cols.resize(ncols); for (GrB_Index j=0; j<ncols; j++) _cols[j] = new GrB_Vector_t(D,nrows);
    return true;
}

bool GrB_Matrix_t::valid
(
) const
{
    return _valid;
}

GrB_Type GrB_Matrix_t::D
(
) const
{
    return _D;
}

GrB_Index GrB_Matrix_t::nrows
(
) const
{
    return _nrows;
}

GrB_Index GrB_Matrix_t::ncols
(
) const
{
    return _ncols;
}

GrB_Index GrB_Matrix_t::nvals
(
) const
{ 
    return _nvals;
}

bool GrB_Matrix_t::transpose
(
    const GrB_Matrix_t& A
)
{
    assert(!_copy);

    GrB_Index m = nrows();
    GrB_Index n = ncols();
    assert(n == A.nrows());
    assert(m == A.ncols());

    for (GrB_Index i=0; i<m; i++) _rows[i]->copy(A(i));
    for (GrB_Index j=0; j<n; j++) _cols[j]->copy(A[j]);

    return true;
}

#include "template/GrB_Matrix_t_AxB.cc"

bool GrB_Matrix_t::replace
(
    const GrB_Mask_t&   Mask,
    const GrB_Matrix_t& Matrix
)
{
    assert(!_copy);

    GrB_Index m = nrows();
    GrB_Index n = ncols();
    assert(m == Matrix.nrows());
    assert(m == Mask.nrows());
    assert(n == Matrix.ncols());
    assert(n == Mask.ncols());

    for (GrB_Index i = 0; i<m; i++) _rows[i]->replace(Mask[i],Matrix[i]);
    for (GrB_Index j = 0; j<n; j++) _cols[j]->replace(Mask(j),Matrix(j));
    _nvals = 0; for (GrB_Index i = 0; i<m; i++) _nvals += _rows[i]->size();

    return true;
}

bool GrB_Matrix_t::merge
(
    const GrB_Mask_t&   Mask,
    const GrB_Matrix_t& Matrix
)
{
    assert(!_copy);

    GrB_Index m = nrows();
    GrB_Index n = ncols();
    assert(m == Matrix.nrows());
    assert(m == Mask.nrows());
    assert(n == Matrix.ncols());
    assert(n == Mask.ncols());

    for (GrB_Index i = 0; i<m; i++) _rows[i]->merge(Mask[i],Matrix[i]);
    for (GrB_Index j = 0; j<n; j++) _cols[j]->merge(Mask(j),Matrix(j));
    _nvals = 0; for (GrB_Index i = 0; i<m; i++) _nvals += _rows[i]->size();

    return true;
}

bool GrB_Matrix_t::clear
(
    GrB_Index   i,
    GrB_Index   j
)
{
    assert(!_copy);

    assert(i < nrows());
    assert(j < ncols());

    if (_rows[i]->ind()->count(j))
    {
        _nvals--;
        _rows[i]->clear(j);
        _cols[j]->clear(i);
    }

    return true;
}

void GrB_Matrix_t::addElement
(
    GrB_Index                   i,
    GrB_Index                   j,
    const Scalar&               s,
    const GrB_BinaryOp_t&       dup
)
{
    assert(!_copy);

    assert(i < nrows());
    assert(j < ncols());

    _nvals += 1 - _rows[i]->ind()->count(j);
    _rows[i]->addElement(j,s,dup);
    _cols[j]->addElement(i,s,dup);
}

void GrB_Matrix_t::addElement
(
    GrB_Index           i,
    GrB_Index           j,
    const Scalar&       s
)
{
    assert(!_copy);

    assert(i < nrows());
    assert(j < ncols());

    clear(i,j);
    _nvals++;

    _rows[i]->addElement(j,s);
    _cols[j]->addElement(i,s);
}

const GrB_Vector_t& GrB_Matrix_t::operator[]
(
    GrB_Index i
) const
{
    return *(_rows[i]);
}

const GrB_Vector_t& GrB_Matrix_t::operator()
(
    GrB_Index j
) const
{
    return *(_cols[j]);
}

bool GrB_Matrix_t::mul
(
    const GrB_BinaryOp_t        *op,
    const GrB_Matrix_t&         A,
    const GrB_Matrix_t&         B
)
{
    assert(!_copy);

    for (GrB_Index i=0; i<nrows(); i++) _rows[i]->mul(op,A[i],B[i]);
    for (GrB_Index j=0; j<ncols(); j++) _cols[j]->mul(op,A(j),B(j));
    return true;
}

bool GrB_Matrix_t::mul
(
    const GrB_Monoid_t          *op,
    const GrB_Matrix_t&         A,
    const GrB_Matrix_t&         B
)
{
    assert(!_copy);

    for (GrB_Index i=0; i<nrows(); i++) _rows[i]->mul(op,A[i],B[i]);
    for (GrB_Index j=0; j<ncols(); j++) _cols[j]->mul(op,A(j),B(j));
    return true;
}

bool GrB_Matrix_t::mul
(
    const GrB_Semiring_t        *op,
    const GrB_Matrix_t&         A,
    const GrB_Matrix_t&         B
)
{
    assert(!_copy);

    for (GrB_Index i=0; i<nrows(); i++) _rows[i]->mul(op,A[i],B[i]);
    for (GrB_Index j=0; j<ncols(); j++) _cols[j]->mul(op,A(j),B(j));
    return true;
}

bool GrB_Matrix_t::add
(
    const GrB_BinaryOp_t        *op,
    const GrB_Matrix_t&         A,
    const GrB_Matrix_t&         B
)
{
    assert(!_copy);

    for (GrB_Index i=0; i<nrows(); i++) _rows[i]->add(op,A[i],B[i]);
    for (GrB_Index j=0; j<ncols(); j++) _cols[j]->add(op,A(j),B(j));
    return true;
}

bool GrB_Matrix_t::add
(
    const GrB_Monoid_t          *op,
    const GrB_Matrix_t&         A,
    const GrB_Matrix_t&         B
)
{
    assert(!_copy);

    for (GrB_Index i=0; i<nrows(); i++) _rows[i]->add(op,A[i],B[i]);
    for (GrB_Index j=0; j<ncols(); j++) _cols[j]->add(op,A(j),B(j));
    return true;
}

bool GrB_Matrix_t::add
(
    const GrB_Semiring_t        *op,
    const GrB_Matrix_t&         A,
    const GrB_Matrix_t&         B
)
{
    assert(!_copy);

    for (GrB_Index i=0; i<nrows(); i++) _rows[i]->add(op,A[i],B[i]);
    for (GrB_Index j=0; j<ncols(); j++) _cols[j]->add(op,A(j),B(j));
    return true;
}
