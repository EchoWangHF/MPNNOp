// freshman.h头文件
//#ifndef FRESHMAN_H
//#define FRESHMAN_H
// 检查返回结果cudaError_t是否成功
#define CHECK(call)\
{\
  const cudaError_t error=call;\
  if(error!=cudaSuccess)\
  {\
      printf("ERROR: %s:%d,",__FILE__,__LINE__);\
      printf("code:%d,reason:%s\n",error,cudaGetErrorString(error));\
      exit(1);\
  }\
}
//#endif

// SumArrays.cu源代码文件
#include <cuda_runtime.h> // cuda相关头文件
#include <stdio.h>
//#include "freshman.h"

void initialData(float* ip,int size)
{
  time_t t;
  srand((unsigned )time(&t));
  for(int i=0;i<size;i++)
  {
    ip[i]=(float)(rand()%100);
  }
}

void sumArraysCpu(float*a, float*b, float*c, int num) {
  for (int i = 0; i < num; ++i) {
    c[i] = a[i] + b[i];
  }
}

bool resultCheck(float* cpu, float* gpu, int num) {
  for (int i = 0; i < num; ++i) {
    if (cpu[i] != gpu[i]) {
      printf("FAILED!\n");
    }
  }
  printf("PASSED!\n");
}

__global__ void sumArraysCuda(float*a,float*b,float*res)
{
  int i=threadIdx.x;
  res[i]=a[i]+b[i];
}

int main(int argc,char **argv)
{
  int dev = 0;
  cudaSetDevice(dev); // 当有多个GPU时，选定cuda设备，默认是0即第一个主GPU，多GPU时0,1,2以此类推

  int nElem=32;
  printf("Vector size:%d\n",nElem);
  int nByte=sizeof(float)*nElem;
  float *a_h=(float*)malloc(nByte);
  float *b_h=(float*)malloc(nByte);
  float *res_gpu=(float*)malloc(nByte);
  float *res_cpu = (float*)malloc(nByte);
  // memset(res_h,0,nByte);

  float *a_d,*b_d,*res_d;
  CHECK(cudaMalloc((float**)&a_d,nByte));
  CHECK(cudaMalloc((float**)&b_d,nByte));
  CHECK(cudaMalloc((float**)&res_d,nByte));

  initialData(a_h,nElem);
  initialData(b_h,nElem);

  CHECK(cudaMemcpy(a_d,a_h,nByte,cudaMemcpyHostToDevice)); // 从主机内存拷贝到设备内存
  CHECK(cudaMemcpy(b_d,b_h,nByte,cudaMemcpyHostToDevice));

  dim3 block(nElem);
  dim3 grid(nElem/block.x);
  sumArraysCuda<<<grid,block>>>(a_d,b_d,res_d);
  printf("Execution configuration<<<%d,%d>>>\n",block.x,grid.x);
  CHECK(cudaMemcpy(res_gpu,res_d,nByte,cudaMemcpyDeviceToHost)); // 将结果从设备内存拷贝到主机内存！
  cudaFree(a_d);
  cudaFree(b_d);
  cudaFree(res_d);

  sumArraysCpu(a_h, b_h, res_cpu, nElem);
  resultCheck(res_cpu, res_gpu, nElem);
  free(a_h);
  free(b_h);
  free(res_gpu);
  free(res_cpu);

  return 0;
}

