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
GrB_Info GrB_Vector_assign_common
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const void                 *val,
    GrB_Type                    type,
    const GrB_Index            *indices,
    GrB_Index                   nindices,
    const GrB_Descriptor        desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!w)     || (w     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (mask  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (w     && (!w    ->valid())) return GrB_INVALID_OBJECT;
        if (mask  && (!mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check for null pointers
        if (!indices) return GrB_NULL_POINTER;
        if (!val)     return GrB_NULL_POINTER;

        // Check domain conformity
        if (mask  && (!mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!w->D()->compatible(type))                           return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !type->compatible(accum->D_in_2()))        return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());

        // Prepare internal vectors for operation
        GrB_Vector_t w_tilde(*w);
        GrB_mask_t   m_tilde(SCMP,mask,*w);

        // Check dimension comformity
        if (w_tilde.size() != m_tilde.size()) return GrB_DIMENSION_MISMATCH;
        if (nindices > w_tilde.size())        return GrB_DIMENSION_MISMATCH;

        // Create the assignment vector
        GrB_Vector_t t_tilde(type, w_tilde.size());
        Scalar value(type,val);
        if (indices == GrB_ALL) for (GrB_Index i = 0; i<nindices; i++) t_tilde.addElement(i,value);
        else for (GrB_Index i = 0; i<nindices; i++) t_tilde.addElement(indices[i],value);
        
        // Accumulate as necessary
        GrB_Vector_t z_tilde;
        if (accum)
        {
            z_tilde.init(accum->D_out(),w_tilde.size());
            z_tilde.add(accum,w_tilde,t_tilde);
        }
        else
        {
            z_tilde.copy(w_tilde);
            for (auto i : *(t_tilde.ind())) { z_tilde.clear(i); z_tilde.addElement(i,t_tilde[i](z_tilde.D())); }
        }

        // Mask and replace
        Replace ? w->replace(m_tilde,z_tilde) : w->merge(m_tilde,z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Vector_assign_BOOL
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    bool                        val,
    const GrB_Index            *indices,
    GrB_Index                   nindices,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_assign_common(w,mask,accum,&val,GrB_BOOL,indices,nindices,desc);
}

GrB_Info GrB_Vector_assign_INT8
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    int8_t                      val,
    const GrB_Index            *indices,
    GrB_Index                   nindices,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_assign_common(w,mask,accum,&val,GrB_INT8,indices,nindices,desc);
}

GrB_Info GrB_Vector_assign_UINT8
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    uint8_t                     val,
    const GrB_Index            *indices,
    GrB_Index                   nindices,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_assign_common(w,mask,accum,&val,GrB_UINT8,indices,nindices,desc);
}

GrB_Info GrB_Vector_assign_INT16
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    int16_t                     val,
    const GrB_Index            *indices,
    GrB_Index                   nindices,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_assign_common(w,mask,accum,&val,GrB_INT16,indices,nindices,desc);
}

GrB_Info GrB_Vector_assign_UINT16
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    uint16_t                    val,
    const GrB_Index            *indices,
    GrB_Index                   nindices,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_assign_common(w,mask,accum,&val,GrB_UINT16,indices,nindices,desc);
}

GrB_Info GrB_Vector_assign_INT32
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    int32_t                     val,
    const GrB_Index            *indices,
    GrB_Index                   nindices,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_assign_common(w,mask,accum,&val,GrB_INT32,indices,nindices,desc);
}

GrB_Info GrB_Vector_assign_UINT32
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    uint32_t                    val,
    const GrB_Index            *indices,
    GrB_Index                   nindices,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_assign_common(w,mask,accum,&val,GrB_UINT32,indices,nindices,desc);
}

GrB_Info GrB_Vector_assign_INT64
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    int64_t                     val,
    const GrB_Index            *indices,
    GrB_Index                   nindices,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_assign_common(w,mask,accum,&val,GrB_INT64,indices,nindices,desc);
}

GrB_Info GrB_Vector_assign_UINT64
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    uint64_t                    val,
    const GrB_Index            *indices,
    GrB_Index                   nindices,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_assign_common(w,mask,accum,&val,GrB_UINT64,indices,nindices,desc);
}

GrB_Info GrB_Vector_assign_FP32
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    float                       val,
    const GrB_Index            *indices,
    GrB_Index                   nindices,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_assign_common(w,mask,accum,&val,GrB_FP32,indices,nindices,desc);
}

GrB_Info GrB_Vector_assign_FP64
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    double                      val,
    const GrB_Index            *indices,
    GrB_Index                   nindices,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_assign_common(w,mask,accum,&val,GrB_FP64,indices,nindices,desc);
}

GrB_Info GrB_Vector_assign_UDT
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const void                 *val,
    const GrB_Index            *indices,
    GrB_Index                   nindices,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_assign_common(w,mask,accum,&val,w->D(),indices,nindices,desc);
}
