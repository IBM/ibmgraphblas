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

#ifndef GRB_MONOID_T_H
#define GRB_MONOID_T_H

struct GrB_Monoid_t
{
private:

    GrB_Type	_D;
    void (*_op)(void*, const void*, const void*);
    void	*_zero;
    size_t	_len;
    bool	_valid;

public:

    GrB_Monoid_t(GrB_Type, 
		 void (*)(void*, const void*, const void*), 
		 const void*, size_t);
    ~GrB_Monoid_t();

    bool	valid() const;
    GrB_Type	D() const;
    GrB_Type	D_out() const;
    GrB_Type	D_in_1() const;
    GrB_Type	D_in_2() const;
    Scalar	zero() const;
    size_t	len() const;
    void (*op() const)(void*, const void*, const void*);
    void f(void*, const void*, const void*) const;
};

#endif // GRB_MONOID_T_H
