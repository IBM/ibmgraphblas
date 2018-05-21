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
#include <iostream>

template<>
GrB_Index       uset<GrB_Index>::capacity
(
) const
{
    return _capacity;
}

template<>
uset<GrB_Index>::~uset
(
)
{
}

template<>
bool uset<GrB_Index>::full
(
) const
{
    return (_capacity == size());
}

template<>
uset<GrB_Index>::uset
(
    GrB_Index  N
) : std::unordered_set<GrB_Index>()
{
    _capacity = N;
}

void            *const GrB_NULL           = 0;
const GrB_Index *const GrB_ALL            = (const GrB_Index*)-1;
void            *const GrB_INVALID_HANDLE = (void*)-2;

// Section 2.5 Domains

GrB_Type        GrB_BOOL   = (GrB_Type)GrB_INVALID_HANDLE;
GrB_Type        GrB_INT8   = (GrB_Type)GrB_INVALID_HANDLE;
GrB_Type        GrB_UINT8  = (GrB_Type)GrB_INVALID_HANDLE;
GrB_Type        GrB_INT16  = (GrB_Type)GrB_INVALID_HANDLE;
GrB_Type        GrB_UINT16 = (GrB_Type)GrB_INVALID_HANDLE;
GrB_Type        GrB_INT32  = (GrB_Type)GrB_INVALID_HANDLE;
GrB_Type        GrB_UINT32 = (GrB_Type)GrB_INVALID_HANDLE;
GrB_Type        GrB_INT64  = (GrB_Type)GrB_INVALID_HANDLE;
GrB_Type        GrB_UINT64 = (GrB_Type)GrB_INVALID_HANDLE;
GrB_Type        GrB_FP32   = (GrB_Type)GrB_INVALID_HANDLE;
GrB_Type        GrB_FP64   = (GrB_Type)GrB_INVALID_HANDLE;

// Section 2.6 Operators and Associated Functions

GrB_UnaryOp     GrB_LNOT         = (GrB_UnaryOp )GrB_INVALID_HANDLE;
GrB_BinaryOp    GrB_LAND         = (GrB_BinaryOp)GrB_INVALID_HANDLE;
GrB_BinaryOp    GrB_LOR          = (GrB_BinaryOp)GrB_INVALID_HANDLE;
GrB_BinaryOp    GrB_LXOR         = (GrB_BinaryOp)GrB_INVALID_HANDLE;

#define Instantiate(TYPE)                                                       \
GrB_UnaryOp      GrB_IDENTITY_ ## TYPE  = (GrB_UnaryOp )GrB_INVALID_HANDLE;     \
GrB_UnaryOp      GrB_AINV_ ## TYPE      = (GrB_UnaryOp )GrB_INVALID_HANDLE;     \
GrB_UnaryOp      GrB_MINV_ ## TYPE      = (GrB_UnaryOp )GrB_INVALID_HANDLE;     \
GrB_BinaryOp     GrB_EQ_ ## TYPE        = (GrB_BinaryOp)GrB_INVALID_HANDLE;     \
GrB_BinaryOp     GrB_NE_ ## TYPE        = (GrB_BinaryOp)GrB_INVALID_HANDLE;     \
GrB_BinaryOp     GrB_GT_ ## TYPE        = (GrB_BinaryOp)GrB_INVALID_HANDLE;     \
GrB_BinaryOp     GrB_LT_ ## TYPE        = (GrB_BinaryOp)GrB_INVALID_HANDLE;     \
GrB_BinaryOp     GrB_GE_ ## TYPE        = (GrB_BinaryOp)GrB_INVALID_HANDLE;     \
GrB_BinaryOp     GrB_LE_ ## TYPE        = (GrB_BinaryOp)GrB_INVALID_HANDLE;     \
GrB_BinaryOp     GrB_FIRST_ ## TYPE     = (GrB_BinaryOp)GrB_INVALID_HANDLE;     \
GrB_BinaryOp     GrB_SECOND_ ## TYPE    = (GrB_BinaryOp)GrB_INVALID_HANDLE;     \
GrB_BinaryOp     GrB_MIN_ ## TYPE       = (GrB_BinaryOp)GrB_INVALID_HANDLE;     \
GrB_BinaryOp     GrB_MAX_ ## TYPE       = (GrB_BinaryOp)GrB_INVALID_HANDLE;     \
GrB_BinaryOp     GrB_PLUS_ ## TYPE      = (GrB_BinaryOp)GrB_INVALID_HANDLE;     \
GrB_BinaryOp     GrB_MINUS_ ## TYPE     = (GrB_BinaryOp)GrB_INVALID_HANDLE;     \
GrB_BinaryOp     GrB_TIMES_ ## TYPE     = (GrB_BinaryOp)GrB_INVALID_HANDLE;     \
GrB_BinaryOp     GrB_DIV_ ## TYPE       = (GrB_BinaryOp)GrB_INVALID_HANDLE;

Instantiate(BOOL)
Instantiate(INT8)
Instantiate(UINT8)
Instantiate(INT16)
Instantiate(UINT16)
Instantiate(INT32)
Instantiate(UINT32)
Instantiate(INT64)
Instantiate(UINT64)
Instantiate(FP32)
Instantiate(FP64)

#undef Instantiate

static void GrB_LNOT_F        (void* z, const void* x)
{
    assert(z); assert(x);
    *((bool*)z) = ! *((const bool*)x);
}

static void GrB_LAND_F        (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((bool*)z) = *((const bool*)x) && *((const bool*)y);
}

static void GrB_LOR_F         (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((bool*)z) = *((const bool*)x) || *((const bool*)y);
}

static void GrB_LXOR_F        (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((bool*)z) = *((const bool*)x) ^ *((const bool*)y);
}

template<class T> static void GrB_IDENTITY_F(void *z, const void *x)
{
    assert(z); assert(x);
    *((T*)z) = *((const T*)x);
}

template<class T> static void GrB_AINV_F(void *z, const void *x)
{
    assert(z); assert(x);
    *((T*)z) = - *((const T*)x);
}

template<class T> static void GrB_MINV_F(void *z, const void *x)
{
    assert(z); assert(x);
    *((T*)z) = 1.0f / *((const T*)x);
}

template<class T> static void GrB_EQ_F      (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((bool*)z) = *((const T*)x) == *((const T*)y);
}

template<class T> static void GrB_NE_F      (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((bool*)z) = *((const T*)x) != *((const T*)y);
}

template<class T> static void GrB_GT_F      (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((bool*)z) = *((const T*)x) > *((const T*)y);
}

template<class T> static void GrB_LT_F      (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((bool*)z) = *((const T*)x) < *((const T*)y);
}

template<class T> static void GrB_GE_F      (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((bool*)z) = *((const T*)x) >= *((const T*)y);
}

template<class T> static void GrB_LE_F      (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((bool*)z) = *((const T*)x) <= *((const T*)y);
}

template<class T> static void GrB_FIRST_F   (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((T*)z) = *((const T*)x);
}

template<class T> static void GrB_SECOND_F  (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((T*)z) = *((const T*)y);
}

template<class T> static void GrB_MAX_F  (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((T*)z) = (*((const T*)x) > *((const T*)y)) ? *((const T*)x) : *((const T*)y);
}

template<class T> static void GrB_MIN_F  (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((T*)z) = (*((const T*)x) < *((const T*)y)) ? *((const T*)x) : *((const T*)y);
}

template<class T> static void GrB_PLUS_F  (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((T*)z) = *((const T*)x) + *((const T*)y);
}

template<class T> static void GrB_MINUS_F  (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((T*)z) = *((const T*)x) - *((const T*)y);
}

template<class T> static void GrB_TIMES_F  (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((T*)z) = *((const T*)x) * *((const T*)y);
}

template<class T> static void GrB_DIV_F  (void* z, const void* x, const void* y)
{
    assert(z); assert(x); assert(y);
    *((T*)z) = *((const T*)x) / *((const T*)y);
}

// Section 4.1.1 init

