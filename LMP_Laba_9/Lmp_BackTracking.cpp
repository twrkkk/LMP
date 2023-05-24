﻿#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::string;

void print(const vector<int>& v, int r)
{
	for (size_t i = 0; i < r; i++)
		cout << v[i] << ' ';
	cout << '\n';
}

bool isProgression(int x, int y, int z)
{
	return z - y == y - x;
}

void copy(const vector<int>& source, vector<int>& dest, int count)
{
	for (int i = 0; i < count; i++)
	{
		dest[i] = source[i];
	}
}

vector<int> v{ 2,4,6,14,9, 22, 30 }; //2,4,6,14,9
vector<int> arifm(v.size());
vector<int> max_prog(v.size());
int len_max = 0;

void Try(int i, int k, int n) // i - start; k - prog size; n - array size
{
	if (k > len_max)
	{
		copy(arifm, max_prog, k);
		len_max = k;
	}

	for (int j = i + 1; j < n; j++)
	{
		if (k < 2)
		{
			arifm[k++] = v[j];
		}
		else if (k < n)
		{
			if (isProgression(arifm[k - 2], arifm[k - 1], v[j]))
			{
				arifm[k++] = v[j];
			}

			Try(j, k, n);
			--k;
		}
	}
}


int main()
{
	for (int i = 0; i < v.size() - len_max; i++)
	{
		int a = max_prog.max_size();
		arifm[0] = v[i];
		Try(i, 1, v.size());
	}

	print(max_prog, len_max);
}
