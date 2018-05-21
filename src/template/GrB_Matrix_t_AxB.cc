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

void GrB_Matrix_t::AxB
(
    const GrB_Semiring  S,
    const GrB_Matrix_t& A,
    const GrB_Matrix_t& B
)
{
    GrB_Index m = A.nrows();
    GrB_Index n = B.ncols();
    GrB_Index p = A.ncols(); assert(p == B.nrows());

    clear();
    for (GrB_Index i = 0; i<m; i++)
    {
        for (GrB_Index j = 0; j<n; j++)
        {
            uset<GrB_Index> Intersect(p);
            const uset<GrB_Index> *intersect;
            if      (A[i].ind()->size() == p) { intersect = B(j).ind(); }
            else if (B(j).ind()->size() == p) { intersect = A[i].ind(); }
            else                              { Intersect = (*(A[i].ind())) * (*(B(j).ind())); intersect = &Intersect; }
            if (intersect->empty()) continue;
            Scalar sum = S->zero();
            dot_product(sum,S,A[i],B(j),*intersect);
            addElement(i,j,sum(D()));
        }
    }
}
