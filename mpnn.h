/*
 * The head file for MLNN.
 * Author: wangjun
 * Email : 1427014893@qq.com
 */

#ifndef MPNN_H_
#define MPNN_H_

enum MPNN_DataType {
  MPNN_DTYPE_INT32 = 0,
  MPNN_DTYPE_INT16 = 1,
  MPNN_DTYPE_FLOAT32 = 2,
  MPNN_DTYPE_FLOAT16 = 3,
};

enum MPNN_Layout {
  MPNN_Layout_ARRAY = 0,
  MPNN_Layout_NCHW = 1,
  MPNN_Layout_NHWC = 2,
};

typedef TensorStruct* TensorDescriptor;

void CreateTensorDescriptor(TensorDescriptor* tensor_desc) {
  if (tensor_desc == nullptr) {
    TensorStruct* temp = new TensorStruct();
    tensor_desc = &temp;
  } else {
  }
}

void DestroyTensorDescriptor(TensorDescriptor tensor_desc) {
  if (tensor_desc != nullptr) {
    delete tensor_desc;
  }
}

#undef
