#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

__global__ void reduce(const float *A, float *C, int n) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  int tid = threadIdx.x;

  if (i < n) {
    float sum = A[i];
    for (int s = 1; s < blockDim.x; s *= 2) {
      if (tid % (2 * s) == 0) {
        sum += A[i + s];
      }
    }
    C[i] = sum;
  }
}

int main() {
  int n;
  float *A, *C;

  // Get matrix dimensions from user
  scanf("%d", &n);

  // Allocate memory for matrices on host
  A = (float *)malloc(n * sizeof(float));
  C = (float *)malloc(n * sizeof(float));

  // Initialize matrices
  for (int i = 0; i < n; ++i) {
    A[i] = rand() / (float)RAND_MAX;
  }

  // Copy matrices to device
  cudaMalloc((void **)&d_A, n * sizeof(float));
  cudaMalloc((void **)&d_C, n * sizeof(float));
  cudaMemcpy(d_A, A, n * sizeof(float), cudaMemcpyHostToDevice);

  // Launch kernel
  dim3 gridDim(n / 16, 1);
  dim3 blockDim(16, 1);
  reduce<<<gridDim, blockDim>>>(d_A, d_C, n);

  // Copy results back to host
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

  return 0;
}
