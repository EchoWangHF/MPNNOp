/*
 * The head file for baseop.
 * Author: wangjun
 * Email : 1427014893@qq.com
 */

#ifndef CORE_TENSOR_H_
#define CORE_TENSOR_H_

#include <assert.h>
#include <stdint.h>
#include <vector>

#include mpnn.h

namespace MPNN {
class BaseOp {
 public:
  BaseOp(){};
  virtual ~BaseOp(){};
  void compute(Device device);

 private:
  virtual void cpuCompute();
};
};  // namespace MPNN

#undef
