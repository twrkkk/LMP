#include <iostream>
#include <Windows.h>
#include <process.h>
#include <algorithm>

const size_t N = 12;
const size_t NTHREAD = 4;

using INFORM = struct elem
{
	int* a;
	size_t beg, end;
	bool sorted;
};

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

unsigned __stdcall sorted_task(void* a)
{
	INFORM* inform = (INFORM*)a;
	bool flag = true;

	if (inform->a[inform->end] < inform->a[inform->end - 1])
	{
		inform->sorted = false;
		flag = false;
	}

	if (flag)
	{
		int i = inform->beg;
		while (i < inform->end && inform->a[i + 1] >= inform->a[i])
			++i;
		if (i != inform->end)
			flag = false;

		inform->sorted = flag;
	}

	_endthreadex(0);
	return 0;
}

bool is_sorted_parallel(int* a)
{
	HANDLE TH[NTHREAD];
	INFORM inform[NTHREAD];
	size_t n = N / NTHREAD;

	for (int i = 0; i < NTHREAD - 1; i++)
	{
		inform[i].a = a;
		inform[i].beg = i * n;
		inform[i].end = (i + 1) * n;

		TH[i] = (HANDLE)_beginthreadex(nullptr, 0, &sorted_task, &inform[i], 0, nullptr);
	}

	bool isSorted = true;
	isSorted *= is_sorted_non_parallel(a + n * (NTHREAD - 1), n);
	WaitForMultipleObjects(NTHREAD - 1, TH, true, INFINITE);

	for (size_t i = 0; i < NTHREAD - 1 && isSorted; i++)
		isSorted *= inform[i].sorted;

	for (size_t i = 0; i < NTHREAD - 1; i++)
		CloseHandle(TH[i]);

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
	std::cout << is_sorted_non_parallel(a, N) << '\n' << is_sorted_parallel(a) << '\n';
}
