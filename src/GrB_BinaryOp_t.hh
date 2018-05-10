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

#ifndef GRB_BINARYOP_T_H
#define GRB_BINARYOP_T_H

struct GrB_BinaryOp_t
{
private:

    GrB_Type _D_in_1;
    GrB_Type _D_in_2;
    GrB_Type _D_out;
    void (*_F)(void*, const void*, const void*);
    bool     _valid;

public:

    GrB_BinaryOp_t(GrB_Type,GrB_Type,GrB_Type,void (*)(void*, const void*, const void*));
    ~GrB_BinaryOp_t();

    bool valid() const;
    GrB_Type D_in_1() const;
    GrB_Type D_in_2() const;
    GrB_Type D_out () const;
    void (*F() const)(void*, const void*, const void*);
    void f(void*, const void*, const void*) const;
};

#endif // IBM_GRB_BINARYOP_T_H
