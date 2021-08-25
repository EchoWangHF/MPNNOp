/*
 * The head file for tensor.
 * Author: wangjun
 * Email : 1427014893@qq.com
 */

#ifndef KERNELS_INCLUDE_CORE_TENSOR_H_
#define KERNELS_INCLUDE_CORE_TENSOR_H_

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <vector>

#include "core/core.h"

namespace MNNL {
class Tensor {
 public:
  Tensor() : _dtype(DTYPE_FLOAT32), _layout(Layout_ARRAY), _dims_size(0){};

  Tensor(const DataType &dtype, const Layout &layout, const uint32_t &dims_size,
         const std::vector<uint32_t> &dims)
      : _dtype(dtype), _layout(layout), _dims_size(dims_size), _dims(dims){};

  Tensor(const DataType &dtype, const Layout &layout,
         const std::vector<uint32_t> &dims)
      : _dtype(dtype), _layout(layout), _dims_size(dims.size()), _dims(dims){};

  Tensor(const DataType &dtype, const Layout &layout, const uint32_t &dims_size,
         const uint32_t *dims[]);

  virtual ~Tensor(){

  };

  DataType getDataType() const { return _dtype; }
  void setDataType(const DataType &dtype) { _dtype = dtype; }

  Layout getLayout() const { return _layout; }
  void setLayout(const Layout &layout) { _layout = layout; }

  uint32_t getDimSize() const { return _dims_size; }
  void setDimSize(const uint32_t &dim_size) { _dims_size = dim_size; }

  std::vector<uint32_t> getDims() const { return _dims; }
  void setDims(const std::vector<uint32_t> &dims) { _dims = dims; }

 private:
  DataType _dtype;
  Layout _layout;
  uint32_t _dims_size;
  std::vector<uint32_t> _dims;
};

};  // namespace MNNL

#endif
