#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define N 10 // side of matrix containing data



__global__ void sum_value(float * da,  float *result)
{
	 int tid = blockDim.x * blockIdx.x + threadIdx.x;
	 
	 if(tid < N){
		 float sum=0.0;
	       	 for(int i=0;i < N ; i++)
		 {
		        //Each thread does sum of its row, thread 0 => 0 to N-1 , thread 1 => n to 2N-1 elements;	  	
			sum= sum+da[N*tid+i];
			//printf("thread= %d, da[%d]= %f\n",tid,N*tid+i,da[N*tid+i]);
		 } 
		 //printf("thread= %d, sum= %f\n",tid,sum);
		 syncthreads();
		 result[tid]= sum;
	 }
}
__global__ void min_key(float *da, float * result)
{
	int tid= blockDim.x*blockIdx.x+threadIdx.x;
	if(tid < N)
	{	
		float minkey=da[N*tid]; // initially first elememt as min
		for(int i=0; i< N; i++){
			if(minkey > da[N*tid+i])
				minkey = da[N*tid+i];	
		}
		syncthreads();
		result[tid] = minkey;
	}
}

__global__ void max_key(float *da, float * result)
{
	int tid= blockDim.x*blockIdx.x+threadIdx.x;
	if(tid < N)
	{	
		float maxkey=da[N*tid]; // initially first element as max
		for(int i=0; i< N; i++){
			if(maxkey < da[N*tid+i])
				maxkey= da[N*tid+i];	
		}
		syncthreads();
		result[tid] = maxkey;
	}
}

	
void init(float * array, int size);
void check_result(float * result);
void check_minresult(float * result);
void check_maxresult(float * result);
	 

int main(int argc, char * argv[])

{
	float * A, *dA,  *dresult, *dminresult, *dmaxresult,*hresult, *hminresult, *hmaxresult;

	A = (float *)malloc(sizeof(float)*N*N);
	hresult = (float *)malloc(sizeof(float)*N);
	hminresult = (float *)malloc(sizeof(float)*N);
	hmaxresult = (float *)malloc(sizeof(float)*N);
	
	init(A,N*N);

	cudaMalloc((void **)&dA,sizeof(float)*N*N);	 
	cudaMalloc((void **)&dresult, sizeof(float)*N);
	cudaMalloc ((void **)&dminresult, sizeof(float)*N);
	cudaMalloc((void **)&dmaxresult, sizeof(float)*N);

	 //copy memory from unpadded array A of 10 cross 10 dimensions
	 cudaMemcpy(dA,A,sizeof(float)*N*N,cudaMemcpyHostToDevice);
         // launching kernel, total number of threads = total number of keys / rows => number of blocks* number of threads	
	 sum_value<<< 1,N >>>(dA,dresult);
	 min_key <<< 1, N >>>(dA,dminresult);
	 max_key<<< 1, N>>>(dA, dmaxresult);
	 
         cudaMemcpy(hresult,dresult,sizeof(float)*N,cudaMemcpyDeviceToHost);
         cudaMemcpy(hminresult,dminresult,sizeof(float)*N,cudaMemcpyDeviceToHost);
	 cudaMemcpy(hmaxresult,dmaxresult,sizeof(float)*N,cudaMemcpyDeviceToHost);
  
	 check_result(hresult);
	 check_minresult(hminresult);
	 check_maxresult(hmaxresult);
 	 free(A);
	 cudaFree(dA);
}
	 
void check_result(float * result){
	for(int i=0;i<N; i++){
		printf(" Key %d -> Sum= %f\n", i, result[i]);
	}	
}

void check_minresult(float * result){
	for(int i=0;i<N; i++){
		printf(" Key %d -> MinKey= %f\n", i, result[i]);
	}	
}

void check_maxresult(float * result){
	for(int i=0;i<N; i++){
		printf(" Key %d -> MaxKey= %f\n", i, result[i]);
	}	
}

void init(float * array, int size)
{
	for (int i = 0; i < N*N; i++)

	 {
	 	array[i] = (float)i;
		//printf("Init=> %d = %f\n",i,array[i]);
	 }
}

