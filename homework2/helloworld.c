//1、运行并测试 课件中的OpenMP helloworld程序，设置不同线程个数并记录运行结果。
//
//2、完成并行矩阵乘法
//
//windows环境或者linux（建议优先使用）均可以。
#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv)
{
	int nthreads, thread_id;
	printf("i am the main thread.\n");
	omp_set_num_threads(4);
	#pragma omp parallel private(nthreads,thread_id)
		{
			
			//omp_get_max_threads();
			nthreads = omp_get_num_threads();
			thread_id = omp_get_thread_num();
			printf("hello.i am thread %d out of a team of %d\n", thread_id, nthreads);
		}
	printf("here i am,back to the main thread.\n");
	return 0;
}