/*
 * The head file for baseop.
 * Author: wangjun
 * Email : 1427014893@qq.com
 */

#include "core/baseop.h"

namespace MPNN {
BaseOp::compute(Device device) {
  switch (device) {
    case CPU:
      cpuCompute();
      break;
    default:
      assert(0);
  }
};
