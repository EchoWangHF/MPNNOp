#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

__global__ void gemm(const float *A, const float *B, float *C, int m, int n, int k) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  int j = blockIdx.y * blockDim.y + threadIdx.y;

  if (i < m && j < n) {
    float sum = 0.0f;
    for (int l = 0; l < k; ++l) {
      sum += A[i * k + l] * B[l * n + j];
    }
    C[i * n + j] = sum;
  }
}

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

  // Copy matrices to device
  cudaMalloc((void **)&d_A, m * k * sizeof(float));
  cudaMalloc((void **)&d_B, k * n * sizeof(float));
  cudaMalloc((void **)&d_C, m * n * sizeof(float));
  cudaMemcpy(d_A, A, m * k * sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(d_B, B, k * n * sizeof(float), cudaMemcpyHostToDevice);

  // Launch kernel
  dim3 gridDim(m / 16, n / 16);
  dim3 blockDim(16, 16);
  gemm<<<gridDim, blockDim>>>(d_A, d_B, d_C, m, n, k);

  // Copy results back to host
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

  return 0;
}
