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

#ifndef SCALAR_H
#define SCALAR_H

class Scalar
{
private:

    GrB_Type	_D;
    void	*_data;

public:

    Scalar();
    Scalar(const Scalar&);
    Scalar& operator=(const Scalar&);
    ~Scalar();

    Scalar(GrB_Type,const void*);
    Scalar(GrB_Type);
 
    Scalar	operator()(GrB_Type) const;
    operator void*();
    operator const void*() const;
    const GrB_Type	D() const;
};

#endif // SCALAR_H
