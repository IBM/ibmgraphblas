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

GrB_Info GrB_mxm
(
    GrB_Matrix              C,
    const GrB_Matrix        Mask,
    const GrB_BinaryOp      accum,
    const GrB_Semiring      op,
    const GrB_Matrix        A,
    const GrB_Matrix        B,
    const GrB_Descriptor    desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!C)     || (C     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (Mask  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!op)    || (op    == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!A)     || (A     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!B)     || (B     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (C     && (!C    ->valid())) return GrB_INVALID_OBJECT;
        if (Mask  && (!Mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (op    && (!op   ->valid())) return GrB_INVALID_OBJECT;
        if (A     && (!A    ->valid())) return GrB_INVALID_OBJECT;
        if (B     && (!B    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check domain conformity
        if (Mask  && (!Mask->D()->predefined())                ) return GrB_DOMAIN_MISMATCH;
        if (!A->D()->compatible(op->D_in_1())                  ) return GrB_DOMAIN_MISMATCH;
        if (!B->D()->compatible(op->D_in_2())                  ) return GrB_DOMAIN_MISMATCH;
        if (!C->D()->compatible(op->D_out())                   ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_in_1())     ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_out())      ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !op->D_out()->compatible(accum->D_in_2())) return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());
        bool tranA   = (desc && desc->inp0_tran());
        bool tranB   = (desc && desc->inp1_tran());

        // Prepare internal matrices for operation
        GrB_Matrix_t C_tilde(*C);
        GrB_Mask_t   M_tilde(SCMP,Mask,*C);
        GrB_Matrix_t A_tilde(tranA,*A);
        GrB_Matrix_t B_tilde(tranB,*B);

        // Check dimension comformity
        if (C_tilde.nrows() != M_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != M_tilde.ncols()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.nrows() != A_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != B_tilde.ncols()) return GrB_DIMENSION_MISMATCH;
        if (A_tilde.ncols() != B_tilde.nrows()) return GrB_DIMENSION_MISMATCH;

        // Perform the multiplication
        GrB_Matrix_t T_tilde(op->D_out(),A_tilde.nrows(),B_tilde.ncols());
        T_tilde.AxB(op,A_tilde,B_tilde);

        // Accumulate as necessary
        GrB_Matrix_t Z_tilde;
        accum ? Z_tilde.init(accum->D_out(),C_tilde.nrows(),C_tilde.ncols())
                && Z_tilde.add(accum,C_tilde,T_tilde)
              : Z_tilde.copy(T_tilde);

        // Mask and replace
        Replace ? C->replace(M_tilde,Z_tilde) : C->merge(M_tilde,Z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}
