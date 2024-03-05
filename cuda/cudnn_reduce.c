#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <cudnn.h>

int main() {
  int m, n;
  float *A, *C;

  // Get matrix dimensions from user
  scanf("%d %d", &m, &n);

  // Allocate memory for matrices on host
  A = (float *)malloc(m * n * sizeof(float));
  C = (float *)malloc(n * sizeof(float));

  // Initialize matrices
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      A[i * n + j] = rand() / (float)RAND_MAX;
    }
  }

  // Create cuDNN handle
  cudnnHandle_t handle;
  cudnnCreate(&handle);

  // Set tensor descriptors
  cudnnTensorDescriptor_t xDesc, yDesc;
  cudnnCreateTensorDescriptor(&xDesc);
  cudnnCreateTensorDescriptor(&yDesc);
  cudnnSetTensorDescriptor(xDesc, CUDNN_TENSOR_NCHW, CUDNN_DATA_FLOAT, m, n, 1, 1);
  cudnnSetTensorDescriptor(yDesc, CUDNN_TENSOR_NCHW, CUDNN_DATA_FLOAT, 1, n, 1, 1);

  // Create reduction descriptor
  cudnnReduceTensorDescriptor_t reduceDesc;
  cudnnCreateReduceTensorDescriptor(&reduceDesc);
  cudnnSetReduceTensorDescriptor(reduceDesc, CUDNN_REDUCE_SUM, CUDNN_DATA_FLOAT, CUDNN_NOT_REDUCE_INDICES, CUDNN_ONE, CUDNN_ZERO);

  // Create cudnn plan
  cudnnPlan_t plan;
  cudnnCreatePlan(handle, &plan, reduceDesc, xDesc, yDesc, NULL);

  // Allocate device memory for input and output
  float *d_A, *d_C;
  cudaMalloc((void **)&d_A, m * n * sizeof(float));
  cudaMalloc((void **)&d_C, n * sizeof(float));

  // Copy input to device
  cudaMemcpy(d_A, A, m * n * sizeof(float), cudaMemcpyHostToDevice);

  // Execute reduction
  cudnnReduceTensor(handle, plan, d_A, d_C);

  // Copy output back to host
  cudaMemcpy(C, d_C, n * sizeof(float), cudaMemcpyDeviceToHost);

  // Print results
  for (int i = 0; i < n; ++i) {
    printf("%f ", C[i]);
  }
  printf("\n");

  // Free memory
  free(A);
  free(C);
  cudaFree(d_A);
  cudaFree(d_C);

  // Destroy cuDNN handle
  cudnnDestroy(handle);

  return 0;
}
