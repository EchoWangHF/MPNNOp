/*
 * The head file for MLNN.
 * Author: wangjun
 * Email : 1427014893@qq.com
 */

#ifndef H_
#define H_
namespace MPNN {
enum DataType {
  DTYPE_INT32 = 0,
  DTYPE_INT16 = 1,
  DTYPE_FLOAT32 = 2,
  DTYPE_FLOAT16 = 3,
};

enum Layout {
  Layout_ARRAY = 0,
  Layout_NCHW = 1,
  Layout_NHWC = 2,
};

enum Device {
  CPU = 0,
  GPU = 1,
  MLU = 2,
};

};  // namespace MPNN

#undef
