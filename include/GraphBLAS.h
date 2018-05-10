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

#ifndef GRAPHBLAS_H
#define GRAPHBLAS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

extern void *const GrB_NULL;
extern void *const GrB_ALL;
extern void *const GrB_INVALID_HANDLE;

typedef enum
{
    GrB_SUCCESS,
    GrB_NULL_POINTER,
    GrB_INVALID_VALUE,
    GrB_INVALID_OBJECT,
    GrB_INVALID_INDEX,
    GrB_UNINITIALIZED_OBJECT,
    GrB_DOMAIN_MISMATCH,
    GrB_DIMENSION_MISMATCH,
    GrB_OUT_OF_MEMORY,
    GrB_OUTPUT_NOT_EMPTY,
    GrB_INDEX_OUT_OF_BOUNDS,
    GrB_INSUFFICIENT_SPACE,
    GrB_NO_VALUE,
    GrB_PANIC
} GrB_Info;

typedef enum
{
    GrB_BLOCKING,
    GrB_NONBLOCKING
} GrB_Mode;

typedef enum
{
    GrB_OUTP,
    GrB_MASK,
    GrB_INP0,
    GrB_INP1
} GrB_Desc_Field;

typedef enum
{
    GrB_REPLACE,
    GrB_SCMP,
    GrB_TRAN
} GrB_Desc_Value;

typedef uint64_t GrB_Index;

typedef struct GrB_Type_t       *GrB_Type;
typedef struct GrB_UnaryOp_t    *GrB_UnaryOp;
typedef struct GrB_BinaryOp_t   *GrB_BinaryOp;
typedef struct GrB_Monoid_t     *GrB_Monoid;
typedef struct GrB_Semiring_t   *GrB_Semiring;
typedef struct GrB_Vector_t     *GrB_Vector;
typedef struct GrB_Matrix_t     *GrB_Matrix;
typedef struct GrB_Descriptor_t *GrB_Descriptor;

extern GrB_Type         GrB_BOOL;
extern GrB_Type         GrB_INT8;
extern GrB_Type         GrB_UINT8;
extern GrB_Type         GrB_INT16;
extern GrB_Type         GrB_UINT16;
extern GrB_Type         GrB_INT32;
extern GrB_Type         GrB_UINT32;
extern GrB_Type         GrB_INT64;
extern GrB_Type         GrB_UINT64;
extern GrB_Type         GrB_FP32;
extern GrB_Type         GrB_FP64;

extern GrB_UnaryOp      GrB_LNOT;
extern GrB_BinaryOp     GrB_LAND;
extern GrB_BinaryOp     GrB_LOR;
extern GrB_BinaryOp     GrB_LXOR;

extern GrB_UnaryOp      GrB_IDENTITY_BOOL;
extern GrB_UnaryOp      GrB_AINV_BOOL;
extern GrB_UnaryOp      GrB_MINV_BOOL;
extern GrB_BinaryOp     GrB_EQ_BOOL;
extern GrB_BinaryOp     GrB_NE_BOOL;
extern GrB_BinaryOp     GrB_GT_BOOL;
extern GrB_BinaryOp     GrB_LT_BOOL;
extern GrB_BinaryOp     GrB_GE_BOOL;
extern GrB_BinaryOp     GrB_LE_BOOL;
extern GrB_BinaryOp     GrB_FIRST_BOOL;
extern GrB_BinaryOp     GrB_SECOND_BOOL;
extern GrB_BinaryOp     GrB_MIN_BOOL;
extern GrB_BinaryOp     GrB_MAX_BOOL;
extern GrB_BinaryOp     GrB_PLUS_BOOL;
extern GrB_BinaryOp     GrB_MINUS_BOOL;
extern GrB_BinaryOp     GrB_TIMES_BOOL;
extern GrB_BinaryOp     GrB_DIV_BOOL;

extern GrB_UnaryOp      GrB_IDENTITY_INT8;
extern GrB_UnaryOp      GrB_AINV_INT8;
extern GrB_UnaryOp      GrB_MINV_INT8;
extern GrB_BinaryOp     GrB_EQ_INT8;
extern GrB_BinaryOp     GrB_NE_INT8;
extern GrB_BinaryOp     GrB_GT_INT8;
extern GrB_BinaryOp     GrB_LT_INT8;
extern GrB_BinaryOp     GrB_GE_INT8;
extern GrB_BinaryOp     GrB_LE_INT8;
extern GrB_BinaryOp     GrB_FIRST_INT8;
extern GrB_BinaryOp     GrB_SECOND_INT8;
extern GrB_BinaryOp     GrB_MIN_INT8;
extern GrB_BinaryOp     GrB_MAX_INT8;
extern GrB_BinaryOp     GrB_PLUS_INT8;
extern GrB_BinaryOp     GrB_MINUS_INT8;
extern GrB_BinaryOp     GrB_TIMES_INT8;
extern GrB_BinaryOp     GrB_DIV_INT8;

extern GrB_UnaryOp      GrB_IDENTITY_UINT8;
extern GrB_UnaryOp      GrB_AINV_UINT8;
extern GrB_UnaryOp      GrB_MINV_UINT8;
extern GrB_BinaryOp     GrB_EQ_UINT8;
extern GrB_BinaryOp     GrB_NE_UINT8;
extern GrB_BinaryOp     GrB_GT_UINT8;
extern GrB_BinaryOp     GrB_LT_UINT8;
extern GrB_BinaryOp     GrB_GE_UINT8;
extern GrB_BinaryOp     GrB_LE_UINT8;
extern GrB_BinaryOp     GrB_FIRST_UINT8;
extern GrB_BinaryOp     GrB_SECOND_UINT8;
extern GrB_BinaryOp     GrB_MIN_UINT8;
extern GrB_BinaryOp     GrB_MAX_UINT8;
extern GrB_BinaryOp     GrB_PLUS_UINT8;
extern GrB_BinaryOp     GrB_MINUS_UINT8;
extern GrB_BinaryOp     GrB_TIMES_UINT8;
extern GrB_BinaryOp     GrB_DIV_UINT8;

extern GrB_UnaryOp      GrB_IDENTITY_INT16;
extern GrB_UnaryOp      GrB_AINV_INT16;
extern GrB_UnaryOp      GrB_MINV_INT16;
extern GrB_BinaryOp     GrB_EQ_INT16;
extern GrB_BinaryOp     GrB_NE_INT16;
extern GrB_BinaryOp     GrB_GT_INT16;
extern GrB_BinaryOp     GrB_LT_INT16;
extern GrB_BinaryOp     GrB_GE_INT16;
extern GrB_BinaryOp     GrB_LE_INT16;
extern GrB_BinaryOp     GrB_FIRST_INT16;
extern GrB_BinaryOp     GrB_SECOND_INT16;
extern GrB_BinaryOp     GrB_MIN_INT16;
extern GrB_BinaryOp     GrB_MAX_INT16;
extern GrB_BinaryOp     GrB_PLUS_INT16;
extern GrB_BinaryOp     GrB_MINUS_INT16;
extern GrB_BinaryOp     GrB_TIMES_INT16;
extern GrB_BinaryOp     GrB_DIV_INT16;

extern GrB_UnaryOp      GrB_IDENTITY_UINT16;
extern GrB_UnaryOp      GrB_AINV_UINT16;
extern GrB_UnaryOp      GrB_MINV_UINT16;
extern GrB_BinaryOp     GrB_EQ_UINT16;
extern GrB_BinaryOp     GrB_NE_UINT16;
extern GrB_BinaryOp     GrB_GT_UINT16;
extern GrB_BinaryOp     GrB_LT_UINT16;
extern GrB_BinaryOp     GrB_GE_UINT16;
extern GrB_BinaryOp     GrB_LE_UINT16;
extern GrB_BinaryOp     GrB_FIRST_UINT16;
extern GrB_BinaryOp     GrB_SECOND_UINT16;
extern GrB_BinaryOp     GrB_MIN_UINT16;
extern GrB_BinaryOp     GrB_MAX_UINT16;
extern GrB_BinaryOp     GrB_PLUS_UINT16;
extern GrB_BinaryOp     GrB_MINUS_UINT16;
extern GrB_BinaryOp     GrB_TIMES_UINT16;
extern GrB_BinaryOp     GrB_DIV_UINT16;

extern GrB_UnaryOp      GrB_IDENTITY_INT32;
extern GrB_UnaryOp      GrB_AINV_INT32;
extern GrB_UnaryOp      GrB_MINV_INT32;
extern GrB_BinaryOp     GrB_EQ_INT32;
extern GrB_BinaryOp     GrB_NE_INT32;
extern GrB_BinaryOp     GrB_GT_INT32;
extern GrB_BinaryOp     GrB_LT_INT32;
extern GrB_BinaryOp     GrB_GE_INT32;
extern GrB_BinaryOp     GrB_LE_INT32;
extern GrB_BinaryOp     GrB_FIRST_INT32;
extern GrB_BinaryOp     GrB_SECOND_INT32;
extern GrB_BinaryOp     GrB_MIN_INT32;
extern GrB_BinaryOp     GrB_MAX_INT32;
extern GrB_BinaryOp     GrB_PLUS_INT32;
extern GrB_BinaryOp     GrB_MINUS_INT32;
extern GrB_BinaryOp     GrB_TIMES_INT32;
extern GrB_BinaryOp     GrB_DIV_INT32;

