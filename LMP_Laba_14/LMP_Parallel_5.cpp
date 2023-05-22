﻿#include <iostream>
#include <thread>
#include <Windows.h>
#include <mutex>
#include <algorithm>

const size_t N = 12;
const size_t NTHREAD = 3;
std::mutex mut;

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

void sorted_task(int* a, int beg, int end, volatile bool& sorted)
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

	mut.lock();

	try {
		sorted *= flag;
	}
	catch (std::string e) {
		mut.unlock();
		throw e;
	}

	mut.unlock();
}

bool is_sorted_parallel(int* a)
{
	std::thread TH[NTHREAD];
	bool results[NTHREAD];
	size_t n = N / (NTHREAD + 1);
	bool isSorted = true;

	for (int i = 0; i < NTHREAD; i++)
	{
		if (i == NTHREAD - 1)
			TH[i] = std::thread(sorted_task, a, i * n, N - 1, std::ref(isSorted));
		else
			TH[i] = std::thread(sorted_task, a, i * n, (i + 1) * n, std::ref(isSorted));
	}

	isSorted *= is_sorted_non_parallel(a + n * NTHREAD, n);

	for (int i = 0; i < NTHREAD; i++)
		TH[i].join();

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
	//std::sort(a, a + N);
	print_array(a, N);

	bool isSorted;
	sorted_task(a, 0, N - 1, isSorted);
	std::cout << isSorted << '\n' << is_sorted_parallel(a) << '\n';
}

