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
#include <iostream>

GrB_Vector_t::GrB_Vector_t
(
)
{
    _valid = false;
}

GrB_Vector_t::GrB_Vector_t
(
    const GrB_Vector_t& u
)
{
    _valid = true;
    _D = u.D();
    _size = u.size();
    _ind = new uset<GrB_Index>(_size);
    _map = new umap<GrB_Index,void*>;
    for (auto it : *u._map)
    {
        _ind->insert(it.first);
        (*_map)[it.first] = D()->clone(it.second,u.D());
    }
}

GrB_Vector_t::GrB_Vector_t
(
    GrB_Type    D,
    GrB_Index   size
)
{
    _valid = true;
    _D = D;
    _size = size;
    _ind = new uset<GrB_Index>(_size);
    _map = new umap<GrB_Index,void*>;
}

GrB_Vector_t::~GrB_Vector_t
(
)
{
    for (auto it = _map->begin(); it != _map->end(); ++it)
    {
        free(it->second);
    }
    delete _map;
    delete _ind;
}

bool GrB_Vector_t::valid
(
) const
{
    return _valid;
}

GrB_Index GrB_Vector_t::nvals
(
) const
{ 
    return _ind->size();
}

GrB_Index GrB_Vector_t::size
(
) const
{
    return _size;
}

bool GrB_Vector_t::clear
(
)
{
    if (!_valid) return false;
    for (auto it = _map->begin(); it != _map->end(); ++it)
    {
        free(it->second);
    }
    delete _map;
    delete _ind;
    _ind = new uset<GrB_Index>(_size);
    _map = new umap<GrB_Index,void*>;
    return true;
}

bool GrB_Vector_t::clear
(
    GrB_Index i
)
{
    if (ind()->count(i))
    {
        _ind->erase(i);
        _map->erase(i);
    }
    return true;
}

GrB_Type GrB_Vector_t::D
(
) const
{
    return _D;
}

const uset<GrB_Index>   *GrB_Vector_t::ind
(
) const
{
    return _ind;
}

const umap<GrB_Index,void*>     *GrB_Vector_t::map
(
) const
{
    return _map;
}

void GrB_Vector_t::addElement
(
    GrB_Index                   i,
    const Scalar&               x,
    const GrB_BinaryOp_t&       dup
)
{
    void *y = D()->clone(x,x.D());
    if (_ind->count(i)) 
    {
        dup.f(_map->at(i),_map->at(i),y);
        free(y);
    }
    else
    {
        (*_map)[i] = y;
        _ind->insert(i);
    }
}

void GrB_Vector_t::addElement
(
    GrB_Index           i,
    const Scalar&       s
)
{
    assert(D() == s.D());
    assert(_ind->count(i) == 0);

    void *y = D()->clone(s,s.D());
    (*_map)[i] = y;
    _ind->insert(i);
}

bool GrB_Vector_t::copy
(
    const GrB_Vector_t &u
)
{
    if (_valid)
    {
        clear();
        _size = u.size();
        _D = u.D();
    }
    else
    {
        _valid = true;
        _D = u.D();
        _size = u.size();
        _ind = new uset<GrB_Index>(_size);
        _map = new umap<GrB_Index,void*>;
    }
    for (auto it : *u._map)
    {
        _ind->insert(it.first);
        (*_map)[it.first] = D()->clone(it.second,u.D());
    }

    return true;
}

bool GrB_Vector_t::replace
(
    const GrB_mask_t&   mask,
    const GrB_Vector_t& Vector
)
{
    assert(size() == mask.size());
    assert(size() == Vector.size());

    clear();
    if (mask.full())
    {
        // full mask - write all elements from vector
        for (auto i : (*Vector.ind())) addElement(i,Vector[i](D()));
    }
    else
    {
        // partial mask - write only those elements according to mask
        for (auto i : (*mask.ind()) * (*Vector.ind())) addElement(i,Vector[i](D()));
    }

    return true;
}

bool GrB_Vector_t::merge
(
    const GrB_mask_t&   mask,
    const GrB_Vector_t& Vector
)
{
    assert(size() == mask.size());
    assert(size() == Vector.size());

    if (mask.full())
    {
        // full mask - erase all elements and replace with new vector
        clear();
        for (auto i : (*Vector.ind())) addElement(i,Vector[i](D()));
    }
    else
    {
        // partial mask - replace only those elements according to mask
        for (auto i : (*mask.ind())) clear(i);
        for (auto i : (*mask.ind()) * (*Vector.ind())) addElement(i,Vector[i](D()));
    }

    return true;
}

bool GrB_Vector_t::add
(
    const GrB_BinaryOp_t        *op,
    const GrB_Vector_t&         u,
    const GrB_Vector_t&         v
)
{
    clear();
    uset<GrB_Index> intersection = (*(u.ind())) * (*(v.ind()));
    Scalar axb(op->D_out());
    for (auto k : intersection)
    {
        op->f(axb,u[k](op->D_in_1()),v[k](op->D_in_2()));
        addElement(k,axb(D()));
    }
    for (auto k : *(u.ind()) - intersection) addElement(k,u[k](D()));
    for (auto k : *(v.ind()) - intersection) addElement(k,v[k](D()));
    return true;
}

