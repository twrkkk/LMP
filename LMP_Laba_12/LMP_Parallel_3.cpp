﻿#include <Windows.h>
#include <algorithm>
#include <iostream>
#include <future>

const size_t N = 12;
const size_t NTHREAD = 3;

bool is_sorted_non_parallel(int* a, int count)
{
	int i = 0;
	bool flag = true;
	while (i < count && a[i + 1] >= a[i])
		++i;
	if (i != count - 1)
		flag = false;

	return flag;
}

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

bool is_sorted_parallel(int* a)
{
	std::future<bool> TH[NTHREAD];
	size_t n = N / (NTHREAD + 1);

	for (int i = 0; i < NTHREAD; i++)
	{
		if (i == NTHREAD - 1)
			TH[i] = std::async(sorted_task, a, i * n, N - 1);
		else
			TH[i] = std::async(sorted_task, a, i * n, (i + 1) * n);
	}

	bool isSorted = true;
	isSorted *= is_sorted_non_parallel(a + n * NTHREAD, n);
	for (size_t i = 0; i < NTHREAD && isSorted; i++)
		isSorted *= TH[i].get();

	return isSorted;
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

	bool isSorted = sorted_task(a, 0, N - 1);
	std::cout << isSorted << '\n' << is_sorted_parallel(a) << '\n';
}