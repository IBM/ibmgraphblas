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

#ifndef GRB_TYPE_T_H
#define GRB_TYPE_T_H

struct GrB_Type_t
{
private:

    bool        _valid;
    size_t      _size;

    template<class IN> void *clone(IN) const;
    void        *clone(const void*) const;

public:

    GrB_Type_t(size_t);
    ~GrB_Type_t();

    bool        valid() const;
    size_t      size() const;
    bool        predefined() const;
    bool        compatible(GrB_Type) const;
    void        *clone(const void*,const GrB_Type) const;
};

#endif // GRB_TYPE_T_H