#define Initialize(type,TYPE)                                                                                                                           \
    if (GrB_SUCCESS != GrB_UnaryOp_new (&GrB_IDENTITY_ ## TYPE, GrB_IDENTITY_F<type>, GrB_ ## TYPE , GrB_ ## TYPE            )) return GrB_PANIC;       \
    if (GrB_SUCCESS != GrB_UnaryOp_new (&GrB_AINV_ ## TYPE    , GrB_AINV_F<type>    , GrB_ ## TYPE , GrB_ ## TYPE            )) return GrB_PANIC;       \
    if (GrB_SUCCESS != GrB_UnaryOp_new (&GrB_MINV_ ## TYPE    , GrB_MINV_F<type>    , GrB_ ## TYPE , GrB_ ## TYPE            )) return GrB_PANIC;       \
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_EQ_ ## TYPE      , GrB_EQ_F<type>      , GrB_BOOL , GrB_ ## TYPE , GrB_ ## TYPE )) return GrB_PANIC;       \
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_NE_ ## TYPE      , GrB_NE_F<type>      , GrB_BOOL , GrB_ ## TYPE , GrB_ ## TYPE )) return GrB_PANIC;       \
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_GT_ ## TYPE      , GrB_GT_F<type>      , GrB_BOOL , GrB_ ## TYPE , GrB_ ## TYPE )) return GrB_PANIC;       \
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_LT_ ## TYPE      , GrB_LT_F<type>      , GrB_BOOL , GrB_ ## TYPE , GrB_ ## TYPE )) return GrB_PANIC;       \
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_GE_ ## TYPE      , GrB_GE_F<type>      , GrB_BOOL , GrB_ ## TYPE , GrB_ ## TYPE )) return GrB_PANIC;       \
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_LE_ ## TYPE      , GrB_LE_F<type>      , GrB_BOOL , GrB_ ## TYPE , GrB_ ## TYPE )) return GrB_PANIC;       \
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_FIRST_ ## TYPE   , GrB_FIRST_F<type>   , GrB_ ## TYPE , GrB_ ## TYPE , GrB_ ## TYPE )) return GrB_PANIC;   \
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_SECOND_ ## TYPE  , GrB_SECOND_F<type>  , GrB_ ## TYPE , GrB_ ## TYPE , GrB_ ## TYPE )) return GrB_PANIC;   \
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_MIN_ ## TYPE     , GrB_MIN_F<type>     , GrB_ ## TYPE , GrB_ ## TYPE , GrB_ ## TYPE )) return GrB_PANIC;   \
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_MAX_ ## TYPE     , GrB_MAX_F<type>     , GrB_ ## TYPE , GrB_ ## TYPE , GrB_ ## TYPE )) return GrB_PANIC;   \
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_PLUS_ ## TYPE    , GrB_PLUS_F<type>    , GrB_ ## TYPE , GrB_ ## TYPE , GrB_ ## TYPE )) return GrB_PANIC;   \
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_MINUS_ ## TYPE   , GrB_MINUS_F<type>   , GrB_ ## TYPE , GrB_ ## TYPE , GrB_ ## TYPE )) return GrB_PANIC;   \
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_TIMES_ ## TYPE   , GrB_TIMES_F<type>   , GrB_ ## TYPE , GrB_ ## TYPE , GrB_ ## TYPE )) return GrB_PANIC;   \
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_DIV_ ## TYPE     , GrB_DIV_F<type>     , GrB_ ## TYPE , GrB_ ## TYPE , GrB_ ## TYPE )) return GrB_PANIC;

GrB_Info GrB_init
(
    GrB_Mode    mode
)
{
    // Create default types
    if ((GrB_BOOL   = new Type<bool    >()) == 0) return GrB_PANIC;
    if ((GrB_INT8   = new Type<int8_t  >()) == 0) return GrB_PANIC;
    if ((GrB_UINT8  = new Type<uint8_t >()) == 0) return GrB_PANIC;
    if ((GrB_INT16  = new Type<int16_t >()) == 0) return GrB_PANIC;
    if ((GrB_UINT16 = new Type<uint16_t>()) == 0) return GrB_PANIC;
    if ((GrB_INT32  = new Type<int32_t >()) == 0) return GrB_PANIC;
    if ((GrB_UINT32 = new Type<uint32_t>()) == 0) return GrB_PANIC;
    if ((GrB_INT64  = new Type<int64_t >()) == 0) return GrB_PANIC;
    if ((GrB_UINT64 = new Type<uint64_t>()) == 0) return GrB_PANIC;
    if ((GrB_FP32   = new Type<float   >()) == 0) return GrB_PANIC;
    if ((GrB_FP64   = new Type<double  >()) == 0) return GrB_PANIC;

    // Create default unary/binary ops
    if (GrB_SUCCESS != GrB_UnaryOp_new (&GrB_LNOT, GrB_LNOT_F, GrB_BOOL, GrB_BOOL           )) return GrB_PANIC;
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_LAND, GrB_LAND_F, GrB_BOOL, GrB_BOOL, GrB_BOOL)) return GrB_PANIC;
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_LOR , GrB_LOR_F , GrB_BOOL, GrB_BOOL, GrB_BOOL)) return GrB_PANIC;
    if (GrB_SUCCESS != GrB_BinaryOp_new(&GrB_LXOR, GrB_LXOR_F, GrB_BOOL, GrB_BOOL, GrB_BOOL)) return GrB_PANIC;

    Initialize(bool  ,BOOL)
    Initialize(int8_t ,INT8)
    Initialize(uint8_t ,UINT8)
    Initialize(int16_t,INT16)
    Initialize(uint16_t,UINT16)
    Initialize(int32_t ,INT32)
    Initialize(uint32_t ,UINT32)
    Initialize(int64_t,INT64)
    Initialize(uint64_t,UINT64)
    Initialize(float ,FP32)
    Initialize(double,FP64)

    return GrB_SUCCESS;
}

#undef Initialize

// Section 4.1.2 finalize

#define Finalize(TYPE)                          \
    GrB_BinaryOp_free(&GrB_DIV_ ## TYPE     );  \
    GrB_BinaryOp_free(&GrB_TIMES_ ## TYPE   );  \
    GrB_BinaryOp_free(&GrB_MINUS_ ## TYPE   );  \
    GrB_BinaryOp_free(&GrB_PLUS_ ## TYPE    );  \
    GrB_BinaryOp_free(&GrB_MAX_ ## TYPE     );  \
    GrB_BinaryOp_free(&GrB_MIN_ ## TYPE     );  \
    GrB_BinaryOp_free(&GrB_SECOND_ ## TYPE  );  \
    GrB_BinaryOp_free(&GrB_FIRST_ ## TYPE   );  \
    GrB_BinaryOp_free(&GrB_LE_ ## TYPE      );  \
    GrB_BinaryOp_free(&GrB_GE_ ## TYPE      );  \
    GrB_BinaryOp_free(&GrB_LT_ ## TYPE      );  \
    GrB_BinaryOp_free(&GrB_GT_ ## TYPE      );  \
    GrB_BinaryOp_free(&GrB_NE_ ## TYPE      );  \
    GrB_BinaryOp_free(&GrB_EQ_ ## TYPE      );  \
    GrB_UnaryOp_free (&GrB_MINV_ ## TYPE    );  \
    GrB_UnaryOp_free (&GrB_AINV_ ## TYPE    );  \
    GrB_UnaryOp_free (&GrB_IDENTITY_ ## TYPE);

GrB_Info GrB_finalize
(
)
{
    GrB_UnaryOp_free (&GrB_LNOT        );
    GrB_BinaryOp_free(&GrB_LAND        );
    GrB_BinaryOp_free(&GrB_LOR         );
    GrB_BinaryOp_free(&GrB_LXOR        );

    Finalize(FP64)
    Finalize(FP32)
    Finalize(UINT64)
    Finalize(INT64)
    Finalize(UINT32)
    Finalize(INT32)
    Finalize(UINT16)
    Finalize(INT16)
    Finalize(UINT8)
    Finalize(INT8)
    Finalize(BOOL)

    GrB_Type_free(&GrB_FP64  );
    GrB_Type_free(&GrB_FP32  );
    GrB_Type_free(&GrB_UINT64);
    GrB_Type_free(&GrB_INT64 );
    GrB_Type_free(&GrB_UINT32);
    GrB_Type_free(&GrB_INT32 );
    GrB_Type_free(&GrB_UINT16);
    GrB_Type_free(&GrB_INT16 );
    GrB_Type_free(&GrB_UINT8 );
    GrB_Type_free(&GrB_INT8  );
    GrB_Type_free(&GrB_BOOL  );

    return GrB_SUCCESS;
}

#undef Finalize

// Section 4.2.1 algebra methods

GrB_Info GrB_Type_new
(
    GrB_Type   *utype,
    size_t      size
)
{
    if (!utype) return GrB_NULL_POINTER;
    *utype = new GrB_Type_t(size);
    if (utype) return GrB_SUCCESS;
    else return GrB_OUT_OF_MEMORY;
}

GrB_Info GrB_UnaryOp_new
(
    GrB_UnaryOp        *unary_op,
    void              (*unary_func)(void*, const void*),
    GrB_Type            d_out,
    GrB_Type            d_in
)
{
    if (!unary_op) return GrB_NULL_POINTER;
    if (!unary_func) return GrB_NULL_POINTER;
    if ((!d_out) || (d_out == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
    if ((!d_in)  || (d_out == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

    *unary_op = new GrB_UnaryOp_t(d_out,d_in,unary_func);
    if (*unary_op) return GrB_SUCCESS;
    else return GrB_OUT_OF_MEMORY;
}

GrB_Info GrB_BinaryOp_new
(
    GrB_BinaryOp        *binary_op,
    void                (*binary_func)(void*, const void*, const void*),
    GrB_Type            d_out,
    GrB_Type            d_in1,
    GrB_Type            d_in2
)
{
    if (!binary_op) return GrB_NULL_POINTER;
    if (!binary_func) return GrB_NULL_POINTER;
    if ((!d_out) || (d_out == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
    if ((!d_in1) || (d_out == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
    if ((!d_in2) || (d_out == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
   
    *binary_op = new GrB_BinaryOp_t(d_out,d_in1,d_in2,binary_func);
    if (*binary_op) return GrB_SUCCESS;
    else return GrB_OUT_OF_MEMORY;
}

GrB_Info GrB_Monoid_new_common
(
   GrB_Monoid  *monoid,
   GrB_Type     type,
   GrB_BinaryOp binary_op,
   const void  *identity
)
{
    if (!monoid) return GrB_NULL_POINTER;
    if ((!binary_op) || (binary_op == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
    if (binary_op->D_out()  != type) return GrB_DOMAIN_MISMATCH;
    if (binary_op->D_in_1() != type) return GrB_DOMAIN_MISMATCH;
    if (binary_op->D_in_2() != type) return GrB_DOMAIN_MISMATCH;

    *monoid = new GrB_Monoid_t(type,binary_op->F(),identity,type->size());
    if (*monoid) return GrB_SUCCESS;
    else return GrB_OUT_OF_MEMORY;
}

GrB_Info GrB_Monoid_new_BOOL
(
   GrB_Monoid   *monoid,
   GrB_BinaryOp  binary_op,
   bool          identity
)
{
    return GrB_Monoid_new_common(monoid,GrB_BOOL,binary_op,&identity);
}

GrB_Info GrB_Monoid_new_INT8
(
   GrB_Monoid   *monoid,
   GrB_BinaryOp  binary_op,
   int8_t        identity
)
{
    return GrB_Monoid_new_common(monoid,GrB_INT8,binary_op,&identity);
}

GrB_Info GrB_Monoid_new_UINT8
(
   GrB_Monoid   *monoid,
   GrB_BinaryOp  binary_op,
   uint8_t       identity
)
{
    return GrB_Monoid_new_common(monoid,GrB_UINT8,binary_op,&identity);
}

GrB_Info GrB_Monoid_new_INT16
(
   GrB_Monoid   *monoid,
   GrB_BinaryOp  binary_op,
   int16_t       identity
)
{
    return GrB_Monoid_new_common(monoid,GrB_INT16,binary_op,&identity);
}

GrB_Info GrB_Monoid_new_UINT16
(
   GrB_Monoid   *monoid,
   GrB_BinaryOp  binary_op,
   uint16_t      identity
)
{
    return GrB_Monoid_new_common(monoid,GrB_UINT16,binary_op,&identity);
}

GrB_Info GrB_Monoid_new_INT32
(
   GrB_Monoid   *monoid,
   GrB_BinaryOp  binary_op,
   int32_t       identity
)
{
    return GrB_Monoid_new_common(monoid,GrB_INT32,binary_op,&identity);
}

GrB_Info GrB_Monoid_new_UINT32
(
   GrB_Monoid   *monoid,
   GrB_BinaryOp  binary_op,
   uint32_t      identity
)
{
    return GrB_Monoid_new_common(monoid,GrB_UINT32,binary_op,&identity);
}

GrB_Info GrB_Monoid_new_INT64
(
   GrB_Monoid   *monoid,
   GrB_BinaryOp  binary_op,
   int64_t       identity
)
{
    return GrB_Monoid_new_common(monoid,GrB_INT64,binary_op,&identity);
}

GrB_Info GrB_Monoid_new_UINT64
(
   GrB_Monoid   *monoid,
   GrB_BinaryOp  binary_op,
   uint64_t      identity
)
{
    return GrB_Monoid_new_common(monoid,GrB_UINT64,binary_op,&identity);
}

GrB_Info GrB_Monoid_new_FP32
(
   GrB_Monoid   *monoid,
   GrB_BinaryOp  binary_op,
   float         identity
)
{
    return GrB_Monoid_new_common(monoid,GrB_FP32,binary_op,&identity);
}

GrB_Info GrB_Monoid_new_FP64
(
   GrB_Monoid   *monoid,
   GrB_BinaryOp  binary_op,
   double        identity
)
{
    return GrB_Monoid_new_common(monoid,GrB_FP64,binary_op,&identity);
}

GrB_Info GrB_Monoid_new_UDT
(
   GrB_Monoid   *monoid,
   GrB_BinaryOp binary_op,
   const void   *identity
)
{
    if (!monoid)   return GrB_NULL_POINTER;
    if (!identity) return GrB_NULL_POINTER;
    if ((!binary_op) || (binary_op == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

    return GrB_Monoid_new_common(monoid,binary_op->D_out(),binary_op,identity);
}

GrB_Info GrB_Semiring_new
(
    GrB_Semiring        *semiring,
    GrB_Monoid          add_op,
    GrB_BinaryOp        mul_op
)
{
    if (!semiring) return GrB_NULL_POINTER;
    if ((!add_op) || (add_op == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
    if ((!mul_op) || (mul_op == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
    if (mul_op->D_out() != add_op->D()) return GrB_DOMAIN_MISMATCH;

    *semiring = new GrB_Semiring_t(mul_op->D_out(), mul_op->D_in_1(), mul_op->D_in_2(), add_op->op(), mul_op->F(), add_op->zero(), add_op->len());
    if (*semiring) return GrB_SUCCESS;
    else return GrB_OUT_OF_MEMORY;
}

// Section 4.2.2 Vector Methods

// Section 4.2.2.1 Vector_new

GrB_Info GrB_Vector_new
(
    GrB_Vector          *v,
    const GrB_Type      d,
    const GrB_Index     nsize
)
{
    if (!v) return GrB_NULL_POINTER;
    if (nsize <= 0) return GrB_INVALID_VALUE;
    if ((!d) || (d == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
    if (d && (!d->valid())) return GrB_INVALID_OBJECT;

    *v = new GrB_Vector_t(d,nsize);
    if (*v) return GrB_SUCCESS;
    else return GrB_OUT_OF_MEMORY;
}

// Section 4.2.2.4 Vector_size

GrB_Info GrB_Vector_size
(
   GrB_Index            *nsize,
   const GrB_Vector     v
)
{
    if ((!v) || (v == GrB_INVALID_HANDLE))      return GrB_UNINITIALIZED_OBJECT;
    if (!nsize                           )      return GrB_NULL_POINTER;
    if (v    && (!v->valid())            )      return GrB_INVALID_OBJECT;

    *nsize = v->size();
    return GrB_SUCCESS;
}

// Section 4.2.2.5 Vector_nvals

GrB_Info GrB_Vector_nvals
(
    GrB_Index           *nvals,
    const GrB_Vector    u
)
{
    if ((!u) || (u == GrB_INVALID_HANDLE))      return GrB_UNINITIALIZED_OBJECT;
    if (!nvals                           )      return GrB_NULL_POINTER;
    if (u    && (!u->valid())            )      return GrB_INVALID_OBJECT;

    *nvals = u->nvals();
    return GrB_SUCCESS;
}

// Section 4.2.2.6 Vector_build

GrB_Info GrB_Vector_build_common
(
    GrB_Vector          w,
    const GrB_Index     *indices,
    const void          *values,
    GrB_Type            type,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    try
    {
        if ((!w)   || (w == GrB_INVALID_HANDLE)  )  return GrB_UNINITIALIZED_OBJECT;
        if ((!dup) || (dup == GrB_INVALID_HANDLE))  return GrB_UNINITIALIZED_OBJECT;

        if (w      && (!w->valid())              )  return GrB_INVALID_OBJECT;
        if (dup    && (!dup->valid())            )  return GrB_INVALID_OBJECT;

        if (!indices)                               return GrB_NULL_POINTER;
        if (!values)                                return GrB_NULL_POINTER;

        if (w->nvals() > 0)                         return GrB_OUTPUT_NOT_EMPTY;

        if (dup->D_out() != dup->D_in_1())          return GrB_DOMAIN_MISMATCH;
        if (dup->D_out() != dup->D_in_2())          return GrB_DOMAIN_MISMATCH;
        if (!(dup->D_out()->compatible(w->D())))    return GrB_DOMAIN_MISMATCH;
        if (!(dup->D_out()->compatible(type)))      return GrB_DOMAIN_MISMATCH;

        GrB_Vector_t w_tilde(dup->D_out(),w->size());
        Scalar val(type);
        for (GrB_Index i=0; i<n; i++)
        {
            if (indices[i] >= w_tilde.size()) return GrB_INDEX_OUT_OF_BOUNDS;
            memcpy(val,(char*)values+i*type->size(),type->size());
            w_tilde.addElement(indices[i],val,*dup);
        }

        w->copy(w_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Vector_build_BOOL
(
    GrB_Vector          w,
    const GrB_Index    *indices,
    const bool         *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Vector_build_common(w,indices,values,GrB_BOOL,n,dup);
}

GrB_Info GrB_Vector_build_INT8
(
    GrB_Vector          w,
    const GrB_Index    *indices,
    const int8_t       *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Vector_build_common(w,indices,values,GrB_INT8,n,dup);
}

GrB_Info GrB_Vector_build_UINT8
(
    GrB_Vector          w,
    const GrB_Index    *indices,
    const uint8_t      *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Vector_build_common(w,indices,values,GrB_UINT8,n,dup);
}

GrB_Info GrB_Vector_build_INT16
(
    GrB_Vector          w,
    const GrB_Index    *indices,
    const int16_t      *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Vector_build_common(w,indices,values,GrB_INT16,n,dup);
}

GrB_Info GrB_Vector_build_UINT16
(
    GrB_Vector          w,
    const GrB_Index    *indices,
    const uint16_t     *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Vector_build_common(w,indices,values,GrB_UINT16,n,dup);
}

GrB_Info GrB_Vector_build_INT32
(
    GrB_Vector          w,
    const GrB_Index    *indices,
    const int32_t      *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Vector_build_common(w,indices,values,GrB_INT32,n,dup);
}

GrB_Info GrB_Vector_build_UINT32
(
    GrB_Vector          w,
    const GrB_Index    *indices,
    const uint32_t     *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Vector_build_common(w,indices,values,GrB_UINT32,n,dup);
}

GrB_Info GrB_Vector_build_INT64
(
    GrB_Vector          w,
    const GrB_Index    *indices,
    const int64_t      *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Vector_build_common(w,indices,values,GrB_INT64,n,dup);
}

GrB_Info GrB_Vector_build_UINT64
(
    GrB_Vector          w,
    const GrB_Index    *indices,
    const uint64_t     *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Vector_build_common(w,indices,values,GrB_UINT64,n,dup);
}

GrB_Info GrB_Vector_build_FP32
(
    GrB_Vector          w,
    const GrB_Index    *indices,
    const float        *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Vector_build_common(w,indices,values,GrB_FP32,n,dup);
}

GrB_Info GrB_Vector_build_FP64
(
    GrB_Vector          w,
    const GrB_Index    *indices,
    const double       *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Vector_build_common(w,indices,values,GrB_FP64,n,dup);
}

GrB_Info GrB_Vector_build_UDT
(
    GrB_Vector          w,
    const GrB_Index    *indices,
    const void         *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    if ((!w)   || (w == GrB_INVALID_HANDLE)  )  return GrB_UNINITIALIZED_OBJECT;
    if ((!dup) || (dup == GrB_INVALID_HANDLE))  return GrB_UNINITIALIZED_OBJECT;

    if (w      && (!w->valid())              )  return GrB_INVALID_OBJECT;
    if (dup    && (!dup->valid())            )  return GrB_INVALID_OBJECT;

    return GrB_Vector_build_common(w,indices,values,w->D(),n,dup);
}

// Section 4.2.2.7 Vector_setElement

GrB_Info GrB_Vector_setElement_common
(
    const GrB_Vector    w,
    const void          *val,
    GrB_Type            type,
    GrB_Index           index
)
{
    try
    {
        if ((!w)   || (w == GrB_INVALID_HANDLE) ) return GrB_UNINITIALIZED_OBJECT;
        if (w      && (!w->valid())             ) return GrB_INVALID_OBJECT;
        if (!val                                ) return GrB_NULL_POINTER;
        if (!(w->D()->compatible(type))         ) return GrB_DOMAIN_MISMATCH;
        if (index >= w->size()                  ) return GrB_INVALID_INDEX;
        
        if ((w->ind()->count(index))) w->clear(index);
        Scalar x(type,val);
        w->addElement(index,x(w->D()));

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Vector_setElement_BOOL
(
    GrB_Vector  w,
    bool        val,
    GrB_Index   index
)
{
    return GrB_Vector_setElement_common(w,&val,GrB_BOOL,index);
}

GrB_Info GrB_Vector_setElement_INT8
(
    GrB_Vector  w,
    int8_t      val,
    GrB_Index   index
)
{
    return GrB_Vector_setElement_common(w,&val,GrB_INT8,index);
}

GrB_Info GrB_Vector_setElement_UINT8
(
    GrB_Vector  w,
    uint8_t     val,
    GrB_Index   index
)
{
    return GrB_Vector_setElement_common(w,&val,GrB_UINT8,index);
}

GrB_Info GrB_Vector_setElement_INT16
(
    GrB_Vector  w,
    int16_t     val,
    GrB_Index   index
)
{
    return GrB_Vector_setElement_common(w,&val,GrB_INT16,index);
}

GrB_Info GrB_Vector_setElement_UINT16
(
    GrB_Vector  w,
    uint16_t    val,
    GrB_Index   index
)
{
    return GrB_Vector_setElement_common(w,&val,GrB_UINT16,index);
}

GrB_Info GrB_Vector_setElement_INT32
(
    GrB_Vector  w,
    int32_t     val,
    GrB_Index   index
)
{
    return GrB_Vector_setElement_common(w,&val,GrB_INT32,index);
}

GrB_Info GrB_Vector_setElement_UINT32
(
    GrB_Vector  w,
    uint32_t    val,
    GrB_Index   index
)
{
    return GrB_Vector_setElement_common(w,&val,GrB_UINT32,index);
}

GrB_Info GrB_Vector_setElement_INT64
(
    GrB_Vector  w,
    int64_t     val,
    GrB_Index   index
)
{
    return GrB_Vector_setElement_common(w,&val,GrB_INT64,index);
}

GrB_Info GrB_Vector_setElement_UINT64
(
    GrB_Vector  w,
    uint64_t    val,
    GrB_Index   index
)
{
    return GrB_Vector_setElement_common(w,&val,GrB_UINT64,index);
}

GrB_Info GrB_Vector_setElement_FP32
(
    GrB_Vector  w,
    float       val,
    GrB_Index   index
)
{
    return GrB_Vector_setElement_common(w,&val,GrB_FP32,index);
}

GrB_Info GrB_Vector_setElement_FP64
(
    GrB_Vector  w,
    double      val,
    GrB_Index   index
)
{
    return GrB_Vector_setElement_common(w,&val,GrB_FP64,index);
}

GrB_Info GrB_Vector_setElement_UDT
(
    GrB_Vector  w,
    const void  *val,
    GrB_Index   index
)
{
    if ((!w)   || (w == GrB_INVALID_HANDLE) ) return GrB_UNINITIALIZED_OBJECT;
    if (w      && (!w->valid())             ) return GrB_INVALID_OBJECT;

    return GrB_Vector_setElement_common(w,val,w->D(),index);
}

// Section 4.2.2.8 Vector_extractElement

GrB_Info GrB_Vector_extractElement_common
(
    void               *val,
    GrB_Type            type,
    const GrB_Vector    u,
    GrB_Index           index
)
{
    try
    {
        if ((!u)   || (u == GrB_INVALID_HANDLE) ) return GrB_UNINITIALIZED_OBJECT;
        if (u      && (!u->valid())             ) return GrB_INVALID_OBJECT;
        if (!val                                ) return GrB_NULL_POINTER;
        if (!(u->D()->compatible(type))         ) return GrB_DOMAIN_MISMATCH;
        if (index >= u->size()                  ) return GrB_INVALID_INDEX;
        if (!(u->ind()->count(index))           ) return GrB_NO_VALUE;

        memcpy(val,(*u)[index](type),type->size());

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Vector_extractElement_BOOL
(
    bool               *val,
    const GrB_Vector    u,
    GrB_Index           index
)
{
    return GrB_Vector_extractElement_common(val,GrB_BOOL,u,index);
}

GrB_Info GrB_Vector_extractElement_INT8
(
    int8_t             *val,
    const GrB_Vector    u,
    GrB_Index           index
)
{
    return GrB_Vector_extractElement_common(val,GrB_INT8,u,index);
}

GrB_Info GrB_Vector_extractElement_UINT8
(
    uint8_t            *val,
    const GrB_Vector    u,
    GrB_Index           index
)
{
    return GrB_Vector_extractElement_common(val,GrB_UINT8,u,index);
}

GrB_Info GrB_Vector_extractElement_INT16
(
    int16_t            *val,
    const GrB_Vector    u,
    GrB_Index           index
)
{
    return GrB_Vector_extractElement_common(val,GrB_INT16,u,index);
}

GrB_Info GrB_Vector_extractElement_UINT16
(
    uint16_t           *val,
    const GrB_Vector    u,
    GrB_Index           index
)
{
    return GrB_Vector_extractElement_common(val,GrB_UINT16,u,index);
}

GrB_Info GrB_Vector_extractElement_INT32
(
    int32_t            *val,
    const GrB_Vector    u,
    GrB_Index           index
)
{
    return GrB_Vector_extractElement_common(val,GrB_INT32,u,index);
}

GrB_Info GrB_Vector_extractElement_UINT32
(
    uint32_t           *val,
    const GrB_Vector    u,
    GrB_Index           index
)
{
    return GrB_Vector_extractElement_common(val,GrB_UINT32,u,index);
}

GrB_Info GrB_Vector_extractElement_INT64
(
    int64_t            *val,
    const GrB_Vector    u,
    GrB_Index           index
)
{
    return GrB_Vector_extractElement_common(val,GrB_INT64,u,index);
}

GrB_Info GrB_Vector_extractElement_UINT64
(
    uint64_t           *val,
    const GrB_Vector    u,
    GrB_Index           index
)
{
    return GrB_Vector_extractElement_common(val,GrB_UINT64,u,index);
}

GrB_Info GrB_Vector_extractElement_FP32
(
    float              *val,
    const GrB_Vector    u,
    GrB_Index           index
)
{
    return GrB_Vector_extractElement_common(val,GrB_FP32,u,index);
}

GrB_Info GrB_Vector_extractElement_FP64
(
    double             *val,
    const GrB_Vector    u,
    GrB_Index           index
)
{
    return GrB_Vector_extractElement_common(val,GrB_FP64,u,index);
}

GrB_Info GrB_Vector_extractElement_UDT
(
    void               *val,
    const GrB_Vector    u,
    GrB_Index           index
)
{
    if ((!u)   || (u == GrB_INVALID_HANDLE) ) return GrB_UNINITIALIZED_OBJECT;
    if (u      && (!u->valid())             ) return GrB_INVALID_OBJECT;
    return GrB_Vector_extractElement_common(val,u->D(),u,index);
}

// Section 4.2.2.9 Vector_extractTuples

static
GrB_Info GrB_Vector_extractTuples_common
(
    GrB_Index           *indices,
    void                *values,
    GrB_Type            type,
    GrB_Index           *n,
    const GrB_Vector    v
)
{
    if ((!v)   || (v == GrB_INVALID_HANDLE)  )  return GrB_UNINITIALIZED_OBJECT;
    if (v      && (!v->valid())              )  return GrB_INVALID_OBJECT;
    if (!indices)                               return GrB_NULL_POINTER;
    if (!values)                                return GrB_NULL_POINTER;
    if (v->nvals() > *n)                        return GrB_INSUFFICIENT_SPACE;
    if (!(v->D()->compatible(type)))            return GrB_DOMAIN_MISMATCH;

    *n = v->nvals();
    size_t p = 0;
    for (auto j : *(v->ind()))
    {
        indices[p] = j;
        memcpy((char*)values+p*type->size(),(*v)[j](type),type->size());
        p++;
    }

    assert(p == *n);
    return GrB_SUCCESS;
}

GrB_Info GrB_Vector_extractTuples_BOOL
(
    GrB_Index          *indices,
    bool              *values,
    GrB_Index          *n,
    const GrB_Vector    v
)
{
    return GrB_Vector_extractTuples_common(indices,values,GrB_BOOL,n,v);
}

GrB_Info GrB_Vector_extractTuples_INT8
(
    GrB_Index          *indices,
    int8_t            *values,
    GrB_Index          *n,
    const GrB_Vector    v
)
{
    return GrB_Vector_extractTuples_common(indices,values,GrB_INT8,n,v);
}

GrB_Info GrB_Vector_extractTuples_UINT8
(
    GrB_Index          *indices,
    uint8_t            *values,
    GrB_Index          *n,
    const GrB_Vector    v
)
{
    return GrB_Vector_extractTuples_common(indices,values,GrB_UINT8,n,v);
}

GrB_Info GrB_Vector_extractTuples_INT16
(
    GrB_Index          *indices,
    int16_t            *values,
    GrB_Index          *n,
    const GrB_Vector    v
)
{
    return GrB_Vector_extractTuples_common(indices,values,GrB_INT16,n,v);
}

GrB_Info GrB_Vector_extractTuples_UINT16
(
    GrB_Index          *indices,
    uint16_t           *values,
    GrB_Index          *n,
    const GrB_Vector    v
)
{
    return GrB_Vector_extractTuples_common(indices,values,GrB_UINT16,n,v);
}

GrB_Info GrB_Vector_extractTuples_INT32
(
    GrB_Index          *indices,
    int32_t            *values,
    GrB_Index          *n,
    const GrB_Vector    v
)
{
    return GrB_Vector_extractTuples_common(indices,values,GrB_INT32,n,v);
}

GrB_Info GrB_Vector_extractTuples_UINT32
(
    GrB_Index          *indices,
    uint32_t           *values,
    GrB_Index          *n,
    const GrB_Vector    v
)
{
    return GrB_Vector_extractTuples_common(indices,values,GrB_UINT32,n,v);
}

GrB_Info GrB_Vector_extractTuples_INT64
(
    GrB_Index          *indices,
    int64_t            *values,
    GrB_Index          *n,
    const GrB_Vector    v
)
{
    return GrB_Vector_extractTuples_common(indices,values,GrB_INT64,n,v);
}

GrB_Info GrB_Vector_extractTuples_UINT64
(
    GrB_Index          *indices,
    uint64_t           *values,
    GrB_Index          *n,
    const GrB_Vector    v
)
{
    return GrB_Vector_extractTuples_common(indices,values,GrB_UINT64,n,v);
}

GrB_Info GrB_Vector_extractTuples_FP32
(
    GrB_Index          *indices,
    float              *values,
    GrB_Index          *n,
    const GrB_Vector    v
)
{
    return GrB_Vector_extractTuples_common(indices,values,GrB_FP32,n,v);
}

GrB_Info GrB_Vector_extractTuples_FP64
(
    GrB_Index          *indices,
    double             *values,
    GrB_Index          *n,
    const GrB_Vector    v
)
{
    return GrB_Vector_extractTuples_common(indices,values,GrB_FP64,n,v);
}

GrB_Info GrB_Vector_extractTuples_UDT
(
    GrB_Index          *indices,
    void               *values,
    GrB_Index          *n,
    const GrB_Vector    v
)
{
    if ((!v)   || (v == GrB_INVALID_HANDLE)  )  return GrB_UNINITIALIZED_OBJECT;
    if (v      && (!v->valid())              )  return GrB_INVALID_OBJECT;
    return GrB_Vector_extractTuples_common(indices,values,v->D(),n,v);
}

// Section 4.2.3 Matrix Methods

// Section 4.2.3.1 Matrix_new

GrB_Info GrB_Matrix_new
(
    GrB_Matrix          *A,
    const GrB_Type      d,
    GrB_Index           nrows,
    GrB_Index           ncols
)
{
    if (!A) return GrB_NULL_POINTER;
    if (nrows <= 0) return GrB_INVALID_VALUE;
    if (ncols <= 0) return GrB_INVALID_VALUE;
    if ((!d) || (d == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
    if (d && (!d->valid())) return GrB_INVALID_OBJECT;

    *A = new GrB_Matrix_t(d,nrows,ncols);
    if (*A) return GrB_SUCCESS;
    else return GrB_OUT_OF_MEMORY;
}

// Section 4.2.3.3 Matrix_clear

GrB_Info GrB_Matrix_clear
(
    GrB_Matrix A
)
{
    if (A->clear()) return GrB_SUCCESS;
    return GrB_PANIC;
}

// Section 4.2.3.4 Matrix_nrows

GrB_Info GrB_Matrix_nrows
(
    GrB_Index           *nrows,
    const GrB_Matrix    A
)
{
    if ((!A) || (A == GrB_INVALID_HANDLE))      return GrB_UNINITIALIZED_OBJECT;
    if (!nrows                           )      return GrB_NULL_POINTER;
    if (A    && (!A->valid())            )      return GrB_INVALID_OBJECT;

    *nrows = A->nrows();
    return GrB_SUCCESS;
}

// Section 4.2.3.5 Matrix_ncols

GrB_Info GrB_Matrix_ncols
(
    GrB_Index           *ncols,
    const GrB_Matrix    A
)
{
    if ((!A) || (A == GrB_INVALID_HANDLE))      return GrB_UNINITIALIZED_OBJECT;
    if (!ncols                           )      return GrB_NULL_POINTER;
    if (A    && (!A->valid())            )      return GrB_INVALID_OBJECT;

    *ncols = A->ncols();
    return GrB_SUCCESS;
}

// Section 4.2.3.6 Matrix_nvals

GrB_Info GrB_Matrix_nvals
(
    GrB_Index           *nvals,
    const GrB_Matrix    A
)
{
    if ((!A) || (A == GrB_INVALID_HANDLE))      return GrB_UNINITIALIZED_OBJECT;
    if (!nvals                           )      return GrB_NULL_POINTER;
    if (A    && (!A->valid())            )      return GrB_INVALID_OBJECT;

    *nvals = A->nvals();
    return GrB_SUCCESS;
}

// Section 4.2.3.7 Matrix_build

static
GrB_Info GrB_Matrix_build_common
(
    GrB_Matrix          C,
    const GrB_Index     *row_indices,
    const GrB_Index     *col_indices,
    const void          *values,
    GrB_Type            type,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    try
    {
        if ((!C)   || (C == GrB_INVALID_HANDLE)  )      return GrB_UNINITIALIZED_OBJECT;
        if ((!dup) || (dup == GrB_INVALID_HANDLE))      return GrB_UNINITIALIZED_OBJECT;
        if (C      && (!C->valid())              )      return GrB_INVALID_OBJECT;
        if (dup    && (!dup->valid())            )      return GrB_INVALID_OBJECT;
        if (!row_indices)                               return GrB_NULL_POINTER;
        if (!col_indices)                               return GrB_NULL_POINTER;
        if (!values)                                    return GrB_NULL_POINTER;
        if (C->nvals() > 0)                             return GrB_OUTPUT_NOT_EMPTY;
        if (dup->D_out() != dup->D_in_1())              return GrB_DOMAIN_MISMATCH;
        if (dup->D_out() != dup->D_in_2())              return GrB_DOMAIN_MISMATCH;
        if (!(dup->D_out()->compatible(C->D())))        return GrB_DOMAIN_MISMATCH;
        if (!(dup->D_out()->compatible(type)))          return GrB_DOMAIN_MISMATCH;

        GrB_Matrix_t C_tilde(dup->D_out(),C->nrows(),C->ncols());
        Scalar val(type);
        for (GrB_Index i=0; i<n; i++)
        {
            if (row_indices[i] >= C_tilde.nrows()) return GrB_INDEX_OUT_OF_BOUNDS;
            if (col_indices[i] >= C_tilde.ncols()) return GrB_INDEX_OUT_OF_BOUNDS;
            memcpy(val,(char*)values+i*type->size(),type->size());
            C_tilde.addElement(row_indices[i],col_indices[i],val,*dup);
        }

        C->copy(C_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Matrix_build_BOOL
(
    GrB_Matrix          C,
    const GrB_Index    *row_indices,
    const GrB_Index    *col_indices,
    const bool         *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Matrix_build_common(C,row_indices,col_indices,values,GrB_BOOL,n,dup);
}

GrB_Info GrB_Matrix_build_INT8
(
    GrB_Matrix          C,
    const GrB_Index    *row_indices,
    const GrB_Index    *col_indices,
    const int8_t       *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Matrix_build_common(C,row_indices,col_indices,values,GrB_INT8,n,dup);
}

GrB_Info GrB_Matrix_build_UINT8
(
    GrB_Matrix          C,
    const GrB_Index    *row_indices,
    const GrB_Index    *col_indices,
    const uint8_t      *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Matrix_build_common(C,row_indices,col_indices,values,GrB_UINT8,n,dup);
}

GrB_Info GrB_Matrix_build_INT16
(
    GrB_Matrix          C,
    const GrB_Index    *row_indices,
    const GrB_Index    *col_indices,
    const int16_t      *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Matrix_build_common(C,row_indices,col_indices,values,GrB_INT16,n,dup);
}

GrB_Info GrB_Matrix_build_UINT16
(
    GrB_Matrix          C,
    const GrB_Index    *row_indices,
    const GrB_Index    *col_indices,
    const uint16_t     *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Matrix_build_common(C,row_indices,col_indices,values,GrB_UINT16,n,dup);
}

GrB_Info GrB_Matrix_build_INT32
(
    GrB_Matrix          C,
    const GrB_Index    *row_indices,
    const GrB_Index    *col_indices,
    const int32_t      *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Matrix_build_common(C,row_indices,col_indices,values,GrB_INT32,n,dup);
}

GrB_Info GrB_Matrix_build_UINT32
(
    GrB_Matrix          C,
    const GrB_Index    *row_indices,
    const GrB_Index    *col_indices,
    const uint32_t     *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Matrix_build_common(C,row_indices,col_indices,values,GrB_UINT32,n,dup);
}

GrB_Info GrB_Matrix_build_INT64
(
    GrB_Matrix          C,
    const GrB_Index    *row_indices,
    const GrB_Index    *col_indices,
    const int64_t      *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Matrix_build_common(C,row_indices,col_indices,values,GrB_INT64,n,dup);
}

GrB_Info GrB_Matrix_build_UINT64
(
    GrB_Matrix          C,
    const GrB_Index    *row_indices,
    const GrB_Index    *col_indices,
    const uint64_t     *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Matrix_build_common(C,row_indices,col_indices,values,GrB_UINT64,n,dup);
}

GrB_Info GrB_Matrix_build_FP32
(
    GrB_Matrix          C,
    const GrB_Index    *row_indices,
    const GrB_Index    *col_indices,
    const float        *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Matrix_build_common(C,row_indices,col_indices,values,GrB_FP32,n,dup);
}

GrB_Info GrB_Matrix_build_FP64
(
    GrB_Matrix          C,
    const GrB_Index    *row_indices,
    const GrB_Index    *col_indices,
    const double       *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    return GrB_Matrix_build_common(C,row_indices,col_indices,values,GrB_FP64,n,dup);
}

GrB_Info GrB_Matrix_build_UDT
(
    GrB_Matrix          C,
    const GrB_Index    *row_indices,
    const GrB_Index    *col_indices,
    const void         *values,
    GrB_Index           n,
    const GrB_BinaryOp  dup
)
{
    if ((!C)   || (C == GrB_INVALID_HANDLE)  )      return GrB_UNINITIALIZED_OBJECT;
    return GrB_Matrix_build_common(C,row_indices,col_indices,values,C->D(),n,dup);
}

// Section 4.2.3.8 Matrix_setElement

GrB_Info GrB_Matrix_setElement_common
(
    const GrB_Matrix    C,
    const void          *val,
    GrB_Type            type,
    GrB_Index           row_index,
    GrB_Index           col_index
)
{
    try
    {
        if ((!C)   || (C == GrB_INVALID_HANDLE) ) return GrB_UNINITIALIZED_OBJECT;
        if (C      && (!C->valid())             ) return GrB_INVALID_OBJECT;
        if (!val                                ) return GrB_NULL_POINTER;
        if (!(C->D()->compatible(type))         ) return GrB_DOMAIN_MISMATCH;
        if (row_index >= C->nrows()             ) return GrB_INVALID_INDEX;
        if (col_index >= C->ncols()             ) return GrB_INVALID_INDEX;
        
        if ((*C)[row_index].ind()->count(col_index)) C->clear(row_index,col_index);
        Scalar x(type,val);
        C->addElement(row_index,col_index,x(C->D()));

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Matrix_setElement_BOOL
(
    GrB_Matrix  C,
    bool        val,
    GrB_Index   row_index,
    GrB_Index   col_index
)
{
    return GrB_Matrix_setElement_common(C,&val,GrB_BOOL,row_index,col_index);
}

GrB_Info GrB_Matrix_setElement_INT8
(
    GrB_Matrix  C,
    int8_t      val,
    GrB_Index   row_index,
    GrB_Index   col_index
)
{
    return GrB_Matrix_setElement_common(C,&val,GrB_INT8,row_index,col_index);
}

GrB_Info GrB_Matrix_setElement_UINT8
(
    GrB_Matrix  C,
    uint8_t     val,
    GrB_Index   row_index,
    GrB_Index   col_index
)
{
    return GrB_Matrix_setElement_common(C,&val,GrB_UINT8,row_index,col_index);
}

GrB_Info GrB_Matrix_setElement_INT16
(
    GrB_Matrix  C,
    int16_t     val,
    GrB_Index   row_index,
    GrB_Index   col_index
)
{
    return GrB_Matrix_setElement_common(C,&val,GrB_INT16,row_index,col_index);
}

GrB_Info GrB_Matrix_setElement_UINT16
(
    GrB_Matrix  C,
    uint16_t    val,
    GrB_Index   row_index,
    GrB_Index   col_index
)
{
    return GrB_Matrix_setElement_common(C,&val,GrB_UINT16,row_index,col_index);
}

GrB_Info GrB_Matrix_setElement_INT32
(
    GrB_Matrix  C,
    int32_t     val,
    GrB_Index   row_index,
    GrB_Index   col_index
)
{
    return GrB_Matrix_setElement_common(C,&val,GrB_INT32,row_index,col_index);
}

GrB_Info GrB_Matrix_setElement_UINT32
(
    GrB_Matrix  C,
    uint32_t    val,
    GrB_Index   row_index,
    GrB_Index   col_index
)
{
    return GrB_Matrix_setElement_common(C,&val,GrB_UINT32,row_index,col_index);
}

GrB_Info GrB_Matrix_setElement_INT64
(
    GrB_Matrix  C,
    int64_t     val,
    GrB_Index   row_index,
    GrB_Index   col_index
)
{
    return GrB_Matrix_setElement_common(C,&val,GrB_INT64,row_index,col_index);
}

GrB_Info GrB_Matrix_setElement_UINT64
(
    GrB_Matrix  C,
    uint64_t    val,
    GrB_Index   row_index,
    GrB_Index   col_index
)
{
    return GrB_Matrix_setElement_common(C,&val,GrB_UINT64,row_index,col_index);
}

GrB_Info GrB_Matrix_setElement_FP32
(
    GrB_Matrix  C,
    float       val,
    GrB_Index   row_index,
    GrB_Index   col_index
)
{
    return GrB_Matrix_setElement_common(C,&val,GrB_FP32,row_index,col_index);
}

GrB_Info GrB_Matrix_setElement_FP64
(
    GrB_Matrix  C,
    double      val,
    GrB_Index   row_index,
    GrB_Index   col_index
)
{
    return GrB_Matrix_setElement_common(C,&val,GrB_FP64,row_index,col_index);
}

GrB_Info GrB_Matrix_setElement_UDT
(
    GrB_Matrix  C,
    const void  *val,
    GrB_Index   row_index,
    GrB_Index   col_index
)
{
    if ((!C)   || (C == GrB_INVALID_HANDLE) ) return GrB_UNINITIALIZED_OBJECT;
    return GrB_Matrix_setElement_common(C,val,C->D(),row_index,col_index);
}

// Section 4.2.3.9 Matrix_extractElement

GrB_Info GrB_Matrix_extractElement_common
(
    void               *val,
    GrB_Type            type,
    const GrB_Matrix    A,
    GrB_Index           row_index,
    GrB_Index           col_index
)
{
    try
    {
        if ((!A)   || (A == GrB_INVALID_HANDLE)       ) return GrB_UNINITIALIZED_OBJECT;
        if (A      && (!A->valid())                   ) return GrB_INVALID_OBJECT;
        if (!val                                      ) return GrB_NULL_POINTER;
        if (!(A->D()->compatible(type))               ) return GrB_DOMAIN_MISMATCH;
        if (row_index >= A->nrows()                   ) return GrB_INVALID_INDEX;
        if (col_index >= A->ncols()                   ) return GrB_INVALID_INDEX;
        if (!((*A)[row_index].ind()->count(col_index))) return GrB_NO_VALUE;

        memcpy(val,(*A)[row_index][col_index](type),type->size());

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Matrix_extractElement_BOOL
(
    bool               *val,
    const GrB_Matrix    A,
    GrB_Index           row_index,
    GrB_Index           col_index
)
{
    return GrB_Matrix_extractElement_common(val,GrB_BOOL,A,row_index,col_index);
}

GrB_Info GrB_Matrix_extractElement_INT8
(
    int8_t             *val,
    const GrB_Matrix    A,
    GrB_Index           row_index,
    GrB_Index           col_index
)
{
    return GrB_Matrix_extractElement_common(val,GrB_INT8,A,row_index,col_index);
}

GrB_Info GrB_Matrix_extractElement_UINT8
(
    uint8_t            *val,
    const GrB_Matrix    A,
    GrB_Index           row_index,
    GrB_Index           col_index
)
{
    return GrB_Matrix_extractElement_common(val,GrB_UINT8,A,row_index,col_index);
}

GrB_Info GrB_Matrix_extractElement_INT16
(
    int16_t            *val,
    const GrB_Matrix    A,
    GrB_Index           row_index,
    GrB_Index           col_index
)
{
    return GrB_Matrix_extractElement_common(val,GrB_INT16,A,row_index,col_index);
}

GrB_Info GrB_Matrix_extractElement_UINT16
(
    uint16_t           *val,
    const GrB_Matrix    A,
    GrB_Index           row_index,
    GrB_Index           col_index
)
{
    return GrB_Matrix_extractElement_common(val,GrB_UINT16,A,row_index,col_index);
}

GrB_Info GrB_Matrix_extractElement_INT32
(
    int32_t            *val,
    const GrB_Matrix    A,
    GrB_Index           row_index,
    GrB_Index           col_index
)
{
    return GrB_Matrix_extractElement_common(val,GrB_INT32,A,row_index,col_index);
}

GrB_Info GrB_Matrix_extractElement_UINT32
(
    uint32_t           *val,
    const GrB_Matrix    A,
    GrB_Index           row_index,
    GrB_Index           col_index
)
{
    return GrB_Matrix_extractElement_common(val,GrB_UINT32,A,row_index,col_index);
}

GrB_Info GrB_Matrix_extractElement_INT64
(
    int64_t            *val,
    const GrB_Matrix    A,
    GrB_Index           row_index,
    GrB_Index           col_index
)
{
    return GrB_Matrix_extractElement_common(val,GrB_INT64,A,row_index,col_index);
}

GrB_Info GrB_Matrix_extractElement_UINT64
(
    uint64_t           *val,
    const GrB_Matrix    A,
    GrB_Index           row_index,
    GrB_Index           col_index
)
{
    return GrB_Matrix_extractElement_common(val,GrB_UINT64,A,row_index,col_index);
}

GrB_Info GrB_Matrix_extractElement_FP32
(
    float              *val,
    const GrB_Matrix    A,
    GrB_Index           row_index,
    GrB_Index           col_index
)
{
    return GrB_Matrix_extractElement_common(val,GrB_FP32,A,row_index,col_index);
}

GrB_Info GrB_Matrix_extractElement_FP64
(
    double             *val,
    const GrB_Matrix    A,
    GrB_Index           row_index,
    GrB_Index           col_index
)
{
    return GrB_Matrix_extractElement_common(val,GrB_FP64,A,row_index,col_index);
}

GrB_Info GrB_Matrix_extractElement_UDT
(
    void               *val,
    const GrB_Matrix    A,
    GrB_Index           row_index,
    GrB_Index           col_index
)
{
    if ((!A)   || (A == GrB_INVALID_HANDLE)       ) return GrB_UNINITIALIZED_OBJECT;
    return GrB_Matrix_extractElement_common(val,A->D(),A,row_index,col_index);
}

// Section 4.2.3.10 Matrix_extractTuples

static
GrB_Info GrB_Matrix_extractTuples_common
(
    GrB_Index          *row_indices,
    GrB_Index          *col_indices,
    void               *values,
    GrB_Type            type,
    GrB_Index          *n,
    const GrB_Matrix    A
)
{
    if ((!A)   || (A == GrB_INVALID_HANDLE)  )  return GrB_UNINITIALIZED_OBJECT;
    if (A      && (!A->valid())              )  return GrB_INVALID_OBJECT;
    if (!row_indices)                           return GrB_NULL_POINTER;
    if (!col_indices)                           return GrB_NULL_POINTER;
    if (!values)                                return GrB_NULL_POINTER;
    if (A->nvals() > *n)                        return GrB_INSUFFICIENT_SPACE;
    if (!(A->D()->compatible(type)))            return GrB_DOMAIN_MISMATCH;

    *n = A->nvals();
    uint32_t p = 0;
    for (GrB_Index i=0; i<A->nrows(); i++)
    {
        for (auto j : *((*A)[i].ind()))
        {
            row_indices[p] = i;
            col_indices[p] = j;
            memcpy((char*)values+p*type->size(),(*A)[i][j](type),type->size());
            p++;
        }
    }

    assert(p == *n);
    return GrB_SUCCESS;
}

GrB_Info GrB_Matrix_extractTuples_BOOL
(
    GrB_Index          *row_indices,
    GrB_Index          *col_indices,
    bool               *values,
    GrB_Index          *n,
    const GrB_Matrix    A
)
{
    return GrB_Matrix_extractTuples_common(row_indices,col_indices,values,GrB_BOOL,n,A);
}

GrB_Info GrB_Matrix_extractTuples_INT8
(
    GrB_Index          *row_indices,
    GrB_Index          *col_indices,
    int8_t             *values,
    GrB_Index          *n,
    const GrB_Matrix    A
)
{
    return GrB_Matrix_extractTuples_common(row_indices,col_indices,values,GrB_INT8,n,A);
}

GrB_Info GrB_Matrix_extractTuples_UINT8
(
    GrB_Index          *row_indices,
    GrB_Index          *col_indices,
    uint8_t            *values,
    GrB_Index          *n,
    const GrB_Matrix    A
)
{
    return GrB_Matrix_extractTuples_common(row_indices,col_indices,values,GrB_UINT8,n,A);
}

GrB_Info GrB_Matrix_extractTuples_INT16
(
    GrB_Index          *row_indices,
    GrB_Index          *col_indices,
    int16_t            *values,
    GrB_Index          *n,
    const GrB_Matrix    A
)
{
    return GrB_Matrix_extractTuples_common(row_indices,col_indices,values,GrB_INT16,n,A);
}

GrB_Info GrB_Matrix_extractTuples_UINT16
(
    GrB_Index          *row_indices,
    GrB_Index          *col_indices,
    uint16_t           *values,
    GrB_Index          *n,
    const GrB_Matrix    A
)
{
    return GrB_Matrix_extractTuples_common(row_indices,col_indices,values,GrB_UINT16,n,A);
}

GrB_Info GrB_Matrix_extractTuples_INT32
(
    GrB_Index          *row_indices,
    GrB_Index          *col_indices,
    int32_t            *values,
    GrB_Index          *n,
    const GrB_Matrix    A
)
{
    return GrB_Matrix_extractTuples_common(row_indices,col_indices,values,GrB_INT32,n,A);
}

GrB_Info GrB_Matrix_extractTuples_UINT32
(
    GrB_Index          *row_indices,
    GrB_Index          *col_indices,
    uint32_t           *values,
    GrB_Index          *n,
    const GrB_Matrix    A
)
{
    return GrB_Matrix_extractTuples_common(row_indices,col_indices,values,GrB_UINT32,n,A);
}

GrB_Info GrB_Matrix_extractTuples_INT64
(
    GrB_Index          *row_indices,
    GrB_Index          *col_indices,
    int64_t            *values,
    GrB_Index          *n,
    const GrB_Matrix    A
)
{
    return GrB_Matrix_extractTuples_common(row_indices,col_indices,values,GrB_INT64,n,A);
}

GrB_Info GrB_Matrix_extractTuples_UINT64
(
    GrB_Index          *row_indices,
    GrB_Index          *col_indices,
    uint64_t           *values,
    GrB_Index          *n,
    const GrB_Matrix    A
)
{
    return GrB_Matrix_extractTuples_common(row_indices,col_indices,values,GrB_UINT64,n,A);
}

GrB_Info GrB_Matrix_extractTuples_FP32
(
    GrB_Index          *row_indices,
    GrB_Index          *col_indices,
    float              *values,
    GrB_Index          *n,
    const GrB_Matrix    A
)
{
    return GrB_Matrix_extractTuples_common(row_indices,col_indices,values,GrB_FP32,n,A);
}

GrB_Info GrB_Matrix_extractTuples_FP64
(
    GrB_Index          *row_indices,
    GrB_Index          *col_indices,
    double             *values,
    GrB_Index          *n,
    const GrB_Matrix    A
)
{
    return GrB_Matrix_extractTuples_common(row_indices,col_indices,values,GrB_FP64,n,A);
}

GrB_Info GrB_Matrix_extractTuples_UDT
(
    GrB_Index          *row_indices,
    GrB_Index          *col_indices,
    void               *values,
    GrB_Index          *n,
    const GrB_Matrix    A
)
{
    if ((!A)   || (A == GrB_INVALID_HANDLE)  )  return GrB_UNINITIALIZED_OBJECT;
    return GrB_Matrix_extractTuples_common(row_indices,col_indices,values,A->D(),n,A);
}

// Section 4.2.4 Descriptor Methods

// Section 4.2.4.1 Descriptor_new

GrB_Info GrB_Descriptor_new
(
    GrB_Descriptor *d
)
{
    if (!d) return GrB_NULL_POINTER;
    *d = new GrB_Descriptor_t();
    if (d) return GrB_SUCCESS;
    else return GrB_OUT_OF_MEMORY;
}

GrB_Info GrB_Descriptor_set
(
    GrB_Descriptor desc,
    GrB_Desc_Field field,
    GrB_Desc_Value val
)
{
    if ((!desc) || (desc == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
    switch (field)
    {
        case GrB_OUTP:
            switch (val)
            {
                case GrB_REPLACE:
                    desc->setReplace();
                    break;
                default:
                    return GrB_INVALID_VALUE;
            }
            break;
        case GrB_MASK:
            switch (val)
            {
                case GrB_SCMP:
                    desc->setSCMP();
                    break;
                default:
                    return GrB_INVALID_VALUE;
            }
            break;
        case GrB_INP0:
            switch (val)
            {
                case GrB_TRAN:
                    desc->setTran0();
                    break;
                default:
                    return GrB_INVALID_VALUE;
            }
            break;
        case GrB_INP1:
            switch (val)
            {
                case GrB_TRAN:
                    desc->setTran1();
                    break;
                default:
                    return GrB_INVALID_VALUE;
            }
            break;
        default:
            return GrB_INVALID_VALUE;
    }
    return GrB_SUCCESS;
}

// Section 4.2.5 free

GrB_Info GrB_Type_free
(
    GrB_Type    *t
)
{
    if ((!t) || (t == GrB_INVALID_HANDLE)) return GrB_SUCCESS;

    delete *t;
    *t = (GrB_Type_t*)GrB_INVALID_HANDLE;

    return GrB_SUCCESS;
}

GrB_Info GrB_UnaryOp_free
(
    GrB_UnaryOp        *b
)
{
    if ((!b) || (b == GrB_INVALID_HANDLE)) return GrB_SUCCESS;

    delete *b;
    *b = (GrB_UnaryOp_t*)GrB_INVALID_HANDLE;

    return GrB_SUCCESS;
}

GrB_Info GrB_BinaryOp_free
(
    GrB_BinaryOp        *b
)
{
    if ((!b) || (b == GrB_INVALID_HANDLE)) return GrB_SUCCESS;

    delete *b;
    *b = (GrB_BinaryOp_t*)GrB_INVALID_HANDLE;

    return GrB_SUCCESS;
}

GrB_Info GrB_Monoid_free
(
    GrB_Monoid  *m
)
{
    if ((!m) || (m == GrB_INVALID_HANDLE)) return GrB_SUCCESS;

    delete *m;
    *m = (GrB_Monoid_t*)GrB_INVALID_HANDLE;

    return GrB_SUCCESS;
}

GrB_Info GrB_Semiring_free
(
    GrB_Semiring        *s
)
{
    if ((!s) || (s == GrB_INVALID_HANDLE)) return GrB_SUCCESS;

    delete *s;
    *s = (GrB_Semiring_t*)GrB_INVALID_HANDLE;

    return GrB_SUCCESS;
}

GrB_Info GrB_Descriptor_free
(
    GrB_Descriptor      *d
)
{
    if ((!d) || (d == GrB_INVALID_HANDLE)) return GrB_SUCCESS;

    delete *d;
    *d = (GrB_Descriptor_t*)GrB_INVALID_HANDLE;

    return GrB_SUCCESS;
}

GrB_Info GrB_Vector_free
(
    GrB_Vector  *v
)
{
    if ((!v) || (v == GrB_INVALID_HANDLE)) return GrB_SUCCESS;

    delete *v;
    *v = (GrB_Vector_t*)GrB_INVALID_HANDLE;

    return GrB_SUCCESS;
}

GrB_Info GrB_Matrix_free
(
    GrB_Matrix  *A
)
{
    if ((!A) || (A == GrB_INVALID_HANDLE)) return GrB_SUCCESS;

    delete *A;
    *A = (GrB_Matrix_t*)GrB_INVALID_HANDLE;

    return GrB_SUCCESS;
}

// Section 4.3.1 mxm

#include "template/GrB_mxm.cc"

// Section 4.3.2 vxm

GrB_Info GrB_vxm
(
    GrB_Vector              w,
    const GrB_Vector        mask,
    const GrB_BinaryOp      accum,
    const GrB_Semiring      op,
    const GrB_Vector        u,
    const GrB_Matrix        A,
    const GrB_Descriptor    desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!w)     || (w     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (mask  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!op)    || (op    == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!u)     || (u     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!A)     || (A     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (w     && (!w    ->valid())) return GrB_INVALID_OBJECT;
        if (mask  && (!mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (op    && (!op   ->valid())) return GrB_INVALID_OBJECT;
        if (u     && (!u    ->valid())) return GrB_INVALID_OBJECT;
        if (A     && (!A    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check domain conformity
        if (mask  && (!mask->D()->predefined())                ) return GrB_DOMAIN_MISMATCH;
        if (!u->D()->compatible(op->D_in_1())                  ) return GrB_DOMAIN_MISMATCH;
        if (!A->D()->compatible(op->D_in_2())                  ) return GrB_DOMAIN_MISMATCH;
        if (!w->D()->compatible(op->D_out())                   ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_in_1())     ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_out())      ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !op->D_out()->compatible(accum->D_in_2())) return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());
        bool tranA   = (desc && desc->inp1_tran());

        // Prepare internal matrices for operation
        GrB_Vector_t w_tilde(*w);
        GrB_mask_t   m_tilde(SCMP,mask,*w);
        GrB_Vector_t u_tilde(*u);
        GrB_Matrix_t A_tilde(tranA,*A);

        // Check dimension comformity
        if (w_tilde.size()  != m_tilde.size() ) return GrB_DIMENSION_MISMATCH;
        if (w_tilde.size()  != A_tilde.ncols()) return GrB_DIMENSION_MISMATCH;
        if (A_tilde.nrows() != u_tilde.size() ) return GrB_DIMENSION_MISMATCH;

        // Perform the multiplication
        GrB_Vector_t t_tilde(op->D_out(),w_tilde.size());
        t_tilde.axB(op,u_tilde,A_tilde);

        // Accumulate as necessary
        GrB_Vector_t z_tilde;
        accum ? z_tilde.init(accum->D_out(),w_tilde.size())
                && z_tilde.add(accum,w_tilde,t_tilde)
              : z_tilde.copy(t_tilde);

        // Mask and replace
        Replace ? w->replace(m_tilde,z_tilde) : w->merge(m_tilde,z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

// Section 4.3.3 mxv

GrB_Info GrB_mxv
(
    GrB_Vector              w,
    const GrB_Vector        mask,
    const GrB_BinaryOp      accum,
    const GrB_Semiring      op,
    const GrB_Matrix        A,
    const GrB_Vector        u,
    const GrB_Descriptor    desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!w)     || (w     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (mask  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!op)    || (op    == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!A)     || (A     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!u)     || (u     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (w     && (!w    ->valid())) return GrB_INVALID_OBJECT;
        if (mask  && (!mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (op    && (!op   ->valid())) return GrB_INVALID_OBJECT;
        if (A     && (!A    ->valid())) return GrB_INVALID_OBJECT;
        if (u     && (!u    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check domain conformity
        if (mask  && (!mask->D()->predefined())                ) return GrB_DOMAIN_MISMATCH;
        if (!A->D()->compatible(op->D_in_1())                  ) return GrB_DOMAIN_MISMATCH;
        if (!u->D()->compatible(op->D_in_2())                  ) return GrB_DOMAIN_MISMATCH;
        if (!w->D()->compatible(op->D_out())                   ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_in_1())     ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_out())      ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !op->D_out()->compatible(accum->D_in_2())) return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());
        bool tranA   = (desc && desc->inp0_tran());

        // Prepare internal matrices for operation
        GrB_Vector_t w_tilde(*w);
        GrB_mask_t   m_tilde(SCMP,mask,*w);
        GrB_Matrix_t A_tilde(tranA,*A);
        GrB_Vector_t u_tilde(*u);

        // Check dimension comformity
        if (w_tilde.size()  != m_tilde.size() ) return GrB_DIMENSION_MISMATCH;
        if (w_tilde.size()  != A_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (A_tilde.ncols() != u_tilde.size() ) return GrB_DIMENSION_MISMATCH;

        // Perform the multiplication
        GrB_Vector_t t_tilde(op->D_out(),w_tilde.size());
        t_tilde.Axb(op,A_tilde,u_tilde);

        // Accumulate as necessary
        GrB_Vector_t z_tilde;
        accum ? z_tilde.init(accum->D_out(),w_tilde.size())
                && z_tilde.add(accum,w_tilde,t_tilde)
              : z_tilde.copy(t_tilde);

        // Mask and replace
        Replace ? w->replace(m_tilde,z_tilde) : w->merge(m_tilde,z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

// Section 4.3.4 eWiseMult

template<class T>
static
GrB_Info GrB_Vector_eWiseMult_common
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const T                     *op,
    const GrB_Vector            u,
    const GrB_Vector            v,
    const GrB_Descriptor        desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!w)     || (w     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (mask  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!op)    || (op    == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!u)     || (u     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!v)     || (v     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (w     && (!w    ->valid())) return GrB_INVALID_OBJECT;
        if (mask  && (!mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (op    && (!op   ->valid())) return GrB_INVALID_OBJECT;
        if (u     && (!u    ->valid())) return GrB_INVALID_OBJECT;
        if (v     && (!v    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check domain conformity
        if (mask  && (!mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!u->D()->compatible(op->D_in_1()))                   return GrB_DOMAIN_MISMATCH;
        if (!v->D()->compatible(op->D_in_2()))                   return GrB_DOMAIN_MISMATCH;
        if (!w->D()->compatible(op->D_out()))                    return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !op->D_out()->compatible(accum->D_in_2())) return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());

        // Prepare internal vectors for operation
        GrB_Vector_t w_tilde(*w);
        GrB_mask_t   m_tilde(SCMP,mask,*w);
        GrB_Vector_t u_tilde(*u);
        GrB_Vector_t v_tilde(*v);

        // Check dimension comformity
        if (w_tilde.size() != m_tilde.size()) return GrB_DIMENSION_MISMATCH;
        if (w_tilde.size() != u_tilde.size()) return GrB_DIMENSION_MISMATCH;
        if (w_tilde.size() != v_tilde.size()) return GrB_DIMENSION_MISMATCH;

        // Perform the multiplication
        GrB_Vector_t t_tilde(op->D_out(),u_tilde.size());
        t_tilde.mul(op,u_tilde,v_tilde);

        // Accumulate as necessary
        GrB_Vector_t z_tilde;
        accum ?  z_tilde.init(accum->D_out(),w_tilde.size()) && z_tilde.add(accum,w_tilde,t_tilde) : z_tilde.copy(t_tilde);

        // Mask and replace
        Replace ? w->replace(m_tilde,z_tilde) : w->merge(m_tilde,z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Vector_eWiseMult_Semiring
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const GrB_Semiring          op,
    const GrB_Vector            u,
    const GrB_Vector            v,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_eWiseMult_common(w,mask,accum,op,u,v,desc);
}

GrB_Info GrB_Vector_eWiseMult_Monoid
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const GrB_Monoid            op,
    const GrB_Vector            u,
    const GrB_Vector            v,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_eWiseMult_common(w,mask,accum,op,u,v,desc);
}

GrB_Info GrB_Vector_eWiseMult_BinaryOp
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const GrB_BinaryOp          op,
    const GrB_Vector            u,
    const GrB_Vector            v,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_eWiseMult_common(w,mask,accum,op,u,v,desc);
}

template<class T>
static
GrB_Info GrB_Matrix_eWiseMult_common
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    const T                     *op,
    const GrB_Matrix            A,
    const GrB_Matrix            B,
    const GrB_Descriptor        desc
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
        if (Mask  && (!Mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!A->D()->compatible(op->D_in_1()))                   return GrB_DOMAIN_MISMATCH;
        if (!B->D()->compatible(op->D_in_2()))                   return GrB_DOMAIN_MISMATCH;
        if (!C->D()->compatible(op->D_out()))                    return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !op->D_out()->compatible(accum->D_in_2())) return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());
        bool tranA   = (desc && desc->inp0_tran());
        bool tranB   = (desc && desc->inp1_tran());

        // Prepare internal Bectors for operation
        GrB_Matrix_t C_tilde(*C);
        GrB_Mask_t   M_tilde(SCMP,Mask,*C);
        GrB_Matrix_t A_tilde(tranA,*A);
        GrB_Matrix_t B_tilde(tranB,*B);

        // Check dimension comformity
        if (C_tilde.nrows() != M_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != M_tilde.ncols()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.nrows() != A_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != A_tilde.ncols()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.nrows() != B_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != B_tilde.ncols()) return GrB_DIMENSION_MISMATCH;

        // Perform the multiplication
        GrB_Matrix_t T_tilde(op->D_out(),A_tilde.nrows(),A_tilde.ncols());
        T_tilde.mul(op,A_tilde,B_tilde);

        // Accumulate as necessary
        GrB_Matrix_t Z_tilde;
        accum ?  Z_tilde.init(accum->D_out(),C_tilde.nrows(),C_tilde.ncols()) && Z_tilde.add(accum,C_tilde,T_tilde) : Z_tilde.copy(T_tilde);

        // Mask and replace
        Replace ? C->replace(M_tilde,Z_tilde) : C->merge(M_tilde,Z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Matrix_eWiseMult_Semiring
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    const GrB_Semiring          op,
    const GrB_Matrix            A,
    const GrB_Matrix            B,
    const GrB_Descriptor        desc
)
{
    return GrB_Matrix_eWiseMult_common(C,Mask,accum,op,A,B,desc);
}

GrB_Info GrB_Matrix_eWiseMult_Monoid
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    const GrB_Monoid            op,
    const GrB_Matrix            A,
    const GrB_Matrix            B,
    const GrB_Descriptor        desc
)
{
    return GrB_Matrix_eWiseMult_common(C,Mask,accum,op,A,B,desc);
}

GrB_Info GrB_Matrix_eWiseMult_BinaryOp
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    const GrB_BinaryOp          op,
    const GrB_Matrix            A,
    const GrB_Matrix            B,
    const GrB_Descriptor        desc
)
{
    return GrB_Matrix_eWiseMult_common(C,Mask,accum,op,A,B,desc);
}

// Section 4.3.5 eWiseAdd

template<class T>
static
GrB_Info GrB_Vector_eWiseAdd_common
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const T                     *op,
    const GrB_Vector            u,
    const GrB_Vector            v,
    const GrB_Descriptor        desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!w)     || (w     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (mask  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!op)    || (op    == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!u)     || (u     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!v)     || (v     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (w     && (!w    ->valid())) return GrB_INVALID_OBJECT;
        if (mask  && (!mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (op    && (!op   ->valid())) return GrB_INVALID_OBJECT;
        if (u     && (!u    ->valid())) return GrB_INVALID_OBJECT;
        if (v     && (!v    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check domain conformity
        if (mask  && (!mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!u->D()->compatible(op->D_in_1()))                   return GrB_DOMAIN_MISMATCH;
        if (!v->D()->compatible(op->D_in_2()))                   return GrB_DOMAIN_MISMATCH;
        if (!w->D()->compatible(op->D_out()))                    return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !op->D_out()->compatible(accum->D_in_2())) return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());

        // Prepare internal vectors for operation
        GrB_Vector_t w_tilde(*w);
        GrB_mask_t   m_tilde(SCMP,mask,*w);
        GrB_Vector_t u_tilde(*u);
        GrB_Vector_t v_tilde(*v);

        // Check dimension comformity
        if (w_tilde.size() != m_tilde.size()) return GrB_DIMENSION_MISMATCH;
        if (w_tilde.size() != u_tilde.size()) return GrB_DIMENSION_MISMATCH;
        if (w_tilde.size() != v_tilde.size()) return GrB_DIMENSION_MISMATCH;

        // Perform the addition
        GrB_Vector_t t_tilde(op->D_out(),u_tilde.size());
        t_tilde.add(op,u_tilde,v_tilde);

        // Accumulate as necessary
        GrB_Vector_t z_tilde;
        accum ?  z_tilde.init(accum->D_out(),w_tilde.size()) && z_tilde.add(accum,w_tilde,t_tilde) : z_tilde.copy(t_tilde);

        // Mask and replace
        Replace ? w->replace(m_tilde,z_tilde) : w->merge(m_tilde,z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Vector_eWiseAdd_Semiring
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const GrB_Semiring          op,
    const GrB_Vector            u,
    const GrB_Vector            v,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_eWiseAdd_common(w,mask,accum,op,u,v,desc);
}

GrB_Info GrB_Vector_eWiseAdd_Monoid
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const GrB_Monoid            op,
    const GrB_Vector            u,
    const GrB_Vector            v,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_eWiseAdd_common(w,mask,accum,op,u,v,desc);
}

GrB_Info GrB_Vector_eWiseAdd_BinaryOp
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const GrB_BinaryOp          op,
    const GrB_Vector            u,
    const GrB_Vector            v,
    const GrB_Descriptor        desc
)
{
    return GrB_Vector_eWiseAdd_common(w,mask,accum,op,u,v,desc);
}

template<class T>
static
GrB_Info GrB_Matrix_eWiseAdd_common
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    const T                     *op,
    const GrB_Matrix            A,
    const GrB_Matrix            B,
    const GrB_Descriptor        desc
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
        if (Mask  && (!Mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!A->D()->compatible(op->D_in_1()))                   return GrB_DOMAIN_MISMATCH;
        if (!B->D()->compatible(op->D_in_2()))                   return GrB_DOMAIN_MISMATCH;
        if (!C->D()->compatible(op->D_out()))                    return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !op->D_out()->compatible(accum->D_in_2())) return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());
        bool tranA   = (desc && desc->inp0_tran());
        bool tranB   = (desc && desc->inp1_tran());

        // Prepare internal Bectors for operation
        GrB_Matrix_t C_tilde(*C);
        GrB_Mask_t   M_tilde(SCMP,Mask,*C);
        GrB_Matrix_t A_tilde(tranA,*A);
        GrB_Matrix_t B_tilde(tranB,*B);

        // Check dimension comformity
        if (C_tilde.nrows() != M_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != M_tilde.ncols()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.nrows() != A_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != A_tilde.ncols()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.nrows() != B_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != B_tilde.ncols()) return GrB_DIMENSION_MISMATCH;

        // Perform the addition
        GrB_Matrix_t T_tilde(op->D_out(),A_tilde.nrows(),A_tilde.ncols());
        T_tilde.add(op,A_tilde,B_tilde);

        // Accumulate as necessary
        GrB_Matrix_t Z_tilde;
        accum ?  Z_tilde.init(accum->D_out(),C_tilde.nrows(),C_tilde.ncols()) && Z_tilde.add(accum,C_tilde,T_tilde) : Z_tilde.copy(T_tilde);

        // Mask and replace
        Replace ? C->replace(M_tilde,Z_tilde) : C->merge(M_tilde,Z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Matrix_eWiseAdd_Semiring
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    const GrB_Semiring          op,
    const GrB_Matrix            A,
    const GrB_Matrix            B,
    const GrB_Descriptor        desc
)
{
    return GrB_Matrix_eWiseAdd_common(C,Mask,accum,op,A,B,desc);
}

GrB_Info GrB_Matrix_eWiseAdd_Monoid
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    const GrB_Monoid            op,
    const GrB_Matrix            A,
    const GrB_Matrix            B,
    const GrB_Descriptor        desc
)
{
    return GrB_Matrix_eWiseAdd_common(C,Mask,accum,op,A,B,desc);
}

GrB_Info GrB_Matrix_eWiseAdd_BinaryOp
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    const GrB_BinaryOp          op,
    const GrB_Matrix            A,
    const GrB_Matrix            B,
    const GrB_Descriptor        desc
)
{
    return GrB_Matrix_eWiseAdd_common(C,Mask,accum,op,A,B,desc);
}

// Section 4.3.6 extract

GrB_Info GrB_Vector_extract
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const GrB_Vector            u,
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
        if ((!u)     || (u     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (w     && (!w    ->valid())) return GrB_INVALID_OBJECT;
        if (mask  && (!mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (u     && (!u    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check for null pointers
        if (!indices) return GrB_NULL_POINTER;

        // Check domain conformity
        if (mask  && (!mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!w->D()->compatible(u->D()))                         return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !u->D()->compatible(accum->D_in_2()))        return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());

        // Prepare internal vectors for operation
        GrB_Vector_t      w_tilde(*w);
        GrB_mask_t        m_tilde(SCMP,mask,*w);
        GrB_Vector_t      u_tilde(*u);
        vector<GrB_Index> I_tilde(nindices); 
        for (GrB_Index i=0; i<nindices; i++) I_tilde[i] = indices == GrB_ALL ? i : indices[i];

        // Check dimension comformity
        if (w_tilde.size() != m_tilde.size()) return GrB_DIMENSION_MISMATCH;
        if (nindices != w_tilde.size())       return GrB_DIMENSION_MISMATCH;

        // Create the extract vector
        GrB_Vector_t t_tilde(u->D(), w_tilde.size());
        for (GrB_Index i=0; i<nindices; i++) 
            if (u_tilde.ind()->count(I_tilde[i])) t_tilde.addElement(i,u_tilde[I_tilde[i]]);
        
        // Accumulate as necessary
        GrB_Vector_t z_tilde;
        accum ?  z_tilde.init(accum->D_out(),w_tilde.size()) && z_tilde.add(accum,w_tilde,t_tilde) : z_tilde.copy(t_tilde);

        // Mask and replace
        Replace ? w->replace(m_tilde,z_tilde) : w->merge(m_tilde,z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Matrix_extract
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    const GrB_Matrix            A,
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
        if ((!A)     || (A     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (C     && (!C    ->valid())) return GrB_INVALID_OBJECT;
        if (Mask  && (!Mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (A     && (!A    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check for null pointers
        if (!row_indices) return GrB_NULL_POINTER;
        if (!col_indices) return GrB_NULL_POINTER;

        // Check domain conformity
        if (Mask  && (!Mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!C->D()->compatible(A->D()))                         return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !A->D()->compatible(accum->D_in_2()))      return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());
        bool tranA   = (desc && desc->inp0_tran());

        // Prepare internal vectors for operation
        GrB_Matrix_t      C_tilde(*C);
        GrB_Mask_t        M_tilde(SCMP,Mask,*C);
        GrB_Matrix_t      A_tilde(tranA,*A);
        vector<GrB_Index> I_tilde(nrows);
        for (GrB_Index i=0; i<nrows; i++) I_tilde[i] = (row_indices == GrB_ALL) ? i : row_indices[i];
        vector<GrB_Index> J_tilde(ncols);
        for (GrB_Index j=0; j<ncols; j++) J_tilde[j] = (col_indices == GrB_ALL) ? j : col_indices[j];

        // Check dimension comformity
        if (C_tilde.nrows() != M_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != M_tilde.ncols()) return GrB_DIMENSION_MISMATCH;
        if (nrows != C_tilde.nrows())           return GrB_DIMENSION_MISMATCH;
        if (ncols != C_tilde.ncols())           return GrB_DIMENSION_MISMATCH;

        // Perform the extract
        GrB_Matrix_t T_tilde(A->D(),C_tilde.nrows(),C_tilde.ncols());
        for (GrB_Index i=0; i<nrows; i++)
            for (GrB_Index j=0; j<ncols; j++)
                if (A_tilde[I_tilde[i]].ind()->count(J_tilde[j])) T_tilde.addElement(i,j,A_tilde[I_tilde[i]][J_tilde[j]]);

        // Accumulate as necessary
        GrB_Matrix_t Z_tilde;
        accum ?  Z_tilde.init(accum->D_out(),C_tilde.nrows(),C_tilde.ncols()) && Z_tilde.add(accum,C_tilde,T_tilde) : Z_tilde.copy(T_tilde);

        // Mask and replace
        Replace ? C->replace(M_tilde,Z_tilde) : C->merge(M_tilde,Z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Col_extract
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const GrB_Matrix            A,
    const GrB_Index            *row_indices,
    GrB_Index                   nrows,
    GrB_Index                   col_index,
    const GrB_Descriptor        desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!w)     || (w     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (mask  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!A)     || (A     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (w     && (!w    ->valid())) return GrB_INVALID_OBJECT;
        if (mask  && (!mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (A     && (!A    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check for null pointers
        if (!row_indices) return GrB_NULL_POINTER;

        // Check domain conformity
        if (mask  && (!mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!w->D()->compatible(A->D()))                         return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !A->D()->compatible(accum->D_in_2()))      return GrB_DOMAIN_MISMATCH;

        // Check valid column index
        if (col_index >= A->ncols()) return GrB_INVALID_INDEX;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());
        bool tranA   = (desc && desc->inp0_tran());

        // Prepare internal vectors for operation
        GrB_Vector_t      w_tilde(*w);
        GrB_mask_t        m_tilde(SCMP,mask,*w);
        GrB_Matrix_t      A_tilde(tranA,*A);
        vector<GrB_Index> I_tilde(nrows);
        for (GrB_Index i=0; i<nrows; i++) I_tilde[i] = (row_indices == GrB_ALL) ? i : row_indices[i];

        // Check dimension comformity
        if (w_tilde.size() != m_tilde.size()) return GrB_DIMENSION_MISMATCH;
        if (nrows != w_tilde.size())          return GrB_DIMENSION_MISMATCH;

        // Create the extract vector
        GrB_Vector_t t_tilde(A->D(), nrows);
        for (GrB_Index i=0; i<nrows; i++) 
            if (A_tilde(col_index).ind()->count(I_tilde[i])) t_tilde.addElement(i,A_tilde[I_tilde[i]][col_index]);
        
        // Accumulate as necessary
        GrB_Vector_t z_tilde;
        accum ?  z_tilde.init(accum->D_out(),w_tilde.size()) && z_tilde.add(accum,w_tilde,t_tilde) : z_tilde.copy(t_tilde);

        // Mask and replace
        Replace ? w->replace(m_tilde,z_tilde) : w->merge(m_tilde,z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

// Section 4.3.7 assign

GrB_Info GrB_Vector_assign
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const GrB_Vector            u,
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
        if ((!u)     || (u     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (w     && (!w    ->valid())) return GrB_INVALID_OBJECT;
        if (mask  && (!mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (u     && (!u    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check for null pointers
        if (!indices) return GrB_NULL_POINTER;

        // Check domain conformity
        if (mask  && (!mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!w->D()->compatible(u->D()))                         return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !u->D()->compatible(accum->D_in_2()))        return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());

        // Prepare internal vectors for operation
        GrB_Vector_t      w_tilde(*w);
        GrB_mask_t        m_tilde(SCMP,mask,*w);
        GrB_Vector_t      u_tilde(*u);
        vector<GrB_Index> I_tilde(nindices); 
        for (GrB_Index i=0; i<nindices; i++) I_tilde[i] = indices == GrB_ALL ? i : indices[i];

        // Check dimension comformity
        if (w_tilde.size() != m_tilde.size()) return GrB_DIMENSION_MISMATCH;
        if (nindices != u_tilde.size())       return GrB_DIMENSION_MISMATCH;

        // Create the assignment vector
        GrB_Vector_t t_tilde(u->D(), w_tilde.size());
        for (auto i : *(u_tilde.ind())) t_tilde.addElement(I_tilde[i],u_tilde[i]);
        
        // Accumulate as necessary
        GrB_Vector_t z_tilde;
        if (accum)
        {
            z_tilde.init(accum->D_out(),w_tilde.size());
            z_tilde.add(accum,w_tilde,t_tilde);
        }
        else
        {
            z_tilde.init(w->D(),w_tilde.size());
            for (auto i : *(w_tilde.ind()) - (I_tilde * (*(w_tilde.ind())))) z_tilde.addElement(i,w_tilde[i]);
            for (auto i : *(t_tilde.ind())) { z_tilde.clear(i); z_tilde.addElement(i,t_tilde[i](w->D())); }
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

GrB_Info GrB_Matrix_assign
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    const GrB_Matrix            A,
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
        if ((!A)     || (A     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (C     && (!C    ->valid())) return GrB_INVALID_OBJECT;
        if (Mask  && (!Mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (A     && (!A    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check for null pointers
        if (!row_indices) return GrB_NULL_POINTER;
        if (!col_indices) return GrB_NULL_POINTER;

        // Check domain conformity
        if (Mask  && (!Mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!C->D()->compatible(A->D()))                         return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !A->D()->compatible(accum->D_in_2()))      return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool SCMP    = (desc && desc->mask_scmp());
        bool tranA   = (desc && desc->inp0_tran());

        // Prepare internal vectors for operation
        GrB_Matrix_t      C_tilde(*C);
        GrB_Mask_t        M_tilde(SCMP,Mask,*C);
        GrB_Matrix_t      A_tilde(tranA,*A);
        vector<GrB_Index> I_tilde(nrows);
        for (GrB_Index i=0; i<nrows; i++) I_tilde[i] = (row_indices == GrB_ALL) ? i : row_indices[i];

        // Check dimension comformity
        if (C_tilde.nrows() != M_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != M_tilde.ncols()) return GrB_DIMENSION_MISMATCH;
        if (nrows != A_tilde.nrows())           return GrB_DIMENSION_MISMATCH;
        if (ncols != A_tilde.ncols())           return GrB_DIMENSION_MISMATCH;

        // Perform the assignment
        for (GrB_Index i=0; i<nrows; i++)
            GrB_Row_assign(C,Mask?((const GrB_Vector)&((*Mask)[i])):0,accum,(const GrB_Vector)&(A_tilde[i]),I_tilde[i],col_indices,ncols,desc);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Col_assign
(
    GrB_Matrix                  C,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const GrB_Vector            u,
    const GrB_Index            *row_indices,
    GrB_Index                   nrows,
    GrB_Index                   col_index,
    const GrB_Descriptor        desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!C)     || (C     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (mask  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!u)     || (u     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (C     && (!C    ->valid())) return GrB_INVALID_OBJECT;
        if (mask  && (!mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (u     && (!u    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check for null pointers
        if (!row_indices) return GrB_NULL_POINTER;

        // Check domain conformity
        if (mask  && (!mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!C->D()->compatible(u->D()))                         return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !u->D()->compatible(accum->D_in_2()))      return GrB_DOMAIN_MISMATCH;

        // Check valid column index
        if (col_index >= C->ncols()) return GrB_INVALID_INDEX;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());

        // Prepare internal vectors for operation
        GrB_Vector_t      c_tilde((*C)(col_index));
        GrB_mask_t        m_tilde(SCMP,mask,c_tilde);
        GrB_Vector_t      u_tilde(*u);
        vector<GrB_Index> I_tilde(nrows);
        for (GrB_Index i=0; i<nrows; i++) I_tilde[i] = (row_indices == GrB_ALL) ? i : row_indices[i];

        // Check dimension comformity
        if (c_tilde.size() != m_tilde.size()) return GrB_DIMENSION_MISMATCH;
        if (nrows != u_tilde.size())          return GrB_DIMENSION_MISMATCH;

        // Create the assignment vector
        GrB_Vector_t t_tilde(u->D(), c_tilde.size());
        for (auto i : *(u_tilde.ind())) t_tilde.addElement(I_tilde[i],u_tilde[i]);

        // Accumulate as necessary
        GrB_Vector_t z_tilde;
        if (accum)
        {
            z_tilde.init(accum->D_out(),c_tilde.size());
            z_tilde.add(accum,c_tilde,t_tilde);
        }
        else
        {
            z_tilde.init(C->D(),c_tilde.size());
            for (auto i : *(c_tilde.ind()) - (I_tilde * (*(c_tilde.ind())))) z_tilde.addElement(i,c_tilde[i]);
            for (auto i : *(t_tilde.ind())) { z_tilde.clear(i); z_tilde.addElement(i,t_tilde[i](C->D())); }
        }

        // Mask and replace
        if (Replace || m_tilde.full()) { uset<GrB_Index> ind = *((*C)(col_index).ind()); for (auto i : ind)                C->clear(i,col_index); }
        else                           {                                                 for (auto i : (*(m_tilde.ind()))) C->clear(i,col_index); }
        if (m_tilde.full()) for (auto i : (*(z_tilde.ind()))) C->addElement(i,col_index,z_tilde[i](C->D()));
        else                for (auto i : (*(m_tilde.ind())) * (*(z_tilde.ind()))) C->addElement(i,col_index,z_tilde[i](C->D()));

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Row_assign
(
    GrB_Matrix                  C,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const GrB_Vector            u,
    GrB_Index                   row_index,
    const GrB_Index            *col_indices,
    GrB_Index                   ncols,
    const GrB_Descriptor        desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!C)     || (C     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (mask  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!u)     || (u     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (C     && (!C    ->valid())) return GrB_INVALID_OBJECT;
        if (mask  && (!mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (u     && (!u    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check for null pointers
        if (!col_indices) return GrB_NULL_POINTER;

        // Check domain conformity
        if (mask  && (!mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!C->D()->compatible(u->D()))                         return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !u->D()->compatible(accum->D_in_2()))      return GrB_DOMAIN_MISMATCH;

        // Check valid column index
        if (row_index >= C->nrows()) return GrB_INVALID_INDEX;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());

        // Prepare internal vectors for operation
        GrB_Vector_t      c_tilde((*C)[row_index]);
        GrB_mask_t        m_tilde(SCMP,mask,c_tilde);
        GrB_Vector_t      u_tilde(*u);
        vector<GrB_Index> I_tilde(ncols);
        for (GrB_Index i=0; i<ncols; i++) I_tilde[i] = (col_indices == GrB_ALL) ? i : col_indices[i];

        // Check dimension comformity
        if (c_tilde.size() != m_tilde.size()) return GrB_DIMENSION_MISMATCH;
        if (ncols != u_tilde.size())          return GrB_DIMENSION_MISMATCH;

        // Create the assignment vector
        GrB_Vector_t t_tilde(u->D(), c_tilde.size());
        for (auto i : *(u_tilde.ind())) t_tilde.addElement(I_tilde[i],u_tilde[i]);

        // Accumulate as necessary
        GrB_Vector_t z_tilde;
        if (accum)
        {
            z_tilde.init(accum->D_out(),c_tilde.size());
            z_tilde.add(accum,c_tilde,t_tilde);
        }
        else
        {
            z_tilde.init(C->D(),c_tilde.size());
            for (auto i : *(c_tilde.ind()) - (I_tilde * (*(c_tilde.ind())))) z_tilde.addElement(i,c_tilde[i]);
            for (auto i : *(t_tilde.ind())) { z_tilde.clear(i); z_tilde.addElement(i,t_tilde[i](C->D())); }
        }

        // Mask and replace
        if (Replace || m_tilde.full()) { uset<GrB_Index> ind = *((*C)[row_index].ind()); for (auto j : ind)                C->clear(row_index,j); }
        else                           {                                                 for (auto j : (*(m_tilde.ind()))) C->clear(row_index,j); }
        if (m_tilde.full()) for (auto j : (*(z_tilde.ind()))) C->addElement(row_index,j,z_tilde[j](C->D()));
        else                for (auto j : (*(m_tilde.ind())) * (*(z_tilde.ind()))) C->addElement(row_index,j,z_tilde[j](C->D()));

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

#include "template/GrB_Vector_assign.cc"
#include "template/GrB_Matrix_assign.cc"

// Section 4.3.8 apply

GrB_Info GrB_Vector_apply
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const GrB_UnaryOp           op,
    const GrB_Vector            u,
    const GrB_Descriptor        desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!w)     || (w     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (mask  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!op)    || (op    == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!u)     || (u     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (w     && (!w    ->valid())) return GrB_INVALID_OBJECT;
        if (mask  && (!mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (op    && (!op   ->valid())) return GrB_INVALID_OBJECT;
        if (u     && (!u    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check domain conformity
        if (mask  && (!mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!u->D()->compatible(op->D_in()))                     return GrB_DOMAIN_MISMATCH;
        if (!w->D()->compatible(op->D_out()))                    return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !op->D_out()->compatible(accum->D_in_2())) return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());

        // Prepare internal vectors for operation
        GrB_Vector_t w_tilde(*w);
        GrB_mask_t   m_tilde(SCMP,mask,*w);
        GrB_Vector_t u_tilde(*u);

        // Check dimension comformity
        if (w_tilde.size() != m_tilde.size()) return GrB_DIMENSION_MISMATCH;
        if (w_tilde.size() != u_tilde.size()) return GrB_DIMENSION_MISMATCH;

        // Perform the operation
        GrB_Vector_t t_tilde(op->D_out(),u_tilde.size());
        Scalar out(op->D_out());
        for (auto i : *(u_tilde.ind()))
        {
            op->f(out,u_tilde[i]);
            t_tilde.addElement(i,out);
        }

        // Accumulate as necessary
        GrB_Vector_t z_tilde;
        accum ?  z_tilde.init(accum->D_out(),w_tilde.size()) && z_tilde.add(accum,w_tilde,t_tilde) : z_tilde.copy(t_tilde);

        // Mask and replace
        Replace ? w->replace(m_tilde,z_tilde) : w->merge(m_tilde,z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Matrix_apply
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    const GrB_UnaryOp           op,
    const GrB_Matrix            A,
    const GrB_Descriptor        desc
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
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (C     && (!C    ->valid())) return GrB_INVALID_OBJECT;
        if (Mask  && (!Mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (op    && (!op   ->valid())) return GrB_INVALID_OBJECT;
        if (A     && (!A    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check domain conformity
        if (Mask  && (!Mask->D()->predefined()))                 return GrB_DOMAIN_MISMATCH;
        if (!A->D()->compatible(op->D_in()))                     return GrB_DOMAIN_MISMATCH;
        if (!C->D()->compatible(op->D_out()))                    return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_in_1()))      return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_out()))       return GrB_DOMAIN_MISMATCH;
        if (accum  && !op->D_out()->compatible(accum->D_in_2())) return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());
        bool tranA   = (desc && desc->inp0_tran());

        // Prepare internal vectors for operation
        GrB_Matrix_t C_tilde(*C);
        GrB_Mask_t   M_tilde(SCMP,Mask,*C);
        GrB_Matrix_t A_tilde(tranA,*A);

        // Check dimension comformity
        if (C_tilde.nrows() != M_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != M_tilde.ncols()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.nrows() != A_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != A_tilde.ncols()) return GrB_DIMENSION_MISMATCH;

        // Perform the operation
        GrB_Matrix_t T_tilde(op->D_out(),A_tilde.nrows(),A_tilde.ncols());
        Scalar out(op->D_out());
        for (GrB_Index i=0; i<A_tilde.nrows(); i++)
        {
            for (auto j : *(A_tilde[i].ind()))
            {
                op->f(out,A_tilde[i][j]);
                T_tilde.addElement(i,j,out);
            }
        }

        // Accumulate as necessary
        GrB_Matrix_t Z_tilde;
        accum ?  Z_tilde.init(accum->D_out(),C_tilde.nrows(),C_tilde.ncols()) && Z_tilde.add(accum,C_tilde,T_tilde) : Z_tilde.copy(T_tilde);

        // Mask and replace
        Replace ? C->replace(M_tilde,Z_tilde) : C->merge(M_tilde,Z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

// Section 4.3.9 reduce

GrB_Info GrB_Matrix_reduce_Monoid
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const GrB_Monoid            op,
    const GrB_Matrix            A,
    const GrB_Descriptor        desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!w)     || (w     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (mask  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!op)    || (op    == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!A)     || (A     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (w     && (!w    ->valid())) return GrB_INVALID_OBJECT;
        if (mask  && (!mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (op    && (!op   ->valid())) return GrB_INVALID_OBJECT;
        if (A     && (!A    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check domain conformity
        if (mask  && (!mask->D()->predefined())            ) return GrB_DOMAIN_MISMATCH;
        if (!A->D()->compatible(op->D())                   ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_in_1()) ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_out())  ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !op->D()->compatible(accum->D_in_2())) return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());
        bool tranA   = (desc && desc->inp0_tran());

        // Prepare internal matrices for operation
        GrB_Vector_t w_tilde(*w);
        GrB_mask_t   m_tilde(SCMP,mask,*w);
        GrB_Matrix_t A_tilde(tranA,*A);

        // Check dimension comformity
        if (w_tilde.size()  != m_tilde.size() ) return GrB_DIMENSION_MISMATCH;
        if (w_tilde.size()  != A_tilde.nrows()) return GrB_DIMENSION_MISMATCH;

        // Perform the reduction
        GrB_Vector_t t_tilde(op->D(),w_tilde.size());
        for (GrB_Index i=0; i<A_tilde.nrows(); i++)
        {
            if (A_tilde[i].ind()->size() == 0) continue;
            Scalar sum = op->zero();
            for (auto j : *(A_tilde[i].ind()))
            {
                op->f(sum,sum,A_tilde[i][j](op->D()));
            }
            t_tilde.addElement(i,sum);
        }

        // Accumulate as necessary
        GrB_Vector_t z_tilde;
        accum ? z_tilde.init(accum->D_out(),w_tilde.size())
                && z_tilde.add(accum,w_tilde,t_tilde)
              : z_tilde.copy(t_tilde);

        // Mask and replace
        Replace ? w->replace(m_tilde,z_tilde) : w->merge(m_tilde,z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

GrB_Info GrB_Matrix_reduce_BinaryOp
(
    GrB_Vector                  w,
    const GrB_Vector            mask,
    const GrB_BinaryOp          accum,
    const GrB_BinaryOp          op,
    const GrB_Matrix            A,
    const GrB_Descriptor        desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!w)     || (w     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (mask  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!op)    || (op    == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!A)     || (A     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (w     && (!w    ->valid())) return GrB_INVALID_OBJECT;
        if (mask  && (!mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (op    && (!op   ->valid())) return GrB_INVALID_OBJECT;
        if (A     && (!A    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check domain conformity
        if (mask  && (!mask->D()->predefined())                ) return GrB_DOMAIN_MISMATCH;
        if (!A->D()->compatible(op->D_in_1())                  ) return GrB_DOMAIN_MISMATCH;
        if (!A->D()->compatible(op->D_in_2())                  ) return GrB_DOMAIN_MISMATCH;
        if (!w->D()->compatible(op->D_out())                   ) return GrB_DOMAIN_MISMATCH;
        if (op->D_out() != op->D_in_1()                        ) return GrB_DOMAIN_MISMATCH;
        if (op->D_out() != op->D_in_2()                        ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_in_1())     ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !w->D()->compatible(accum->D_out())      ) return GrB_DOMAIN_MISMATCH;
        if (accum  && !op->D_out()->compatible(accum->D_in_2())) return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());
        bool tranA   = (desc && desc->inp0_tran());

        // Prepare internal matrices for operation
        GrB_Vector_t w_tilde(*w);
        GrB_mask_t   m_tilde(SCMP,mask,*w);
        GrB_Matrix_t A_tilde(tranA,*A);

        // Check dimension comformity
        if (w_tilde.size()  != m_tilde.size() ) return GrB_DIMENSION_MISMATCH;
        if (w_tilde.size()  != A_tilde.nrows()) return GrB_DIMENSION_MISMATCH;

        // Perform the reduction
        GrB_Vector_t t_tilde(op->D_out(),w_tilde.size());
        for (GrB_Index i=0; i<A_tilde.nrows(); i++)
        {
            if (A_tilde[i].ind()->size() == 0) continue;
            bool first = true;
            Scalar sum(op->D_out());
            for (auto j : *(A_tilde[i].ind()))
            {
                if (first) sum = A_tilde[i][j](op->D_out());
                else op->f(sum,sum,A_tilde[i][j](op->D_in_2()));
                first = false;
            }
            t_tilde.addElement(i,sum);
        }

        // Accumulate as necessary
        GrB_Vector_t z_tilde;
        accum ? z_tilde.init(accum->D_out(),w_tilde.size())
                && z_tilde.add(accum,w_tilde,t_tilde)
              : z_tilde.copy(t_tilde);

        // Mask and replace
        Replace ? w->replace(m_tilde,z_tilde) : w->merge(m_tilde,z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

#include "template/GrB_Vector_reduce.cc"
#include "template/GrB_Matrix_reduce.cc"

// Section 4.3.10 transpose

GrB_Info GrB_transpose
(
    GrB_Matrix                  C,
    const GrB_Matrix            Mask,
    const GrB_BinaryOp          accum,
    const GrB_Matrix            A,
    const GrB_Descriptor        desc
)
{
    try
    {
        // Check that the input objects are initialized
        if ((!C)     || (C     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (Mask  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (accum == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if ((!A)     || (A     == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;
        if (            (desc  == GrB_INVALID_HANDLE)) return GrB_UNINITIALIZED_OBJECT;

        // Check that the objects are valid
        if (C     && (!C    ->valid())) return GrB_INVALID_OBJECT;
        if (Mask  && (!Mask ->valid())) return GrB_INVALID_OBJECT;
        if (accum && (!accum->valid())) return GrB_INVALID_OBJECT;
        if (A     && (!A    ->valid())) return GrB_INVALID_OBJECT;
        if (desc  && (!desc ->valid())) return GrB_INVALID_OBJECT;

        // Check domain conformity
        if (Mask  && (!Mask->D()->predefined()))            return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_in_1())) return GrB_DOMAIN_MISMATCH;
        if (accum  && !C->D()->compatible(accum->D_out()))  return GrB_DOMAIN_MISMATCH;
        if (accum  && !A->D()->compatible(accum->D_in_2())) return GrB_DOMAIN_MISMATCH;

        // Decode descriptor
        bool Replace = (desc && desc->outp_replace());
        bool SCMP    = (desc && desc->mask_scmp());
        bool tranA   = (desc && desc->inp0_tran());

        // Prepare internal vectors for operation
        GrB_Matrix_t C_tilde(*C);
        GrB_Mask_t   M_tilde(SCMP,Mask,*C);
        GrB_Matrix_t A_tilde(tranA,*A);

        // Check dimension comformity
        if (C_tilde.nrows() != M_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != M_tilde.ncols()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.nrows() != A_tilde.nrows()) return GrB_DIMENSION_MISMATCH;
        if (C_tilde.ncols() != A_tilde.ncols()) return GrB_DIMENSION_MISMATCH;

        // Perform the operation
        GrB_Matrix_t T_tilde(A->D(),A_tilde.ncols(),A_tilde.nrows());
        T_tilde.transpose(A_tilde);

        // Accumulate as necessary
        GrB_Matrix_t Z_tilde;
        accum ?  Z_tilde.init(accum->D_out(),C_tilde.nrows(),C_tilde.ncols()) && Z_tilde.add(accum,C_tilde,T_tilde) : Z_tilde.copy(T_tilde);

        // Mask and replace
        Replace ? C->replace(M_tilde,Z_tilde) : C->merge(M_tilde,Z_tilde);

        return GrB_SUCCESS;
    }
    catch (const Exception& e)
    {
        return e.info();
    }
}

// Section 4.4.2 error

const char *GrB_error
(
)
{
    static const char *nullstr = "";
    return nullstr;
}

// Helper operations

void uset_intersection(uset<GrB_Index>& y, const uset<GrB_Index>& a, const uset<GrB_Index>& b)
{
    assert(&y != &a); assert(&y != &b);

    y.clear();
    for (auto it = a.begin(); it != a.end(); ++it)
    {
        if (b.count(*it)) y.insert(*it);
    }
}

void uset_difference(uset<GrB_Index>& y, const uset<GrB_Index>& a, const uset<GrB_Index>& b)
{
    assert(&y != &a); assert(&y != &b);

    y.clear();
    for (auto it = a.begin(); it != a.end(); ++it)
    {
        if (!b.count(*it)) y.insert(*it);
    }
}

uset<GrB_Index> operator*
(
    const uset<GrB_Index>& a, 
    const uset<GrB_Index>& b
)
{
    assert(a.capacity() == b.capacity());
    uset<GrB_Index> intersect(a.capacity());
    uset_intersection(intersect,a,b);
    return intersect;
}

uset<GrB_Index> operator*
(
    const vector<GrB_Index>& a,
    const uset<GrB_Index>&   b
)
{
    assert(a.size() == b.capacity());
    uset<GrB_Index> intersect(a.capacity());
    for (auto it = a.begin(); it != a.end(); ++it)
    {
        if (!b.count(*it)) intersect.insert(*it);
    }
    return intersect;
}

uset<GrB_Index> operator-
(
    const uset<GrB_Index>& a, 
    const uset<GrB_Index>& b
)
{
    assert(a.capacity() == b.capacity());
    uset<GrB_Index> difference(a.capacity());
    uset_difference(difference,a,b);
    return difference;
}
