/*
 * The cpp file for tensor.
 * Author: wangjun
 * Email : 1427014893@qq.com
 */

#include "core/tensor.h"

namespace MNNL {
Tensor::Tensor(const DataType &dtype, const Layout &layout,
               const uint32_t &dims_size, const uint32_t *dims[])
    : _dtype(dtype),
      _layout(layout),
      _dims_size(dims_size),
      _dims(std::vector<uint32_t>(dims_size, 0)) {
  assert(dims != nullptr);
  memcpy(_dims.data(), dims, dims_size * sizeof(uint32_t));
}
};  // namespace MNNL
