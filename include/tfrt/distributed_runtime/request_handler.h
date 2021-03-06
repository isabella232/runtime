/*
 * Copyright 2020 The TensorFlow Runtime Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//===- request_handler.h - Request Handler ----------------------*- C++ -*-===//
//
// This file declares RequestHandler, which implements logic to send data, and
// register and execute programs.
//
//===----------------------------------------------------------------------===//

#ifndef TFRT_DISTRIBUTED_RUNTIME_REQUEST_HANDLER_H_
#define TFRT_DISTRIBUTED_RUNTIME_REQUEST_HANDLER_H_

#include <llvm/ADT/ArrayRef.h>
#include <tfrt/support/ref_count.h>

#include "tfrt/distributed_runtime/proto/remote_message.pb.h"
#include "tfrt/support/forward_decls.h"

namespace tfrt {

using CallbackFn = llvm::unique_function<void(Error)>;

class RequestHandlerInterface {
 public:
  virtual ~RequestHandlerInterface() {}

  virtual Error HandleGetDevices(const GetDevicesRequest* request,
                                 GetDevicesResponse* response) = 0;

  virtual Error HandleCreateContext(const CreateContextRequest* request,
                                    CreateContextResponse* response) = 0;

  virtual Error HandleCloseContext(const CloseContextRequest* request,
                                   CloseContextResponse* response) = 0;

  virtual Error HandleSendData(const SendDataRequest* request,
                               SendDataResponse* response) = 0;

  virtual void HandleRegisterFunction(const RegisterFunctionRequest* request,
                                      RegisterFunctionResponse* response,
                                      CallbackFn done) = 0;

  virtual void HandleRemoteExecute(const RemoteExecuteRequest* request,
                                   RemoteExecuteResponse* response,
                                   CallbackFn done) = 0;

  virtual void HandleRemoteExecuteOp(const RemoteExecuteOpRequest* request,
                                     RemoteExecuteOpResponse* response,
                                     CallbackFn done) = 0;

  virtual void HandleDeleteRemoteObjects(
      const DeleteRemoteObjectsRequest* request,
      DeleteRemoteObjectsResponse* response, CallbackFn done) = 0;

  virtual Error HandleKeepAlive(const KeepAliveRequest* request,
                                KeepAliveResponse* response) = 0;
};

}  // namespace tfrt
#endif  // TFRT_DISTRIBUTED_RUNTIME_REQUEST_HANDLER_H_
