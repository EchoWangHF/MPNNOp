/*
 * The head file for tensor.
 * Author: wangjun
 * Email : 1427014893@qq.com
 */

#ifndef CORE_TENSOR_H_
#define CORE_TENSOR_H_
#include mpnn.h

#define MAX_TENSOR_DIM 8

struct TensorStruct {
  TensorStruct() {}
  ~TensorStruct() {}
  int32_t dim[MAX_TENSOR_DIM];
  int32_t dims;
  MPNN_Layout layout;
  MPNN_DataType dtype;
};

#undef
