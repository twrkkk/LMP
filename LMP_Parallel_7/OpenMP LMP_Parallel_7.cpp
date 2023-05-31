#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <omp.h>

const size_t N = 12;
const size_t NTHREAD = 4;

bool sorted_task(int* a, int beg, int end)
{
	bool flag = true;
	if (a[end] < a[end - 1])
		flag = false;

	if (flag)
	{
		int i = beg;
		while (i < end && a[i + 1] >= a[i])
			++i;
		if (i != end)
			flag = false;
	}

	return flag;
}

void f()
{
	std::cout << "Thread " << omp_get_thread_num() << '\n';
}

void init_array(int* arr, bool random = true)
{
	if (random)
	{
		for (size_t i = 0; i < N; i++)
			arr[i] = rand() % 100;
	}
	else
	{
		for (size_t i = 0; i < N; i++)
			std::cin >> arr[i];
	}
}

void print_array(int* a, int count)
{
	for (size_t i = 0; i < count; i++)
		std::cout << a[i] << ' ';
	std::cout << '\n';
}

bool parallel(int* arr, int size)
{
	bool global_sorted = true;
	//omp_lock_t lock;
	//omp_init_lock(&lock);
	omp_set_num_threads(NTHREAD);

#pragma omp parallel shared(arr, cancel_flag)
	{
		bool local_sorted = true;
#pragma omp for schedule(static, N / NTHREAD)
		for (int i = 0; i < size - 1; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				local_sorted = false;
				//		#pragma omp cancellation point for
				//#pragma omp cancel for
			}
		}

		//omp_set_lock(&lock);
#pragma omp atomic
		global_sorted *= local_sorted;
		//omp_unset_lock(&lock);
	}

	//omp_destroy_lock(&lock);
	return global_sorted;
}



int main()
{
	int* a = new int[N];
	srand(GetTickCount());

	init_array(a);
	std::sort(a, a + N);
	print_array(a, N);

	bool isSorted = sorted_task(a, 0, N - 1);
	std::cout << isSorted << '\n' << parallel(a, N) << '\n';
	return 0;
}