/* Copyright (c) 2020 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#ifdef PADDLE_WITH_XPU
#include "paddle/fluid/operators/elementwise/elementwise_div_op.h"
#include "paddle/fluid/operators/elementwise/elementwise_op.h"
#include "paddle/fluid/operators/elementwise/elementwise_xpu.h"
namespace paddle {
namespace operators {

template <typename DeviceContext, typename T>
class ElementwiseFloordivXPUKernel : public framework::OpKernel<T> {
  using XPUType = typename XPUTypeTrait<T>::Type;

 public:
  void Compute(const framework::ExecutionContext& ctx) const override {
    auto f = [](xpu::Context* ctx,
              const XPUType* x,
              const XPUType* y,
              XPUType* z,
              const std::vector<int>& xshape,
              const std::vector<int>& yshape) {
    return xpu::broadcast_floordiv<XPUType>(ctx, x, y, z, xshape, yshape);
  };
    XPUElementwise<T, XPUType>(ctx, f);
  }
};

}  // namespace operators
}  // namespace paddle
namespace ops = paddle::operators;
REGISTER_OP_XPU_KERNEL(
    elementwise_floordiv,
    ops::ElementwiseFloordivXPUKernel<paddle::platform::XPUDeviceContext,
                                      float>,
    ops::ElementwiseFloordivXPUKernel<paddle::platform::XPUDeviceContext,
                                      paddle::platform::float16>);

#endif
