#include <iostream>
#include <Windows.h>
#include <process.h>


int test_int = 0;
// 1번째 Thread

unsigned int WINAPI Thread_Function_one(void *avg)
{

	while (true) {
		Sleep(100);
		printf("A");
		test_int++;
	}
	

	return test_int;
}


// 2번째 Thread

unsigned int WINAPI Thread_Function_two(void *avg)
{
	while (true) {
		Sleep(100);
		printf("B");
		test_int++;
	}

	return test_int;
}

void main()
{
	HANDLE thread_one;
	HANDLE thread_two;

	DWORD thread_one_id;
	DWORD thread_two_id;

	std::cout << "Main Test Int : " << test_int << std::endl;

	// Thread One 생성

	thread_one = (HANDLE)_beginthreadex(NULL, 0, Thread_Function_one, NULL, 0, (unsigned*)&thread_one_id);

	if (thread_one == 0)
	{
		std::cout << "_beginthreades Error" << std::endl;
	}
	else
	{
		std::cout << "Create Thread One" << std::endl;
	}


	// Thread Two 생성

	thread_two = (HANDLE)_beginthreadex(NULL, 0, Thread_Function_two, NULL, 0, (unsigned*)&thread_two_id);

	if (thread_two == 0)
	{
		std::cout << "_beginthreades Error" << std::endl;
	}
	else
	{
		std::cout << "Create Thread Two" << std::endl;
	}
	while (true) {
		if (test_int == 20) {
			std::cout << "thread_one kill " << test_int << std::endl;

			TerminateThread(thread_one, 0); //<= 강제 종료.
			CloseHandle(thread_one); //<= 핸들 닫기(Handle Count 1 삭제됨)
			thread_one = NULL;
			thread_one_id = 0;
		}

		else if (test_int == 40) {
			std::cout << "thread_two kill " << test_int << std::endl;

			TerminateThread(thread_two, 0); //<= 강제 종료.
			CloseHandle(thread_two); //<= 핸들 닫기(Handle Count 1 삭제됨)
			thread_two = NULL;
			thread_two_id = 0;
		}

		else if (test_int == 60) {
			break;
		}
	}
}