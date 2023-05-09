#include <iostream>
#include <Windows.h>
#include <process.h>

const size_t N = 9;
const size_t NTHREAD = 3;

using INFORM = struct elem
{
	int* a;
	size_t beg, end;
	bool sorted;
	int first_elem;
	int last_elem;
};

bool is_sorted_non_parallel(int* a)
{
	int i = 0;
	bool flag = true;
	while (i<N - 1 && a[i + 1] > a[i])
		++i;
	if (i != N - 1)
		flag = false;

	return flag;
}

unsigned __stdcall sorted_task(void* a)
{
	INFORM* inform = (INFORM*)a;

	int i = inform->beg;
	bool flag = true;
	while (i<inform->end && inform->a[i + 1] > inform->a[i])
		++i;
	if (i != inform->end)
		flag = false;

	inform->sorted = flag;
    inform->first_elem = inform->a[inform->beg];
	inform->last_elem = inform->a[inform->end];

	_endthreadex(0);
	return 0;
}

bool is_sorted_parallel(int* a)
{
    HANDLE TH[NTHREAD];
    INFORM inform[NTHREAD];
    size_t n = N / NTHREAD;

    for (int i = 0; i < NTHREAD; i++)
    {
        inform[i].a = a;
        inform[i].beg = i * n;
        if (i == NTHREAD - 1)
            inform[i].end = N - 1;
        else
            inform[i].end = (i + 1) * n - 1;
        TH[i] = (HANDLE)_beginthreadex(nullptr, 0, &sorted_task, &inform[i], 0, nullptr);
    }
    WaitForMultipleObjects(NTHREAD, TH, true, INFINITE);


    bool isSorted = inform[0].sorted;
    for (size_t i = 1; i < NTHREAD && isSorted; i++)
    {
        isSorted *= inform[i].sorted;
        isSorted *= inform[i - 1].last_elem < inform[i].first_elem;
    }

    for (size_t i = 0; i < NTHREAD; i++)
        CloseHandle(TH[i]);

    return isSorted;
}

int main()
{
	int* a = new int[N];
	for (int i = 0; i < N; i++)
		std::cin >> a[i];
	std::cout << is_sorted_non_parallel(a) << '\n' << is_sorted_parallel(a) << '\n';
}
