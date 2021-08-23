/*
 * The head file for baseop.
 * Author: wangjun
 * Email : 1427014893@qq.com
 */

#ifndef KERNELS_INCLUDE_CORE_BASEOP_H_
#define KERNELS_INCLUDE_CORE_BASEOP_H_

#include <assert.h>
#include <stdint.h>
#include <vector>

#include "core/core.h"

namespace MNNL {
class BaseOp {
 public:
  BaseOp(){};
  virtual ~BaseOp(){};
  void compute(Device device);

 private:
  virtual void cpuCompute();
};
};  // namespace MNNL

#endif