extern GrB_UnaryOp      GrB_IDENTITY_UINT32;
extern GrB_UnaryOp      GrB_AINV_UINT32;
extern GrB_UnaryOp      GrB_MINV_UINT32;
extern GrB_BinaryOp     GrB_EQ_UINT32;
extern GrB_BinaryOp     GrB_NE_UINT32;
extern GrB_BinaryOp     GrB_GT_UINT32;
extern GrB_BinaryOp     GrB_LT_UINT32;
extern GrB_BinaryOp     GrB_GE_UINT32;
extern GrB_BinaryOp     GrB_LE_UINT32;
extern GrB_BinaryOp     GrB_FIRST_UINT32;
extern GrB_BinaryOp     GrB_SECOND_UINT32;
extern GrB_BinaryOp     GrB_MIN_UINT32;
extern GrB_BinaryOp     GrB_MAX_UINT32;
extern GrB_BinaryOp     GrB_PLUS_UINT32;
extern GrB_BinaryOp     GrB_MINUS_UINT32;
extern GrB_BinaryOp     GrB_TIMES_UINT32;
extern GrB_BinaryOp     GrB_DIV_UINT32;

extern GrB_UnaryOp      GrB_IDENTITY_INT64;
extern GrB_UnaryOp      GrB_AINV_INT64;
extern GrB_UnaryOp      GrB_MINV_INT64;
extern GrB_BinaryOp     GrB_EQ_INT64;
extern GrB_BinaryOp     GrB_NE_INT64;
extern GrB_BinaryOp     GrB_GT_INT64;
extern GrB_BinaryOp     GrB_LT_INT64;
extern GrB_BinaryOp     GrB_GE_INT64;
extern GrB_BinaryOp     GrB_LE_INT64;
extern GrB_BinaryOp     GrB_FIRST_INT64;
extern GrB_BinaryOp     GrB_SECOND_INT64;
extern GrB_BinaryOp     GrB_MIN_INT64;
extern GrB_BinaryOp     GrB_MAX_INT64;
extern GrB_BinaryOp     GrB_PLUS_INT64;
extern GrB_BinaryOp     GrB_MINUS_INT64;
extern GrB_BinaryOp     GrB_TIMES_INT64;
extern GrB_BinaryOp     GrB_DIV_INT64;

extern GrB_UnaryOp      GrB_IDENTITY_UINT64;
extern GrB_UnaryOp      GrB_AINV_UINT64;
extern GrB_UnaryOp      GrB_MINV_UINT64;
extern GrB_BinaryOp     GrB_EQ_UINT64;
extern GrB_BinaryOp     GrB_NE_UINT64;
extern GrB_BinaryOp     GrB_GT_UINT64;
extern GrB_BinaryOp     GrB_LT_UINT64;
extern GrB_BinaryOp     GrB_GE_UINT64;
extern GrB_BinaryOp     GrB_LE_UINT64;
extern GrB_BinaryOp     GrB_FIRST_UINT64;
extern GrB_BinaryOp     GrB_SECOND_UINT64;
extern GrB_BinaryOp     GrB_MIN_UINT64;
extern GrB_BinaryOp     GrB_MAX_UINT64;
extern GrB_BinaryOp     GrB_PLUS_UINT64;
extern GrB_BinaryOp     GrB_MINUS_UINT64;
extern GrB_BinaryOp     GrB_TIMES_UINT64;
extern GrB_BinaryOp     GrB_DIV_UINT64;

extern GrB_UnaryOp      GrB_IDENTITY_FP32;
extern GrB_UnaryOp      GrB_AINV_FP32;
extern GrB_UnaryOp      GrB_MINV_FP32;
extern GrB_BinaryOp     GrB_EQ_FP32;
extern GrB_BinaryOp     GrB_NE_FP32;
extern GrB_BinaryOp     GrB_GT_FP32;
extern GrB_BinaryOp     GrB_LT_FP32;
extern GrB_BinaryOp     GrB_GE_FP32;
extern GrB_BinaryOp     GrB_LE_FP32;
extern GrB_BinaryOp     GrB_FIRST_FP32;
extern GrB_BinaryOp     GrB_SECOND_FP32;
extern GrB_BinaryOp     GrB_MIN_FP32;
extern GrB_BinaryOp     GrB_MAX_FP32;
extern GrB_BinaryOp     GrB_PLUS_FP32;
extern GrB_BinaryOp     GrB_MINUS_FP32;
extern GrB_BinaryOp     GrB_TIMES_FP32;
extern GrB_BinaryOp     GrB_DIV_FP32;

extern GrB_UnaryOp      GrB_IDENTITY_FP64;
extern GrB_UnaryOp      GrB_AINV_FP64;
extern GrB_UnaryOp      GrB_MINV_FP64;
extern GrB_BinaryOp     GrB_EQ_FP64;
extern GrB_BinaryOp     GrB_NE_FP64;
extern GrB_BinaryOp     GrB_GT_FP64;
extern GrB_BinaryOp     GrB_LT_FP64;
extern GrB_BinaryOp     GrB_GE_FP64;
extern GrB_BinaryOp     GrB_LE_FP64;
extern GrB_BinaryOp     GrB_FIRST_FP64;
extern GrB_BinaryOp     GrB_SECOND_FP64;
extern GrB_BinaryOp     GrB_MIN_FP64;
extern GrB_BinaryOp     GrB_MAX_FP64;
extern GrB_BinaryOp     GrB_PLUS_FP64;
extern GrB_BinaryOp     GrB_MINUS_FP64;
extern GrB_BinaryOp     GrB_TIMES_FP64;
extern GrB_BinaryOp     GrB_DIV_FP64;

// Section 4.1.1 init

GrB_Info GrB_init(GrB_Mode);

// Section 4.1.2 finalize

GrB_Info GrB_finalize();

// Section 4.2.1 algebra methods

GrB_Info GrB_Type_new    (GrB_Type*   , size_t);
GrB_Info GrB_UnaryOp_new (GrB_UnaryOp*,  void (*)(void*, const void*             ), GrB_Type, GrB_Type);
GrB_Info GrB_BinaryOp_new(GrB_BinaryOp*, void (*)(void*, const void*, const void*), GrB_Type, GrB_Type, GrB_Type);

GrB_Info GrB_Monoid_new_BOOL  (GrB_Monoid*, GrB_BinaryOp, bool);
GrB_Info GrB_Monoid_new_INT8  (GrB_Monoid*, GrB_BinaryOp, int8_t);
GrB_Info GrB_Monoid_new_UINT8 (GrB_Monoid*, GrB_BinaryOp, uint8_t);
GrB_Info GrB_Monoid_new_INT16 (GrB_Monoid*, GrB_BinaryOp, int16_t);
GrB_Info GrB_Monoid_new_UINT16(GrB_Monoid*, GrB_BinaryOp, uint16_t);
GrB_Info GrB_Monoid_new_INT32 (GrB_Monoid*, GrB_BinaryOp, int32_t);
GrB_Info GrB_Monoid_new_UINT32(GrB_Monoid*, GrB_BinaryOp, uint32_t);
GrB_Info GrB_Monoid_new_INT64 (GrB_Monoid*, GrB_BinaryOp, int64_t);
GrB_Info GrB_Monoid_new_UINT64(GrB_Monoid*, GrB_BinaryOp, uint64_t);
GrB_Info GrB_Monoid_new_FP32  (GrB_Monoid*, GrB_BinaryOp, float);
GrB_Info GrB_Monoid_new_FP64  (GrB_Monoid*, GrB_BinaryOp, double);
GrB_Info GrB_Monoid_new_UDT   (GrB_Monoid*, GrB_BinaryOp, const void*);

GrB_Info GrB_Semiring_new(GrB_Semiring*,GrB_Monoid,GrB_BinaryOp);

// Section 4.2.2 vector methods

GrB_Info GrB_Vector_new  (GrB_Vector*, GrB_Type, GrB_Index);
GrB_Info GrB_Vector_dup  (GrB_Vector*, const GrB_Vector);
GrB_Info GrB_Vector_clear(GrB_Vector);
GrB_Info GrB_Vector_size (GrB_Index*, const GrB_Vector);
GrB_Info GrB_Vector_nvals(GrB_Index*, const GrB_Vector);

