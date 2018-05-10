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

#ifndef GRB_DESCRIPTOR_T_H
#define GRB_DESCRIPTOR_T_H

struct GrB_Descriptor_t
{
private:
    
    bool _valid;
    bool _replace;
    bool _scmp;
    bool _tran0;
    bool _tran1;

public:
    GrB_Descriptor_t();
    ~GrB_Descriptor_t();

    bool valid() const;
    bool outp_replace() const;
    bool mask_scmp() const;
    bool inp0_tran() const;
    bool inp1_tran() const;

    void setReplace();
    void setSCMP();
    void setTran0();
    void setTran1();
};

#endif // GRB_DESCRIPTOR_T_H
