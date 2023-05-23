#include <Windows.h>
#include <algorithm>
#include <iostream>
#include <thread>

const size_t N = 9;
const size_t NTHREAD = 4;

long volatile sorted = 1;

void sorted_task(int* a, int beg, int end)
{
	long flag = 1;
	if (a[end] < a[end - 1])
		flag = 0;

	if (flag)
	{
		int i = beg;
		while (i < end && a[i + 1] >= a[i])
			++i;
		if (i != end)
			flag = 0;
	}

	while (_InterlockedAnd(&sorted, flag) <= 0)
		Sleep(0);
}

bool is_sorted_parallel(int* a)
{
	std::thread TH[NTHREAD];
	size_t n = N / NTHREAD;

	for (int i = 0; i < NTHREAD - 1; i++)
	{
		TH[i] = std::thread(sorted_task, a, i * n, (i + 1) * n);
	}

	sorted_task(a, n * (NTHREAD - 1), N - 1);

	for (int i = 0; i < NTHREAD - 1; i++)
		TH[i].join();

	return sorted;
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

int main()
{
	int* a = new int[N];
	srand(GetTickCount());

	init_array(a);
	std::sort(a, a + N);
	print_array(a, N);

	std::cout << is_sorted_parallel(a) << '\n';
}