GrB_Info GrB_Vector_build_BOOL   (GrB_Vector, const GrB_Index*, const bool*     , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Vector_build_INT8   (GrB_Vector, const GrB_Index*, const int8_t*   , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Vector_build_UINT8  (GrB_Vector, const GrB_Index*, const uint8_t*  , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Vector_build_INT16  (GrB_Vector, const GrB_Index*, const int16_t*  , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Vector_build_UINT16 (GrB_Vector, const GrB_Index*, const uint16_t* , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Vector_build_INT32  (GrB_Vector, const GrB_Index*, const int32_t*  , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Vector_build_UINT32 (GrB_Vector, const GrB_Index*, const uint32_t* , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Vector_build_INT64  (GrB_Vector, const GrB_Index*, const int64_t*  , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Vector_build_UINT64 (GrB_Vector, const GrB_Index*, const uint64_t* , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Vector_build_FP32   (GrB_Vector, const GrB_Index*, const float*    , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Vector_build_FP64   (GrB_Vector, const GrB_Index*, const double*   , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Vector_build_UDT    (GrB_Vector, const GrB_Index*, const void*     , GrB_Index, const GrB_BinaryOp);

GrB_Info GrB_Vector_setElement_BOOL   (GrB_Vector, bool       , GrB_Index);
GrB_Info GrB_Vector_setElement_INT8   (GrB_Vector, int8_t     , GrB_Index);
GrB_Info GrB_Vector_setElement_UINT8  (GrB_Vector, uint8_t    , GrB_Index);
GrB_Info GrB_Vector_setElement_INT16  (GrB_Vector, int16_t    , GrB_Index);
GrB_Info GrB_Vector_setElement_UINT16 (GrB_Vector, uint16_t   , GrB_Index);
GrB_Info GrB_Vector_setElement_INT32  (GrB_Vector, int32_t    , GrB_Index);
GrB_Info GrB_Vector_setElement_UINT32 (GrB_Vector, uint32_t   , GrB_Index);
GrB_Info GrB_Vector_setElement_INT64  (GrB_Vector, int64_t    , GrB_Index);
GrB_Info GrB_Vector_setElement_UINT64 (GrB_Vector, uint64_t   , GrB_Index);
GrB_Info GrB_Vector_setElement_FP32   (GrB_Vector, float      , GrB_Index);
GrB_Info GrB_Vector_setElement_FP64   (GrB_Vector, double     , GrB_Index);
GrB_Info GrB_Vector_setElement_UDT    (GrB_Vector, const void*, GrB_Index);

GrB_Info GrB_Vector_extractElement_BOOL  (bool*    , const GrB_Vector, GrB_Index);
GrB_Info GrB_Vector_extractElement_INT8  (int8_t*  , const GrB_Vector, GrB_Index);
GrB_Info GrB_Vector_extractElement_UINT8 (uint8_t* , const GrB_Vector, GrB_Index);
GrB_Info GrB_Vector_extractElement_INT16 (int16_t* , const GrB_Vector, GrB_Index);
GrB_Info GrB_Vector_extractElement_UINT16(uint16_t*, const GrB_Vector, GrB_Index);
GrB_Info GrB_Vector_extractElement_INT32 (int32_t* , const GrB_Vector, GrB_Index);
GrB_Info GrB_Vector_extractElement_UINT32(uint32_t*, const GrB_Vector, GrB_Index);
GrB_Info GrB_Vector_extractElement_INT64 (int64_t* , const GrB_Vector, GrB_Index);
GrB_Info GrB_Vector_extractElement_UINT64(uint64_t*, const GrB_Vector, GrB_Index);
GrB_Info GrB_Vector_extractElement_FP32  (float*   , const GrB_Vector, GrB_Index);
GrB_Info GrB_Vector_extractElement_FP64  (double*  , const GrB_Vector, GrB_Index);
GrB_Info GrB_Vector_extractElement_UDT   (void*    , const GrB_Vector, GrB_Index);

GrB_Info GrB_Vector_extractTuples_BOOL   (GrB_Index*, bool*    , GrB_Index*, const GrB_Vector);
GrB_Info GrB_Vector_extractTuples_INT8   (GrB_Index*, int8_t*  , GrB_Index*, const GrB_Vector);
GrB_Info GrB_Vector_extractTuples_UINT8  (GrB_Index*, uint8_t* , GrB_Index*, const GrB_Vector);
GrB_Info GrB_Vector_extractTuples_INT16  (GrB_Index*, int16_t* , GrB_Index*, const GrB_Vector);
GrB_Info GrB_Vector_extractTuples_UINT16 (GrB_Index*, uint16_t*, GrB_Index*, const GrB_Vector);
GrB_Info GrB_Vector_extractTuples_INT32  (GrB_Index*, int32_t* , GrB_Index*, const GrB_Vector);
GrB_Info GrB_Vector_extractTuples_UINT32 (GrB_Index*, uint32_t*, GrB_Index*, const GrB_Vector);
GrB_Info GrB_Vector_extractTuples_INT64  (GrB_Index*, int64_t* , GrB_Index*, const GrB_Vector);
GrB_Info GrB_Vector_extractTuples_UINT64 (GrB_Index*, uint64_t*, GrB_Index*, const GrB_Vector);
GrB_Info GrB_Vector_extractTuples_FP32   (GrB_Index*, float*   , GrB_Index*, const GrB_Vector);
GrB_Info GrB_Vector_extractTuples_FP64   (GrB_Index*, double*  , GrB_Index*, const GrB_Vector);
GrB_Info GrB_Vector_extractTuples_UDT    (GrB_Index*, void*    , GrB_Index*, const GrB_Vector);

// Section 4.2.3 matrix methods

GrB_Info GrB_Matrix_new  (GrB_Matrix*, GrB_Type, GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_dup  (GrB_Matrix*, const GrB_Matrix);
GrB_Info GrB_Matrix_clear(GrB_Matrix);
GrB_Info GrB_Matrix_nrows(GrB_Index*, const GrB_Matrix);
GrB_Info GrB_Matrix_ncols(GrB_Index*, const GrB_Matrix);
GrB_Info GrB_Matrix_nvals(GrB_Index*, const GrB_Matrix);

GrB_Info GrB_Matrix_build_BOOL   (GrB_Matrix, const GrB_Index*, const GrB_Index*, const bool*    , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Matrix_build_INT8   (GrB_Matrix, const GrB_Index*, const GrB_Index*, const int8_t*  , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Matrix_build_UINT8  (GrB_Matrix, const GrB_Index*, const GrB_Index*, const uint8_t* , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Matrix_build_INT16  (GrB_Matrix, const GrB_Index*, const GrB_Index*, const int16_t* , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Matrix_build_UINT16 (GrB_Matrix, const GrB_Index*, const GrB_Index*, const uint16_t*, GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Matrix_build_INT32  (GrB_Matrix, const GrB_Index*, const GrB_Index*, const int32_t* , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Matrix_build_UINT32 (GrB_Matrix, const GrB_Index*, const GrB_Index*, const uint32_t*, GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Matrix_build_INT64  (GrB_Matrix, const GrB_Index*, const GrB_Index*, const int64_t* , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Matrix_build_UINT64 (GrB_Matrix, const GrB_Index*, const GrB_Index*, const uint64_t*, GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Matrix_build_FP32   (GrB_Matrix, const GrB_Index*, const GrB_Index*, const float*   , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Matrix_build_FP64   (GrB_Matrix, const GrB_Index*, const GrB_Index*, const double*  , GrB_Index, const GrB_BinaryOp);
GrB_Info GrB_Matrix_build_UDT    (GrB_Matrix, const GrB_Index*, const GrB_Index*, const void*    , GrB_Index, const GrB_BinaryOp);

GrB_Info GrB_Matrix_setElement_BOOL   (GrB_Matrix, bool        , GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_setElement_INT8   (GrB_Matrix, int8_t      , GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_setElement_UINT8  (GrB_Matrix, uint8_t     , GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_setElement_INT16  (GrB_Matrix, int16_t     , GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_setElement_UINT16 (GrB_Matrix, uint16_t    , GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_setElement_INT32  (GrB_Matrix, int32_t     , GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_setElement_UINT32 (GrB_Matrix, uint32_t    , GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_setElement_INT64  (GrB_Matrix, int64_t     , GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_setElement_UINT64 (GrB_Matrix, uint64_t    , GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_setElement_FP32   (GrB_Matrix, float       , GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_setElement_FP64   (GrB_Matrix, double      , GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_setElement_UDT    (GrB_Matrix, const void* , GrB_Index, GrB_Index);

GrB_Info GrB_Matrix_extractElement_BOOL  (bool*    , const GrB_Matrix, GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_extractElement_INT8  (int8_t*  , const GrB_Matrix, GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_extractElement_UINT8 (uint8_t* , const GrB_Matrix, GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_extractElement_INT16 (int16_t* , const GrB_Matrix, GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_extractElement_UINT16(uint16_t*, const GrB_Matrix, GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_extractElement_INT32 (int32_t* , const GrB_Matrix, GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_extractElement_UINT32(uint32_t*, const GrB_Matrix, GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_extractElement_INT64 (int64_t* , const GrB_Matrix, GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_extractElement_UINT64(uint64_t*, const GrB_Matrix, GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_extractElement_FP32  (float*   , const GrB_Matrix, GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_extractElement_FP64  (double*  , const GrB_Matrix, GrB_Index, GrB_Index);
GrB_Info GrB_Matrix_extractElement_UDT   (void*    , const GrB_Matrix, GrB_Index, GrB_Index);

GrB_Info GrB_Matrix_extractTuples_BOOL  (GrB_Index*, GrB_Index*, bool*    , GrB_Index*, const GrB_Matrix);
GrB_Info GrB_Matrix_extractTuples_INT8  (GrB_Index*, GrB_Index*, int8_t*  , GrB_Index*, const GrB_Matrix);
GrB_Info GrB_Matrix_extractTuples_UINT8 (GrB_Index*, GrB_Index*, uint8_t* , GrB_Index*, const GrB_Matrix);
GrB_Info GrB_Matrix_extractTuples_INT16 (GrB_Index*, GrB_Index*, int16_t* , GrB_Index*, const GrB_Matrix);
GrB_Info GrB_Matrix_extractTuples_UINT16(GrB_Index*, GrB_Index*, uint16_t*, GrB_Index*, const GrB_Matrix);
GrB_Info GrB_Matrix_extractTuples_INT32 (GrB_Index*, GrB_Index*, int32_t* , GrB_Index*, const GrB_Matrix);
GrB_Info GrB_Matrix_extractTuples_UINT32(GrB_Index*, GrB_Index*, uint32_t*, GrB_Index*, const GrB_Matrix);
GrB_Info GrB_Matrix_extractTuples_INT64 (GrB_Index*, GrB_Index*, int64_t* , GrB_Index*, const GrB_Matrix);
GrB_Info GrB_Matrix_extractTuples_UINT64(GrB_Index*, GrB_Index*, uint64_t*, GrB_Index*, const GrB_Matrix);
GrB_Info GrB_Matrix_extractTuples_FP32  (GrB_Index*, GrB_Index*, float*   , GrB_Index*, const GrB_Matrix);
GrB_Info GrB_Matrix_extractTuples_FP64  (GrB_Index*, GrB_Index*, double*  , GrB_Index*, const GrB_Matrix);
GrB_Info GrB_Matrix_extractTuples_UDT   (GrB_Index*, GrB_Index*, void*    , GrB_Index*, const GrB_Matrix);

// Section 4.2.4 descriptor methods

GrB_Info GrB_Descriptor_new(GrB_Descriptor*);
GrB_Info GrB_Descriptor_set(GrB_Descriptor, GrB_Desc_Field, GrB_Desc_Value);

// Section 4.2.5 free

GrB_Info GrB_Type_free(GrB_Type*);
GrB_Info GrB_UnaryOp_free(GrB_UnaryOp*);
GrB_Info GrB_BinaryOp_free(GrB_BinaryOp*);
GrB_Info GrB_Monoid_free(GrB_Monoid*);
GrB_Info GrB_Semiring_free(GrB_Semiring*);
GrB_Info GrB_Vector_free(GrB_Vector*);
GrB_Info GrB_Matrix_free(GrB_Matrix*);
GrB_Info GrB_Descriptor_free(GrB_Descriptor*);

// Section 4.3.1 mxm

GrB_Info GrB_mxm(GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, const GrB_Semiring, const GrB_Matrix, const GrB_Matrix, const GrB_Descriptor);

// Section 4.3.2 vxm

GrB_Info GrB_vxm(GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const GrB_Semiring, const GrB_Vector, const GrB_Matrix, const GrB_Descriptor);

// Section 4.3.3 mxv

GrB_Info GrB_mxv(GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const GrB_Semiring, const GrB_Matrix, const GrB_Vector, const GrB_Descriptor);

// Section 4.3.4 eWiseMult

GrB_Info GrB_Vector_eWiseMult_Semiring(GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const GrB_Semiring, const GrB_Vector, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_eWiseMult_Monoid  (GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const GrB_Monoid  , const GrB_Vector, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_eWiseMult_BinaryOp(GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const GrB_BinaryOp, const GrB_Vector, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Matrix_eWiseMult_Semiring(GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, const GrB_Semiring, const GrB_Matrix, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_eWiseMult_Monoid  (GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, const GrB_Monoid  , const GrB_Matrix, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_eWiseMult_BinaryOp(GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, const GrB_BinaryOp, const GrB_Matrix, const GrB_Matrix, const GrB_Descriptor);

// Section 4.3.5 eWiseAdd

GrB_Info GrB_Vector_eWiseAdd_Semiring(GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const GrB_Semiring, const GrB_Vector, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_eWiseAdd_Monoid  (GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const GrB_Monoid  , const GrB_Vector, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_eWiseAdd_BinaryOp(GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const GrB_BinaryOp, const GrB_Vector, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Matrix_eWiseAdd_Semiring(GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, const GrB_Semiring, const GrB_Matrix, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_eWiseAdd_Monoid  (GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, const GrB_Monoid  , const GrB_Matrix, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_eWiseAdd_BinaryOp(GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, const GrB_BinaryOp, const GrB_Matrix, const GrB_Matrix, const GrB_Descriptor);

// Section 4.3.6 extract

GrB_Info GrB_Vector_extract(GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const GrB_Vector, const GrB_Index*, GrB_Index                             , const GrB_Descriptor);
GrB_Info GrB_Matrix_extract(GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, const GrB_Matrix, const GrB_Index*, GrB_Index, const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Col_extract   (GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const GrB_Matrix, const GrB_Index*, GrB_Index, const GrB_Index            , const GrB_Descriptor);

#define GrB_GET_7_OR_8_OR_9(_1,_2,_3,_4,_5,_6,_7,_8,_9,   NAME,...) NAME
#define GrB_extract(...) GrB_GET_7_OR_8_OR_9(__VA_ARGS__,GrB_Matrix_extract,GrB_Col_extract,GrB_Vector_extract)(__VA_ARGS__)

// Section 4.3.7 assign

GrB_Info GrB_Vector_assign(GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const GrB_Vector, const GrB_Index *, GrB_Index                                        , const GrB_Descriptor);
GrB_Info GrB_Matrix_assign(GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, const GrB_Matrix, const GrB_Index *, GrB_Index          , const GrB_Index *, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Col_assign   (GrB_Matrix, const GrB_Vector, const GrB_BinaryOp, const GrB_Vector, const GrB_Index *, GrB_Index          , GrB_Index                   , const GrB_Descriptor);
GrB_Info GrB_Row_assign   (GrB_Matrix, const GrB_Vector, const GrB_BinaryOp, const GrB_Vector, GrB_Index        , const GrB_Index *  , GrB_Index                   , const GrB_Descriptor);

GrB_Info GrB_Vector_assign_BOOL  (GrB_Vector, const GrB_Vector, const GrB_BinaryOp, bool       , const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Vector_assign_INT8  (GrB_Vector, const GrB_Vector, const GrB_BinaryOp, int8_t     , const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Vector_assign_UINT8 (GrB_Vector, const GrB_Vector, const GrB_BinaryOp, uint8_t    , const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Vector_assign_INT16 (GrB_Vector, const GrB_Vector, const GrB_BinaryOp, int16_t    , const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Vector_assign_UINT16(GrB_Vector, const GrB_Vector, const GrB_BinaryOp, uint16_t   , const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Vector_assign_INT32 (GrB_Vector, const GrB_Vector, const GrB_BinaryOp, int32_t    , const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Vector_assign_UINT32(GrB_Vector, const GrB_Vector, const GrB_BinaryOp, uint32_t   , const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Vector_assign_INT64 (GrB_Vector, const GrB_Vector, const GrB_BinaryOp, int64_t    , const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Vector_assign_UINT64(GrB_Vector, const GrB_Vector, const GrB_BinaryOp, uint64_t   , const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Vector_assign_FP32  (GrB_Vector, const GrB_Vector, const GrB_BinaryOp, float      , const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Vector_assign_FP64  (GrB_Vector, const GrB_Vector, const GrB_BinaryOp, double     , const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Vector_assign_UDT   (GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const void*, const GrB_Index*, GrB_Index, const GrB_Descriptor);

GrB_Info GrB_Matrix_assign_BOOL  (GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, bool       , const GrB_Index*, GrB_Index, const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Matrix_assign_INT8  (GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, int8_t     , const GrB_Index*, GrB_Index, const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Matrix_assign_INT16 (GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, int16_t    , const GrB_Index*, GrB_Index, const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Matrix_assign_INT32 (GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, int32_t    , const GrB_Index*, GrB_Index, const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Matrix_assign_INT64 (GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, int64_t    , const GrB_Index*, GrB_Index, const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Matrix_assign_UINT8 (GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, uint8_t    , const GrB_Index*, GrB_Index, const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Matrix_assign_UINT16(GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, uint16_t   , const GrB_Index*, GrB_Index, const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Matrix_assign_UINT32(GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, uint32_t   , const GrB_Index*, GrB_Index, const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Matrix_assign_UINT64(GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, uint64_t   , const GrB_Index*, GrB_Index, const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Matrix_assign_FP32  (GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, float      , const GrB_Index*, GrB_Index, const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Matrix_assign_FP64  (GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, double     , const GrB_Index*, GrB_Index, const GrB_Index*, GrB_Index, const GrB_Descriptor);
GrB_Info GrB_Matrix_assign_UDT   (GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, const void*, const GrB_Index*, GrB_Index, const GrB_Index*, GrB_Index, const GrB_Descriptor);

// Section 4.3.8 apply

GrB_Info GrB_Vector_apply(GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const GrB_UnaryOp, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Matrix_apply(GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, const GrB_UnaryOp, const GrB_Matrix, const GrB_Descriptor);

// Section 4.3.9 reduce

GrB_Info GrB_Matrix_reduce_Monoid  (GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const GrB_Monoid  , const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_reduce_BinaryOp(GrB_Vector, const GrB_Vector, const GrB_BinaryOp, const GrB_BinaryOp, const GrB_Matrix, const GrB_Descriptor);

GrB_Info GrB_Vector_reduce_BOOL  (bool*    , const GrB_BinaryOp, const GrB_Monoid, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_reduce_INT8  (int8_t*  , const GrB_BinaryOp, const GrB_Monoid, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_reduce_UINT8 (uint8_t* , const GrB_BinaryOp, const GrB_Monoid, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_reduce_INT16 (int16_t* , const GrB_BinaryOp, const GrB_Monoid, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_reduce_UINT16(uint16_t*, const GrB_BinaryOp, const GrB_Monoid, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_reduce_INT32 (int32_t* , const GrB_BinaryOp, const GrB_Monoid, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_reduce_UINT32(uint32_t*, const GrB_BinaryOp, const GrB_Monoid, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_reduce_INT64 (int64_t* , const GrB_BinaryOp, const GrB_Monoid, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_reduce_UINT64(uint64_t*, const GrB_BinaryOp, const GrB_Monoid, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_reduce_FP32  (float*   , const GrB_BinaryOp, const GrB_Monoid, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_reduce_FP64  (double*  , const GrB_BinaryOp, const GrB_Monoid, const GrB_Vector, const GrB_Descriptor);
GrB_Info GrB_Vector_reduce_UDT   (void*    , const GrB_BinaryOp, const GrB_Monoid, const GrB_Vector, const GrB_Descriptor);

GrB_Info GrB_Matrix_reduce_BOOL  (bool*    , const GrB_BinaryOp, const GrB_Monoid, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_reduce_INT8  (int8_t*  , const GrB_BinaryOp, const GrB_Monoid, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_reduce_UINT8 (uint8_t* , const GrB_BinaryOp, const GrB_Monoid, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_reduce_INT16 (int16_t* , const GrB_BinaryOp, const GrB_Monoid, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_reduce_UINT16(uint16_t*, const GrB_BinaryOp, const GrB_Monoid, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_reduce_INT32 (int32_t* , const GrB_BinaryOp, const GrB_Monoid, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_reduce_UINT32(uint32_t*, const GrB_BinaryOp, const GrB_Monoid, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_reduce_INT64 (int64_t* , const GrB_BinaryOp, const GrB_Monoid, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_reduce_UINT64(uint64_t*, const GrB_BinaryOp, const GrB_Monoid, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_reduce_FP32  (float*   , const GrB_BinaryOp, const GrB_Monoid, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_reduce_FP64  (double*  , const GrB_BinaryOp, const GrB_Monoid, const GrB_Matrix, const GrB_Descriptor);
GrB_Info GrB_Matrix_reduce_UDT   (void*    , const GrB_BinaryOp, const GrB_Monoid, const GrB_Matrix, const GrB_Descriptor);

// Section 4.3.10 transpose

GrB_Info GrB_transpose(GrB_Matrix, const GrB_Matrix, const GrB_BinaryOp, const GrB_Matrix, const GrB_Descriptor);

// Section 4.4.1 wait

GrB_Info GrB_wait();

// Section 4.4.2 error

const char *GrB_error();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

extern "C++"
{

#define GrB_Instantiate_Polymorphic_Value(NAME) \
NAME(bool       , BOOL  )                       \
NAME(int8_t     , INT8  )                       \
NAME(int16_t    , INT16 )                       \
NAME(int32_t    , INT32 )                       \
NAME(int64_t    , INT64 )                       \
NAME(uint8_t    , UINT8 )                       \
NAME(uint16_t   , UINT16)                       \
NAME(uint32_t   , UINT32)                       \
NAME(uint64_t   , UINT64)                       \
NAME(float      , FP32  )                       \
NAME(double     , FP64  )                       \
NAME(const void*, UDT   )

#define GrB_Instantiate_Polymorphic_Pointer(NAME)       \
NAME(bool       , BOOL  )                               \
NAME(int8_t     , INT8  )                               \
NAME(int16_t    , INT16 )                               \
NAME(int32_t    , INT32 )                               \
NAME(int64_t    , INT64 )                               \
NAME(uint8_t    , UINT8 )                               \
NAME(uint16_t   , UINT16)                               \
NAME(uint32_t   , UINT32)                               \
NAME(uint64_t   , UINT64)                               \
NAME(float      , FP32  )                               \
NAME(double     , FP64  )                               \
NAME(void       , UDT   )

#define GrB_Monoid_new(type, TYPE)                                      \
static inline                                                           \
GrB_Info GrB_Monoid_new(GrB_Monoid* m, GrB_BinaryOp op, type id)        \
{                                                                       \
        return GrB_Monoid_new_ ## TYPE (m,op,id);                       \
}

GrB_Instantiate_Polymorphic_Value(GrB_Monoid_new)

#undef GrB_Monoid_new

#define GrB_Vector_build(type, TYPE)                                                                            \
static inline                                                                                                   \
GrB_Info GrB_Vector_build(GrB_Vector w, GrB_Index *indices, const type *values, GrB_Index n, GrB_BinaryOp dup)  \
{                                                                                                               \
        return GrB_Vector_build_ ## TYPE (w,indices,values,n,dup);                                              \
}

GrB_Instantiate_Polymorphic_Pointer(GrB_Vector_build)

#undef GrB_Vector_build

#define GrB_Vector_setElement(type, TYPE)                               \
static inline                                                           \
GrB_Info GrB_Vector_setElement(GrB_Vector w, type val, GrB_Index index) \
{                                                                       \
        return GrB_Vector_setElement_ ## TYPE (w, val, index);          \
}

GrB_Instantiate_Polymorphic_Value(GrB_Vector_setElement)

#undef GrB_Vector_setElement

#define GrB_Vector_extractElement(type, TYPE)                                           \
static inline                                                                           \
GrB_Info GrB_Vector_extractElement(type *val, const GrB_Vector u, GrB_Index index)      \
{                                                                                       \
        return GrB_Vector_extractElement_ ## TYPE (val, u, index);                      \
}

GrB_Instantiate_Polymorphic_Pointer(GrB_Vector_extractElement)

#undef GrB_Vector_extractElement

#define GrB_Vector_extractTuples(type, TYPE)                                                            \
static inline                                                                                           \
GrB_Info GrB_Vector_extractTuples(GrB_Index *indices, type *values, GrB_Index *n, const GrB_Vector v)   \
{                                                                                                       \
        return GrB_Vector_extractTuples_ ## TYPE (indices, values, n, v);                               \
}

GrB_Instantiate_Polymorphic_Pointer(GrB_Vector_extractTuples)

#undef GrB_Vector_extractTuples

#define GrB_Matrix_build(type, TYPE)                                                                            \
static inline                                                                                                   \
GrB_Info GrB_Matrix_build(GrB_Matrix C, GrB_Index *row_indices, GrB_Index *col_indices,                         \
                          const type *values, GrB_Index n, GrB_BinaryOp dup)                                    \
{                                                                                                               \
        return GrB_Matrix_build_ ## TYPE (C,row_indices,col_indices, values,n,dup);                             \
}

GrB_Instantiate_Polymorphic_Pointer(GrB_Matrix_build)

#undef GrB_Matrix_build

#define GrB_Matrix_setElement(type, TYPE)                                                               \
static inline                                                                                           \
GrB_Info GrB_Matrix_setElement(GrB_Matrix C, type val, GrB_Index row_index, GrB_Index col_index)        \
{                                                                                                       \
        return GrB_Matrix_setElement_ ## TYPE (C, val, row_index, col_index);                           \
}

GrB_Instantiate_Polymorphic_Value(GrB_Matrix_setElement)

#undef GrB_Matrix_setElement

#define GrB_Matrix_extractElement(type, TYPE)                                                                   \
static inline                                                                                                   \
GrB_Info GrB_Matrix_extractElement(type *val, const GrB_Matrix A, GrB_Index row_index, GrB_Index col_index)     \
{                                                                                                               \
        return GrB_Matrix_extractElement_ ## TYPE (val, A, row_index, col_index);                               \
}

GrB_Instantiate_Polymorphic_Pointer(GrB_Matrix_extractElement)

#undef GrB_Matrix_extractElement

#define GrB_Matrix_extractTuples(type, TYPE)                                                            \
static inline                                                                                           \
GrB_Info GrB_Matrix_extractTuples(GrB_Index *row_indices, GrB_Index *col_indices, type *values,         \
                                  GrB_Index *n, const GrB_Matrix A)                                     \
{                                                                                                       \
        return GrB_Matrix_extractTuples_ ## TYPE (row_indices, col_indices, values, n, A);              \
}

GrB_Instantiate_Polymorphic_Pointer(GrB_Matrix_extractTuples)

#undef GrB_Matrix_extractTuples

static inline GrB_Info GrB_free(GrB_Type       *x) { return GrB_Type_free(x);       }
static inline GrB_Info GrB_free(GrB_UnaryOp    *x) { return GrB_UnaryOp_free(x);    }
static inline GrB_Info GrB_free(GrB_BinaryOp   *x) { return GrB_BinaryOp_free(x);   }
static inline GrB_Info GrB_free(GrB_Monoid     *x) { return GrB_Monoid_free(x);     }
static inline GrB_Info GrB_free(GrB_Semiring   *x) { return GrB_Semiring_free(x);   }
static inline GrB_Info GrB_free(GrB_Vector     *x) { return GrB_Vector_free(x);     }
static inline GrB_Info GrB_free(GrB_Matrix     *x) { return GrB_Matrix_free(x);     }
static inline GrB_Info GrB_free(GrB_Descriptor *x) { return GrB_Descriptor_free(x); }

static inline
GrB_Info GrB_eWiseMult(GrB_Vector             w,
		       const GrB_Vector       mask,
		       const GrB_BinaryOp     accum,
		       const GrB_Semiring     op,
		       const GrB_Vector       u,
		       const GrB_Vector       v,
		       const GrB_Descriptor   desc)
{
	return GrB_Vector_eWiseMult_Semiring(w,mask,accum,op,u,v,desc);
}

static inline
GrB_Info GrB_eWiseMult(GrB_Vector             w,
		       const GrB_Vector       mask,
		       const GrB_BinaryOp     accum,
		       const GrB_Monoid       op,
		       const GrB_Vector       u,
		       const GrB_Vector       v,
		       const GrB_Descriptor   desc)
{
	return GrB_Vector_eWiseMult_Monoid(w,mask,accum,op,u,v,desc);
}

static inline
GrB_Info GrB_eWiseMult(GrB_Vector             w,
		       const GrB_Vector       mask,
		       const GrB_BinaryOp     accum,
		       const GrB_BinaryOp     op,
		       const GrB_Vector       u,
		       const GrB_Vector       v,
		       const GrB_Descriptor   desc)
{
	return GrB_Vector_eWiseMult_BinaryOp(w,mask,accum,op,u,v,desc);
}

static inline
GrB_Info GrB_eWiseMult(GrB_Matrix             C,
		       const GrB_Matrix       mask,
		       const GrB_BinaryOp     accum,
		       const GrB_Semiring     op,
		       const GrB_Matrix       A,
		       const GrB_Matrix       B,
		       const GrB_Descriptor   desc)
{
	return GrB_Matrix_eWiseMult_Semiring(C,mask,accum,op,A,B,desc);
}

static inline
GrB_Info GrB_eWiseMult(GrB_Matrix             C,
		       const GrB_Matrix       mask,
		       const GrB_BinaryOp     accum,
		       const GrB_Monoid       op,
		       const GrB_Matrix       A,
		       const GrB_Matrix       B,
		       const GrB_Descriptor   desc)
{
	return GrB_Matrix_eWiseMult_Monoid(C,mask,accum,op,A,B,desc);
}

static inline
GrB_Info GrB_eWiseMult(GrB_Matrix             C,
		       const GrB_Matrix       mask,
		       const GrB_BinaryOp     accum,
		       const GrB_BinaryOp     op,
		       const GrB_Matrix       A,
		       const GrB_Matrix       B,
		       const GrB_Descriptor   desc)
{
	return GrB_Matrix_eWiseMult_BinaryOp(C,mask,accum,op,A,B,desc);
}

static inline
GrB_Info GrB_eWiseAdd (GrB_Vector             w,
		       const GrB_Vector       mask,
		       const GrB_BinaryOp     accum,
		       const GrB_Semiring     op,
		       const GrB_Vector       u,
		       const GrB_Vector       v,
		       const GrB_Descriptor   desc)
{
	return GrB_Vector_eWiseAdd_Semiring(w,mask,accum,op,u,v,desc);
}

static inline
GrB_Info GrB_eWiseAdd (GrB_Vector             w,
		       const GrB_Vector       mask,
		       const GrB_BinaryOp     accum,
		       const GrB_Monoid       op,
		       const GrB_Vector       u,
		       const GrB_Vector       v,
		       const GrB_Descriptor   desc)
{
	return GrB_Vector_eWiseAdd_Monoid(w,mask,accum,op,u,v,desc);
}

static inline
GrB_Info GrB_eWiseAdd (GrB_Vector             w,
		       const GrB_Vector       mask,
		       const GrB_BinaryOp     accum,
		       const GrB_BinaryOp     op,
		       const GrB_Vector       u,
		       const GrB_Vector       v,
		       const GrB_Descriptor   desc)
{
	return GrB_Vector_eWiseAdd_BinaryOp(w,mask,accum,op,u,v,desc);
}

static inline
GrB_Info GrB_eWiseAdd (GrB_Matrix             C,
		       const GrB_Matrix       mask,
		       const GrB_BinaryOp     accum,
		       const GrB_Semiring     op,
		       const GrB_Matrix       A,
		       const GrB_Matrix       B,
		       const GrB_Descriptor   desc)
{
	return GrB_Matrix_eWiseAdd_Semiring(C,mask,accum,op,A,B,desc);
}

static inline
GrB_Info GrB_eWiseAdd (GrB_Matrix             C,
		       const GrB_Matrix       mask,
		       const GrB_BinaryOp     accum,
		       const GrB_Monoid       op,
		       const GrB_Matrix       A,
		       const GrB_Matrix       B,
		       const GrB_Descriptor   desc)
{
	return GrB_Matrix_eWiseAdd_Monoid(C,mask,accum,op,A,B,desc);
}

static inline
GrB_Info GrB_eWiseAdd (GrB_Matrix             C,
		       const GrB_Matrix       mask,
		       const GrB_BinaryOp     accum,
		       const GrB_BinaryOp     op,
		       const GrB_Matrix       A,
		       const GrB_Matrix       B,
		       const GrB_Descriptor   desc)
{
	return GrB_Matrix_eWiseAdd_BinaryOp(C,mask,accum,op,A,B,desc);
}

static inline
GrB_Info GrB_assign(GrB_Vector            w,
		    const GrB_Vector      mask,
		    const GrB_BinaryOp    accum,
		    const GrB_Vector      u,
		    const GrB_Index      *indices,
		    GrB_Index             nindices,
		    const GrB_Descriptor  desc)
{
	return GrB_Vector_assign(w,mask,accum,u,indices,nindices,desc);
}

static inline
GrB_Info GrB_assign(GrB_Matrix            C,
		    const GrB_Matrix      Mask,
		    const GrB_BinaryOp    accum,
		    const GrB_Matrix      A,
		    const GrB_Index      *row_indices,
		    GrB_Index             nrows,
		    const GrB_Index      *col_indices,
		    GrB_Index             ncols,
		    const GrB_Descriptor  desc)
{
	return GrB_Matrix_assign(C,Mask,accum,A,row_indices,nrows,col_indices,ncols,desc);
}

static inline
GrB_Info GrB_assign(GrB_Matrix            C,
		    const GrB_Vector      mask,
		    const GrB_BinaryOp    accum,
		    const GrB_Vector      u,
		    const GrB_Index      *row_indices,
		    GrB_Index             nrows,
		    GrB_Index             col_index,
		    const GrB_Descriptor  desc)
{
	return GrB_Col_assign(C,mask,accum,u,row_indices,nrows,col_index,desc);
}

static inline
GrB_Info GrB_assign(GrB_Matrix            C,
		    const GrB_Vector      mask,
		    const GrB_BinaryOp    accum,
		    const GrB_Vector      u,
		    GrB_Index             row_index,
		    const GrB_Index      *col_indices,
		    GrB_Index             ncols,
		    const GrB_Descriptor  desc)
{
	return GrB_Row_assign(C,mask,accum,u,row_index,col_indices,ncols,desc);
}

#define GrB_Vector_assign(type, TYPE)                                          		\
static inline                                                                 		\
GrB_Info GrB_assign(GrB_Vector            w,						\
		    const GrB_Vector      mask,						\
		    const GrB_BinaryOp    accum,					\
		    type                  val,						\
		    const GrB_Index      *indices,					\
		    GrB_Index             nindices,					\
		    const GrB_Descriptor  desc)						\
{                                                                               	\
       return GrB_Vector_assign_ ## TYPE (w,mask,accum,val,indices,nindices,desc);	\
}

GrB_Instantiate_Polymorphic_Value(GrB_Vector_assign)

#undef GrB_Vector_assign

#define GrB_Matrix_assign(type, TYPE)                                          		\
static inline                                                                 		\
GrB_Info GrB_assign(GrB_Matrix            C,						\
		    const GrB_Matrix      Mask,						\
		    const GrB_BinaryOp    accum,					\
		    type                  val,						\
		    const GrB_Index      *row_indices,					\
		    GrB_Index             nrows,					\
		    const GrB_Index      *col_indices,					\
		    GrB_Index             ncols,					\
		    const GrB_Descriptor  desc)						\
{                                                                               	\
       return GrB_Matrix_assign_ ## TYPE (C,Mask,accum,val,row_indices,nrows,col_indices,ncols,desc);	\
}

GrB_Instantiate_Polymorphic_Value(GrB_Matrix_assign)

#undef GrB_Matrix_assign

static inline
GrB_Info GrB_apply(GrB_Vector             w,
		   const GrB_Vector       mask,
		   const GrB_BinaryOp     accum,
		   const GrB_UnaryOp      op,
		   const GrB_Vector       u,
		   const GrB_Descriptor   desc)
{
	return GrB_Vector_apply(w,mask,accum,op,u,desc);
}

static inline
GrB_Info GrB_apply(GrB_Matrix            C,
		   const GrB_Matrix      Mask,
		   const GrB_BinaryOp    accum,
		   const GrB_UnaryOp     op,
		   const GrB_Matrix      A,
		   const GrB_Descriptor  desc)
{
	return GrB_Matrix_apply(C,Mask,accum,op,A,desc);
}

#define GrB_Matrix_reduce(type, TYPE)                                          	\
static inline                                                                 	\
GrB_Info GrB_reduce(type *val, const GrB_BinaryOp accum, const GrB_Monoid op,	\
		    const GrB_Matrix A, const GrB_Descriptor desc)              \
{                                                                               \
        return GrB_Matrix_reduce_ ## TYPE (val,accum,op,A,desc);              	\
}

GrB_Instantiate_Polymorphic_Pointer(GrB_Matrix_reduce)

#undef GrB_Matrix_reduce

#define GrB_Vector_reduce(type, TYPE)                                          	\
static inline                                                                 	\
GrB_Info GrB_reduce(type *val, const GrB_BinaryOp accum, const GrB_Monoid op,	\
		    const GrB_Vector A, const GrB_Descriptor desc)              \
{                                                                               \
        return GrB_Vector_reduce_ ## TYPE (val,accum,op,A,desc);              	\
}

GrB_Instantiate_Polymorphic_Pointer(GrB_Vector_reduce)

#undef GrB_Vector_reduce

static inline
GrB_Info GrB_reduce(GrB_Vector             w,
		    const GrB_Vector       mask,
		    const GrB_BinaryOp     accum,
		    const GrB_Monoid       op,
		    const GrB_Matrix       A,
		    const GrB_Descriptor   desc)
{
	return GrB_Matrix_reduce_Monoid(w,mask,accum,op,A,desc);
}

static inline
GrB_Info GrB_reduce(GrB_Vector             w,
		    const GrB_Vector       mask,
		    const GrB_BinaryOp     accum,
		    const GrB_BinaryOp     op,
		    const GrB_Matrix       A,
		    const GrB_Descriptor   desc)
{
	return GrB_Matrix_reduce_BinaryOp(w,mask,accum,op,A,desc);
}

#undef GrB_Instantiate_Polymorphic_Value
#undef GrB_Instantiate_Polymorphic_Pointer

}

#else

#define GrB_Monoid_new(m,b,i) _Generic((i),             \
        bool            : GrB_Monoid_new_BOOL,          \
        int8_t          : GrB_Monoid_new_INT8,          \
        uint8_t         : GrB_Monoid_new_UINT8,         \
        int16_t         : GrB_Monoid_new_INT16,         \
        uint16_t        : GrB_Monoid_new_UINT16,        \
        int32_t         : GrB_Monoid_new_INT32,         \
        uint32_t        : GrB_Monoid_new_UINT32,        \
        int64_t         : GrB_Monoid_new_INT64,         \
        uint64_t        : GrB_Monoid_new_UINT64,        \
        float           : GrB_Monoid_new_FP32,          \
        double          : GrB_Monoid_new_FP64,          \
        default         : GrB_Monoid_new_UDT            \
)(m,b,i)

#define GrB_Vector_build(w,indices,values,n,dup) _Generic((values),     \
  const bool*           : GrB_Vector_build_BOOL,                        \
        bool*           : GrB_Vector_build_BOOL,                        \
  const int8_t*         : GrB_Vector_build_INT8,                        \
        int8_t*         : GrB_Vector_build_INT8,                        \
  const uint8_t*        : GrB_Vector_build_UINT8,                       \
        uint8_t*        : GrB_Vector_build_UINT8,                       \
  const int16_t*        : GrB_Vector_build_INT16,                       \
        int16_t*        : GrB_Vector_build_INT16,                       \
  const uint16_t*       : GrB_Vector_build_UINT16,                      \
        uint16_t*       : GrB_Vector_build_UINT16,                      \
  const int32_t*        : GrB_Vector_build_INT32,                       \
        int32_t*        : GrB_Vector_build_INT32,                       \
  const uint32_t*       : GrB_Vector_build_UINT32,                      \
        uint32_t*       : GrB_Vector_build_UINT32,                      \
  const int64_t*        : GrB_Vector_build_INT64,                       \
        int64_t*        : GrB_Vector_build_INT64,                       \
  const uint64_t*       : GrB_Vector_build_UINT64,                      \
        uint64_t*       : GrB_Vector_build_UINT64,                      \
  const float*          : GrB_Vector_build_FP32,                        \
        float*          : GrB_Vector_build_FP32,                        \
  const double*         : GrB_Vector_build_FP64,                        \
        double*         : GrB_Vector_build_FP64,                        \
  const void*           : GrB_Vector_build_UDT,                         \
        void*           : GrB_Vector_build_UDT                          \
)(w,indices,values,n,dup)

#define GrB_Vector_setElement(w,val,index) _Generic((val),      \
        bool     : GrB_Vector_setElement_BOOL,                  \
        int8_t   : GrB_Vector_setElement_INT8,                  \
        uint8_t  : GrB_Vector_setElement_UINT8,                 \
        int16_t  : GrB_Vector_setElement_INT16,                 \
        uint16_t : GrB_Vector_setElement_UINT16,                \
        int32_t  : GrB_Vector_setElement_INT32,                 \
        uint32_t : GrB_Vector_setElement_UINT32,                \
        int64_t  : GrB_Vector_setElement_INT64,                 \
        uint64_t : GrB_Vector_setElement_UINT64,                \
        float    : GrB_Vector_setElement_FP32,                  \
        double   : GrB_Vector_setElement_FP64,                  \
        default  : GrB_Vector_setElement_UDT                    \
)(w,val,index)

#define GrB_Vector_extractElement(val,u,index) _Generic((val),  \
        bool*           : GrB_Vector_extractElement_BOOL,       \
        int8_t*         : GrB_Vector_extractElement_INT8,       \
        uint8_t*        : GrB_Vector_extractElement_UINT8,      \
        int16_t*        : GrB_Vector_extractElement_INT16,      \
        uint16_t*       : GrB_Vector_extractElement_UINT16,     \
        int32_t*        : GrB_Vector_extractElement_INT32,      \
        uint32_t*       : GrB_Vector_extractElement_UINT32,     \
        int64_t*        : GrB_Vector_extractElement_INT64,      \
        uint64_t*       : GrB_Vector_extractElement_UINT64,     \
        float*          : GrB_Vector_extractElement_FP32,       \
        double*         : GrB_Vector_extractElement_FP64,       \
        void*           : GrB_Vector_extractElement_UDT         \
)(val,u,index)

#define GrB_Vector_extractTuples(indices,values,n,v) _Generic((values), \
        bool     : GrB_Vector_extractTuples_BOOL,                       \
        int8_t   : GrB_Vector_extractTuples_INT8,                       \
        uint8_t  : GrB_Vector_extractTuples_UINT8,                      \
        int16_t  : GrB_Vector_extractTuples_INT16,                      \
        uint16_t : GrB_Vector_extractTuples_UINT16,                     \
        int32_t  : GrB_Vector_extractTuples_INT32,                      \
        uint32_t : GrB_Vector_extractTuples_UINT32,                     \
        int64_t  : GrB_Vector_extractTuples_INT64,                      \
        uint64_t : GrB_Vector_extractTuples_UINT64,                     \
        float    : GrB_Vector_extractTuples_FP32,                       \
        double   : GrB_Vector_extractTuples_FP64,                       \
        default  : GrB_Vector_extractTuples_UDT                         \
)(indices,values,n,v)

#define GrB_Matrix_build(C,row_indices,col_indices,values,nvals,dup) _Generic((values), \
  const bool*           : GrB_Matrix_build_BOOL,                        \
        bool*           : GrB_Matrix_build_BOOL,                        \
  const int8_t*         : GrB_Matrix_build_INT8,                        \
        int8_t*         : GrB_Matrix_build_INT8,                        \
  const uint8_t*        : GrB_Matrix_build_UINT8,                       \
        uint8_t*        : GrB_Matrix_build_UINT8,                       \
  const int16_t*        : GrB_Matrix_build_INT16,                       \
        int16_t*        : GrB_Matrix_build_INT16,                       \
  const uint16_t*       : GrB_Matrix_build_UINT16,                      \
        uint16_t*       : GrB_Matrix_build_UINT16,                      \
  const int32_t*        : GrB_Matrix_build_INT32,                       \
        int32_t*        : GrB_Matrix_build_INT32,                       \
  const uint32_t*       : GrB_Matrix_build_UINT32,                      \
        uint32_t*       : GrB_Matrix_build_UINT32,                      \
  const int64_t*        : GrB_Matrix_build_INT64,                       \
        int64_t*        : GrB_Matrix_build_INT64,                       \
  const uint64_t*       : GrB_Matrix_build_UINT64,                      \
        uint64_t*       : GrB_Matrix_build_UINT64,                      \
  const float*          : GrB_Matrix_build_FP32,                        \
        float*          : GrB_Matrix_build_FP32,                        \
  const double*         : GrB_Matrix_build_FP64,                        \
        double*         : GrB_Matrix_build_FP64,                        \
  const void*           : GrB_Matrix_build_UDT,                         \
        void*           : GrB_Matrix_build_UDT                          \
)(C,row_indices,col_indices,values,nvals,dup)

#define GrB_Matrix_setElement(w,val,row_index, col_index) _Generic((val),       \
        bool     : GrB_Matrix_setElement_BOOL,                  \
        int8_t   : GrB_Matrix_setElement_INT8,                  \
        uint8_t  : GrB_Matrix_setElement_UINT8,                 \
        int16_t  : GrB_Matrix_setElement_INT16,                 \
        uint16_t : GrB_Matrix_setElement_UINT16,                \
        int32_t  : GrB_Matrix_setElement_INT32,                 \
        uint32_t : GrB_Matrix_setElement_UINT32,                \
        int64_t  : GrB_Matrix_setElement_INT64,                 \
        uint64_t : GrB_Matrix_setElement_UINT64,                \
        float    : GrB_Matrix_setElement_FP32,                  \
        double   : GrB_Matrix_setElement_FP64,                  \
        default  : GrB_Matrix_setElement_UDT                    \
)(w,val,row_index,col_index)

#define GrB_Matrix_extractElement(val,u,row_index,col_index) _Generic((val),    \
        bool*     : GrB_Matrix_extractElement_BOOL,                             \
        int8_t*   : GrB_Matrix_extractElement_INT8,                             \
        uint8_t*  : GrB_Matrix_extractElement_UINT8,                            \
        int16_t*  : GrB_Matrix_extractElement_INT16,                            \
        uint16_t* : GrB_Matrix_extractElement_UINT16,                           \
        int32_t*  : GrB_Matrix_extractElement_INT32,                            \
        uint32_t* : GrB_Matrix_extractElement_UINT32,                           \
        int64_t*  : GrB_Matrix_extractElement_INT64,                            \
        uint64_t* : GrB_Matrix_extractElement_UINT64,                           \
        float*    : GrB_Matrix_extractElement_FP32,                             \
        double*   : GrB_Matrix_extractElement_FP64,                             \
        void*     : GrB_Matrix_extractElement_UDT                               \
)(val,u,row_index,col_index)

#define GrB_Matrix_extractTuples(row_indices,col_indices,values,n,v) _Generic((values), \
        bool*     : GrB_Matrix_extractTuples_BOOL,                                      \
        int8_t*   : GrB_Matrix_extractTuples_INT8,                                      \
        uint8_t*  : GrB_Matrix_extractTuples_UINT8,                                     \
        int16_t*  : GrB_Matrix_extractTuples_INT16,                                     \
        uint16_t* : GrB_Matrix_extractTuples_UINT16,                                    \
        int32_t*  : GrB_Matrix_extractTuples_INT32,                                     \
        uint32_t* : GrB_Matrix_extractTuples_UINT32,                                    \
        int64_t*  : GrB_Matrix_extractTuples_INT64,                                     \
        uint64_t* : GrB_Matrix_extractTuples_UINT64,                                    \
        float*    : GrB_Matrix_extractTuples_FP32,                                      \
        double*   : GrB_Matrix_extractTuples_FP64,                                      \
        void*     : GrB_Matrix_extractTuples_UDT                                        \
)(row_indices,col_indices,values,n,v)

#define GrB_free(x) _Generic((x),               \
        GrB_Type*       : GrB_Type_free,        \
        GrB_UnaryOp*    : GrB_UnaryOp_free,     \
        GrB_BinaryOp*   : GrB_BinaryOp_free,    \
        GrB_Monoid*     : GrB_Monoid_free,      \
        GrB_Semiring*   : GrB_Semiring_free,    \
        GrB_Vector*     : GrB_Vector_free,      \
        GrB_Matrix*     : GrB_Matrix_free,      \
        GrB_Descriptor* : GrB_Descriptor_free   \
)(x)

#define GrB_Vector_eWiseMult(w,mask,accum,op,u,v,desc) _Generic((op),   \
        GrB_Semiring    : GrB_Vector_eWiseMult_Semiring,                \
        GrB_Monoid      : GrB_Vector_eWiseMult_Monoid  ,                \
        GrB_BinaryOp    : GrB_Vector_eWiseMult_BinaryOp                 \
)

#define GrB_Matrix_eWiseMult(w,mask,accum,op,u,v,desc) _Generic((op),   \
        GrB_Semiring    : GrB_Matrix_eWiseMult_Semiring,                \
        GrB_Monoid      : GrB_Matrix_eWiseMult_Monoid  ,                \
        GrB_BinaryOp    : GrB_Matrix_eWiseMult_BinaryOp                 \
)

#define GrB_eWiseMult(w,mask,accum,op,u,v,desc) _Generic((w),                   \
        GrB_Vector      : GrB_Vector_eWiseMult(w,mask,accum,op,u,v,desc),       \
        GrB_Matrix      : GrB_Matrix_eWiseMult(w,mask,accum,op,u,v,desc)        \
)(w,mask,accum,op,u,v,desc)

#define GrB_Vector_eWiseAdd(w,mask,accum,op,u,v,desc) _Generic((op),    \
        GrB_Semiring    : GrB_Vector_eWiseAdd_Semiring,                 \
        GrB_Monoid      : GrB_Vector_eWiseAdd_Monoid  ,                 \
        GrB_BinaryOp    : GrB_Vector_eWiseAdd_BinaryOp                  \
)

#define GrB_Matrix_eWiseAdd(w,mask,accum,op,u,v,desc) _Generic((op),    \
        GrB_Semiring    : GrB_Matrix_eWiseAdd_Semiring,                 \
        GrB_Monoid      : GrB_Matrix_eWiseAdd_Monoid  ,                 \
        GrB_BinaryOp    : GrB_Matrix_eWiseAdd_BinaryOp                  \
)

#define GrB_eWiseAdd(w,mask,accum,op,u,v,desc) _Generic((w),                    \
        GrB_Vector      : GrB_Vector_eWiseAdd(w,mask,accum,op,u,v,desc),        \
        GrB_Matrix      : GrB_Matrix_eWiseAdd(w,mask,accum,op,u,v,desc)         \
)(w,mask,accum,op,u,v,desc)

#define GrB_assign_7(u,mask,accum,val,indices,n,desc) _Generic((val),   \
        GrB_Vector : GrB_Vector_assign,                                 \
        bool       : GrB_Vector_assign_BOOL,                            \
        int8_t     : GrB_Vector_assign_INT8,                            \
        uint8_t    : GrB_Vector_assign_UINT8,                           \
        int16_t    : GrB_Vector_assign_INT16,                           \
        uint16_t   : GrB_Vector_assign_UINT16,                          \
        int32_t    : GrB_Vector_assign_INT32,                           \
        uint32_t   : GrB_Vector_assign_UINT32,                          \
        int64_t    : GrB_Vector_assign_INT64,                           \
        uint64_t   : GrB_Vector_assign_UINT64,                          \
        float      : GrB_Vector_assign_FP32,                            \
        double     : GrB_Vector_assign_FP64,                            \
        default    : GrB_Vector_assign_UDT                              \
)(u,mask,accum,val,indices,n,desc)

#define GrB_assign_8(C,mask,accum,u,row,col,n,desc) _Generic((row),     \
        GrB_Index        : GrB_Row_assign,                              \
        const GrB_Index* : GrB_Col_assign                               \
)(C,mask,accum,u,row,col,n,desc)

#define GrB_assign_9(C,Mask,accum,val,rows,m,cols,n,desc) _Generic((val),       \
        GrB_Matrix : GrB_Matrix_assign,                                         \
        bool       : GrB_Matrix_assign_BOOL,                                    \
        int8_t     : GrB_Matrix_assign_INT8,                                    \
        uint8_t    : GrB_Matrix_assign_UINT8,                                   \
        int16_t    : GrB_Matrix_assign_INT16,                                   \
        uint16_t   : GrB_Matrix_assign_UINT16,                                  \
        int32_t    : GrB_Matrix_assign_INT32,                                   \
        uint32_t   : GrB_Matrix_assign_UINT32,                                  \
        int64_t    : GrB_Matrix_assign_INT64,                                   \
        uint64_t   : GrB_Matrix_assign_UINT64,                                  \
        float      : GrB_Matrix_assign_FP32,                                    \
        double     : GrB_Matrix_assign_FP64,                                    \
        default    : GrB_Matrix_assign_UDT                                      \
)(C,Mask,accum,val,rows,m,cols,n,desc)

#define GrB_assign(...) GrB_GET_7_OR_8_OR_9(__VA_ARGS__,GrB_assign_9,GrB_assign_8,GrB_assign_7)(__VA_ARGS__)

#define GrB_apply(w,mask,accum,op,u,desc) _Generic((w), \
        GrB_Vector      : GrB_Vector_apply,             \
        GrB_Matrix      : GrB_Matrix_apply              \
)(w,mask,accum,op,u,desc)

#define GrB_Vector_reduce(val,accum,op,u,desc) _Generic((val),          \
        bool*           : GrB_Vector_reduce_BOOL,                       \
        int8_t*         : GrB_Vector_reduce_INT8,                       \
        uint8_t*        : GrB_Vector_reduce_UINT8,                      \
        int16_t*        : GrB_Vector_reduce_INT16,                      \
        uint16_t*       : GrB_Vector_reduce_UINT16,                     \
        int32_t*        : GrB_Vector_reduce_INT32,                      \
        uint32_t*       : GrB_Vector_reduce_UINT32,                     \
        int64_t*        : GrB_Vector_reduce_INT64,                      \
        uint64_t*       : GrB_Vector_reduce_UINT64,                     \
        float*          : GrB_Vector_reduce_FP32,                       \
        double*         : GrB_Vector_reduce_FP64,                       \
        default         : GrB_Vector_reduce_UDT                         \
)

#define GrB_Matrix_reduce(val,accum,op,u,desc) _Generic((val),          \
        bool*           : GrB_Matrix_reduce_BOOL,                       \
        int8_t*         : GrB_Matrix_reduce_INT8,                       \
        uint8_t*        : GrB_Matrix_reduce_UINT8,                      \
        int16_t*        : GrB_Matrix_reduce_INT16,                      \
        uint16_t*       : GrB_Matrix_reduce_UINT16,                     \
        int32_t*        : GrB_Matrix_reduce_INT32,                      \
        uint32_t*       : GrB_Matrix_reduce_UINT32,                     \
        int64_t*        : GrB_Matrix_reduce_INT64,                      \
        uint64_t*       : GrB_Matrix_reduce_UINT64,                     \
        float*          : GrB_Matrix_reduce_FP32,                       \
        double*         : GrB_Matrix_reduce_FP64,                       \
        default         : GrB_Matrix_reduce_UDT                         \
)

#define GrB_reduce_scalar(val,accum,op,u,desc) _Generic((u),            \
        GrB_Vector      : GrB_Vector_reduce(val,accum,op,u,desc),       \
        GrB_Matrix      : GrB_Matrix_reduce(val,accum,op,u,desc)        \
)(val,accum,op,u,desc)

#define GrB_reduce_vector(w,mask,accum,op,A,desc) _Generic((op),        \
        GrB_BinaryOp    : GrB_Matrix_reduce_BinaryOp,                   \
        GrB_Monoid      : GrB_Matrix_reduce_Monoid                      \
)(w,mask,accum,op,A,desc)

#define GrB_GET_5_OR_6(_1,_2,_3,_4,_5,_6,NAME,...) NAME
#define GrB_reduce(...) GrB_GET_5_OR_6(__VA_ARGS__,GrB_reduce_vector,GrB_reduce_scalar)(__VA_ARGS__)

#endif

#endif // GRAPHBLAS_H
