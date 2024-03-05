#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <cudnn.h>

int main() {
  int m, n, k;
  float *A, *B, *C;

  // Get matrix dimensions from user
  scanf("%d %d %d", &m, &n, &k);

  // Allocate memory for matrices on host
  A = (float *)malloc(m * k * sizeof(float));
  B = (float *)malloc(k * n * sizeof(float));
  C = (float *)malloc(m * n * sizeof(float));

  // Initialize matrices
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < k; ++j) {
      A[i * k + j] = rand() / (float)RAND_MAX;
    }
  }
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < n; ++j) {
      B[i * n + j] = rand() / (float)RAND_MAX;
    }
  }

  // Create cuDNN handle
  cudnnHandle_t handle;
  cudnnCreate(&handle);

  // Set tensor descriptors
  cudnnTensorDescriptor_t xDesc, yDesc, zDesc;
  cudnnCreateTensorDescriptor(&xDesc);
  cudnnCreateTensorDescriptor(&yDesc);
  cudnnCreateTensorDescriptor(&zDesc);
  cudnnSetTensorDescriptor(xDesc, CUDNN_TENSOR_NCHW, CUDNN_DATA_FLOAT, m, k, 1, 1);
  cudnnSetTensorDescriptor(yDesc, CUDNN_TENSOR_NCHW, CUDNN_DATA_FLOAT, k, n, 1, 1);
  cudnnSetTensorDescriptor(zDesc, CUDNN_TENSOR_NCHW, CUDNN_DATA_FLOAT, m, n, 1, 1);

  // Create GEMM descriptor
  cudnnGemmDescriptor_t gemmDesc;
  cudnnCreateGemmDescriptor(&gemmDesc);
  cudnnSetGemmDescriptor(gemmDesc, CUDNN_OP_TENSOR, CUDNN_OP_N, CUDNN_ALPHA_ONE, CUDNN_BETA_ZERO);

  // Allocate device memory for input and output
  float *d_A, *d_B, *d_C;
  cudaMalloc((void **)&d_A, m * k * sizeof(float));
  cudaMalloc((void **)&d_B, k * n * sizeof(float));
  cudaMalloc((void **)&d_C, m * n * sizeof(float));

  // Copy input to device
  cudaMemcpy(d_A, A, m * k * sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(d_B, B, k * n * sizeof(float), cudaMemcpyHostToDevice);

  // Execute GEMM
  cudnnGemm(handle, gemmDesc, d_A, xDesc, d_B, yDesc, d_C, zDesc);

  // Copy output back to host
  cudaMemcpy(C, d_C, m * n * sizeof(float), cudaMemcpyDeviceToHost);

  // Print results
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%f ", C[i * n + j]);
    }
    printf("\n");
  }

  // Free memory
  free(A);
  free(B);
  free(C);
  cudaFree(d_A);
  cudaFree(d_B);
  cudaFree(d_C);

  // Destroy cuDNN handle
  cudnnDestroy(handle);

  return 0;
}
