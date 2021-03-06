// Copyright 2020 The TensorFlow Runtime Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//===- Mlir-Opt utility ---------------------------------------------------===//
//
// Load MLIR and apply required passes on it.
//
//===----------------------------------------------------------------------===//

#include "mlir/Support/MlirOptMain.h"
#include "tfrt/gpu/kernels/cuda_opdefs/cuda_ops.h"
#include "tfrt/gpu/kernels/cuda_opdefs/cuda_test_ops.h"
#include "tfrt/init_tfrt_dialects.h"

int main(int argc, char **argv) {
  mlir::DialectRegistry registry;
  tfrt::RegisterTFRTDialects(registry);
  registry.insert<tfrt::cuda::CUDADialect>();
  registry.insert<tfrt::cuda::CUDATestDialect>();
  return failed(mlir::MlirOptMain(argc, argv, "TFRT pass driver\n", registry));
}
