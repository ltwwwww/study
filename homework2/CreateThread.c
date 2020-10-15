//自己做实验完成课件中的CreateThread实验，并变化线程数量进行分析（分析 g_Count++值的变化; 请列表记录多次实验结果）。
#include <windows.h>
#include <stdio.h>
const unsigned int THREAD_NUM = 50; unsigned int g_Count = 0;
DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
	//printf("im main thread, pid = %d\n", GetCurrentThreadId());
	HANDLE *hThread = (HANDLE*)malloc(THREAD_NUM*sizeof(HANDLE));
	//DWORD* threadId = (DWORD*)malloc(THREAD_NUM * sizeof(DWORD));
	for (int i = 0; i < 10; i++) 
	{
		g_Count = 0;
		for (int i = 0; i < THREAD_NUM; i++)
		{
			hThread[i] = CreateThread(NULL, 0, ThreadFunc, &i, 0, NULL);
		}
		WaitForMultipleObjects(THREAD_NUM, hThread, TRUE, INFINITE);
		printf("THREAD_NUM = %d \t g_Count = %d\n", THREAD_NUM, g_Count);
	}
	return 0;
}

DWORD WINAPI ThreadFunc(LPVOID p)
{
	//int n = *(int*)p;
	//Sleep(500*n);
	Sleep(50);
	g_Count++;
	//printf("im child thread , pid = %d\n",GetCurrentThreadId());
	//printf("child thread , pid = %d exit\n\n", GetCurrentThreadId());
	Sleep(50);
	return 0;
}