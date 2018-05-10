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
GrB_Info GrB_Vector_reduce_common
(
    void                    *val,
    GrB_Type                type,
    const GrB_BinaryOp      accum,
    const GrB_Monoid        op,
    const GrB_Vector        u,
    const GrB_Descriptor    desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!val)                                   ) return GrB_NULL_POINTER;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!op)    || (op    == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!u)     || (u     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (op    && (!op   ->valid())) return GrB_INVALID_OBJECT;
        if (u     && (!u    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check domain conformity
        if (!u->D()->compatible(op->D())                   ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !type->compatible(accum->D_in_1())   ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !type->compatible(accum->D_out())    ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !op->D()->compatible(accum->D_in_2())) return GrB_DOMAIN_MISMATCH;
        if (!accum && !type->compatible(op->D())           ) return GrB_DOMAIN_MISMATCH;

        // Perform the reduction
        Scalar sum = op->zero();
        for (auto k : *(u->ind()))
        {
            Scalar a = (*u)[k];
            op->f(sum,sum,a(op->D()));
        }

        // Compute final result
        if (accum)
        {
            Scalar v(type,val);
            Scalar final(accum->D_out());
            accum->f(final,v(accum->D_in_1()),sum(accum->D_in_2()));
            memcpy(val,final(type),type->size());
        }
        else
        {
            memcpy(val,sum(type),type->size());
        }

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Vector_reduce_BOOL
(
    bool                   *val,
    const GrB_BinaryOp      accum,
    const GrB_Monoid        op,
    const GrB_Vector        u,
    const GrB_Descriptor    desc
)
{
    return GrB_Vector_reduce_common(val,GrB_BOOL,accum,op,u,desc);
}

GrB_Info GrB_Vector_reduce_INT8
(
    int8_t                 *val,
    const GrB_BinaryOp      accum,
    const GrB_Monoid        op,
    const GrB_Vector        u,
    const GrB_Descriptor    desc
)
{
    return GrB_Vector_reduce_common(val,GrB_INT8,accum,op,u,desc);
}

GrB_Info GrB_Vector_reduce_UINT8
(
    uint8_t                *val,
    const GrB_BinaryOp      accum,
    const GrB_Monoid        op,
    const GrB_Vector        u,
    const GrB_Descriptor    desc
)
{
    return GrB_Vector_reduce_common(val,GrB_UINT8,accum,op,u,desc);
}

GrB_Info GrB_Vector_reduce_INT16
(
    int16_t                *val,
    const GrB_BinaryOp      accum,
    const GrB_Monoid        op,
    const GrB_Vector        u,
    const GrB_Descriptor    desc
)
{
    return GrB_Vector_reduce_common(val,GrB_INT16,accum,op,u,desc);
}

GrB_Info GrB_Vector_reduce_UINT16
(
    uint16_t               *val,
    const GrB_BinaryOp      accum,
    const GrB_Monoid        op,
    const GrB_Vector        u,
    const GrB_Descriptor    desc
)
{
    return GrB_Vector_reduce_common(val,GrB_UINT16,accum,op,u,desc);
}

GrB_Info GrB_Vector_reduce_INT32
(
    int32_t                *val,
    const GrB_BinaryOp      accum,
    const GrB_Monoid        op,
    const GrB_Vector        u,
    const GrB_Descriptor    desc
)
{
    return GrB_Vector_reduce_common(val,GrB_INT32,accum,op,u,desc);
}

GrB_Info GrB_Vector_reduce_UINT32
(
    uint32_t               *val,
    const GrB_BinaryOp      accum,
    const GrB_Monoid        op,
    const GrB_Vector        u,
    const GrB_Descriptor    desc
)
{
    return GrB_Vector_reduce_common(val,GrB_UINT32,accum,op,u,desc);
}

GrB_Info GrB_Vector_reduce_INT64
(
    int64_t                *val,
    const GrB_BinaryOp      accum,
    const GrB_Monoid        op,
    const GrB_Vector        u,
    const GrB_Descriptor    desc
)
{
    return GrB_Vector_reduce_common(val,GrB_INT64,accum,op,u,desc);
}

GrB_Info GrB_Vector_reduce_UINT64
(
    uint64_t               *val,
    const GrB_BinaryOp      accum,
    const GrB_Monoid        op,
    const GrB_Vector        u,
    const GrB_Descriptor    desc
)
{
    return GrB_Vector_reduce_common(val,GrB_UINT64,accum,op,u,desc);
}

GrB_Info GrB_Vector_reduce_FP32
(
    float                  *val,
    const GrB_BinaryOp      accum,
    const GrB_Monoid        op,
    const GrB_Vector        u,
    const GrB_Descriptor    desc
)
{
    return GrB_Vector_reduce_common(val,GrB_FP32,accum,op,u,desc);
}

GrB_Info GrB_Vector_reduce_FP64
(
    double                 *val,
    const GrB_BinaryOp      accum,
    const GrB_Monoid        op,
    const GrB_Vector        u,
    const GrB_Descriptor    desc
)
{
    return GrB_Vector_reduce_common(val,GrB_FP64,accum,op,u,desc);
}

GrB_Info GrB_Vector_reduce_UDT
(
    void                   *val,
    const GrB_BinaryOp      accum,
    const GrB_Monoid        op,
    const GrB_Vector        u,
    const GrB_Descriptor    desc
)
{
    if ((!u)     || (u     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
    return GrB_Vector_reduce_common(val,u->D(),accum,op,u,desc);
}
