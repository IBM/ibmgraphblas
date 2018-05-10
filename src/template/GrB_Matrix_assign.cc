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
GrB_Info GrB_Matrix_assign_common
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    const void                 *val,
    GrB_Type                    type,
    const GrB_Index            *row_indices,
    GrB_Index                   nrows,
    const GrB_Index            *col_indices,
    GrB_Index                   ncols,
    const GrB_Descriptor        desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!C)     || (C     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (Mask  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (C     && (!C    ->valid())) return GrB_INVALID_OBJECT;
        if (Mask  && (!Mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check for null pointers
        if (!row_indices) return GrB_NULL_POINTER;
        if (!col_indices) return GrB_NULL_POINTER;
        if (!val)         return GrB_NULL_POINTER;

        // Check domain conformity
        if (Mask  && (!Mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!C->D()->compatible(type))                           return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !type->compatible(accum->D_in_2()))        return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());

        // Prepare internal matrices for operation
        GrB_Matrix_t C_tilde(*C);
        GrB_Mask_t   M_tilde(SCMP,Mask,*C);

        // Check dimension comformity
        if (C_tilde.nrows() != M_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != M_tilde.ncols()) return GrB_DIMENSION_MISMATCH;
        if (nrows > C_tilde.nrows())            return GrB_DIMENSION_MISMATCH;
        if (ncols > C_tilde.ncols())            return GrB_DIMENSION_MISMATCH;

        // Create the assignment vector
        GrB_Matrix_t T_tilde(type, C_tilde.nrows(), C_tilde.ncols());
        Scalar value(type,val);
        for (GrB_Index i = 0; i<nrows; i++)
        {
            if (row_indices == GrB_ALL)
            {
                if (col_indices == GrB_ALL) for (GrB_Index j=0; j<ncols; j++) T_tilde.addElement(i,j,value);
                else for (GrB_Index j=0; j<ncols; j++) T_tilde.addElement(i,col_indices[j],value);
            }
            else
            {
                if (col_indices == GrB_ALL) for (GrB_Index j=0; j<ncols; j++) T_tilde.addElement(row_indices[i],j,value);
                else for (GrB_Index j=0; j<ncols; j++) T_tilde.addElement(row_indices[i],col_indices[j],value);
            }
        }
        
        // Accumulate as necessary
        GrB_Matrix_t Z_tilde;
        if (accum)
        {
            Z_tilde.init(accum->D_out(),C_tilde.nrows(),C_tilde.ncols());
            Z_tilde.add(accum,C_tilde,T_tilde);
        }
        else
        {
            Z_tilde.copy(C_tilde);
            for (GrB_Index i=0; i<Z_tilde.nrows(); i++)
                for (auto j : *(T_tilde[i].ind())) Z_tilde.addElement(i,j,T_tilde[i][j]);
        }

        // Mask and replace
        Replace ? C->replace(M_tilde,Z_tilde) : C->merge(M_tilde,Z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Matrix_assign_BOOL
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    bool                        val,
    const GrB_Index            *row_indices,
    GrB_Index                   nrows,
    const GrB_Index            *col_indices,
    GrB_Index                   ncols,
    const GrB_Descriptor        desc
)
{
    return GrB_Matrix_assign_common(C,Mask,accum,&val,GrB_BOOL,row_indices,nrows,col_indices,ncols,desc);
}

GrB_Info GrB_Matrix_assign_UDT
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    const void                 *val,
    const GrB_Index            *row_indices,
    GrB_Index                   nrows,
    const GrB_Index            *col_indices,
    GrB_Index                   ncols,
    const GrB_Descriptor        desc
)
{
    return GrB_Matrix_assign_common(C,Mask,accum,&val,C->D(),row_indices,nrows,col_indices,ncols,desc);
}