bool GrB_Vector_t::add
(
    const GrB_Monoid_t          *op,
    const GrB_Vector_t&         u,
    const GrB_Vector_t&         v
)
{
    clear();
    uset<GrB_Index> intersection = (*(u.ind())) * (*(v.ind()));
    Scalar axb(op->D_out());
    for (auto k : intersection)
    {
        op->f(axb,u[k](op->D_in_1()),v[k](op->D_in_2()));
        addElement(k,axb(D()));
    }
    for (auto k : *(u.ind()) - intersection) addElement(k,u[k](D()));
    for (auto k : *(v.ind()) - intersection) addElement(k,v[k](D()));
    return true;
}

bool GrB_Vector_t::add
(
    const GrB_Semiring_t        *op,
    const GrB_Vector_t&         u,
    const GrB_Vector_t&         v
)
{
    clear();
    uset<GrB_Index> intersection = (*(u.ind())) * (*(v.ind()));
    Scalar axb(op->D_out());
    for (auto k : intersection)
    {
        op->add(axb,u[k](op->D_in_1()),v[k](op->D_in_2()));
        addElement(k,axb(D()));
    }
    for (auto k : *(u.ind()) - intersection) addElement(k,u[k](D()));
    for (auto k : *(v.ind()) - intersection) addElement(k,v[k](D()));
    return true;
}

bool GrB_Vector_t::mul
(
    const GrB_BinaryOp_t        *op,
    const GrB_Vector_t&         u,
    const GrB_Vector_t&         v
)
{
    clear();
    uset<GrB_Index> intersection = (*(u.ind())) * (*(v.ind()));
    Scalar axb(op->D_out());
    for (auto k : intersection)
    {
        op->f(axb,u[k](op->D_in_1()),v[k](op->D_in_2()));
        addElement(k,axb(D()));
    }
    return true;
}

bool GrB_Vector_t::mul
(
    const GrB_Monoid_t          *op,
    const GrB_Vector_t&         u,
    const GrB_Vector_t&         v
)
{
    clear();
    uset<GrB_Index> intersection = (*(u.ind())) * (*(v.ind()));
    Scalar axb(op->D_out());
    for (auto k : intersection)
    {
        op->f(axb,u[k](op->D_in_1()),v[k](op->D_in_2()));
        addElement(k,axb(D()));
    }
    return true;
}

bool GrB_Vector_t::mul
(
    const GrB_Semiring_t        *op,
    const GrB_Vector_t&         u,
    const GrB_Vector_t&         v
)
{
    clear();
    uset<GrB_Index> intersection = (*(u.ind())) * (*(v.ind()));
    Scalar axb(op->D_out());
    for (auto k : intersection)
    {
        op->mul(axb,u[k](op->D_in_1()),v[k](op->D_in_2()));
        addElement(k,axb(D()));
    }
    return true;
}

bool GrB_Vector_t::init
(
   GrB_Type     D,
   GrB_Index    size
)
{
    _valid = true;
    _D = D;
    _size = size;
    _ind = new uset<GrB_Index>(_size);
    _map = new umap<GrB_Index,void*>;

    return true;
}

Scalar GrB_Vector_t::operator[]
(
    GrB_Index   i
) const
{
    Scalar a(_D,_map->at(i));
    return a;
}

static
void dot_product
(
    Scalar&                     sum,
    const GrB_Semiring          S,
    const GrB_Vector_t&         u,
    const GrB_Vector_t&         v,
    const uset<GrB_Index>&      intersect
)
{
    Scalar axb = S->zero();
    if ((S->D_in_1() == u.D()) && (S->D_in_2() == v.D()))
    {
        for (auto k : intersect)
        {
            S->mul(axb,u.map()->at(k),v.map()->at(k));
            S->add(sum,sum,axb);
        }
    }
    else
    {
        for (auto k : intersect)
        {
            S->mul(axb,u[k](S->D_in_1()),v[k](S->D_in_2()));
            S->add(sum,sum,axb);
        }
    }
}

void GrB_Vector_t::Axb
(
    const GrB_Semiring  S,
    const GrB_Matrix_t& A,
    const GrB_Vector_t& b
)
{
    GrB_Index m = A.nrows();
    GrB_Index n = b.size();
    assert(n == A.ncols());

    clear();
    for (GrB_Index i = 0; i<m; i++)
    {
        uset<GrB_Index> Intersect(n);
        const uset<GrB_Index> *intersect;
        if      (A[i].ind()->size() == n) { intersect = b.ind(); }
        else if (b.ind()->size() == n)    { intersect = A[i].ind(); }
        else                              { Intersect = (*(A[i].ind())) * (*(b.ind())); intersect = &Intersect; }
        if (intersect->empty()) continue;
        Scalar sum = S->zero();
        dot_product(sum,S,A[i],b,*intersect);
        addElement(i,sum(D()));
    }
}

void GrB_Vector_t::axB
(
    const GrB_Semiring  S,
    const GrB_Vector_t& a,
    const GrB_Matrix_t& B
)
{
    GrB_Index m = a.size();
    GrB_Index n = B.ncols();
    assert(m == B.nrows());

    clear();
    for (GrB_Index j = 0; j<n; j++)
    {
        uset<GrB_Index> Intersect(m);
        const uset<GrB_Index> *intersect;
        if      (a.ind()->size() == m)    { intersect = B(j).ind(); }
        else if (B(j).ind()->size() == m) { intersect = a.ind(); }
        else                              { Intersect = (*(a.ind())) * (*(B(j).ind())); intersect = &Intersect; }
        if (intersect->empty()) continue;
        Scalar sum = S->zero();
        dot_product(sum,S,a,B(j),*intersect);
        addElement(j,sum(D()));
    }
}
