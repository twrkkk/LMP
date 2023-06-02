#include<iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <set>
using std::set;
#include  <utility>
using std::pair;
#include <vector>
using std::vector;
#include <list>
using std::list;
const size_t N = 5;
const size_t K = 12;

set<size_t> Neighbours[N]{ {1,4},{0,2},{1,3},{2,4},{3,0} };//[i] элемент массива это соседи i вершины

bool isNeighbour(size_t x, size_t y)
{
	return Neighbours[x].find(y) != Neighbours[x].end();
}

//set<pair<size_t, size_t>> Neighbours{
//	std::make_pair(0, 1), 
//	std::make_pair(1, 2), 
//	std::make_pair(2, 3), 
//	std::make_pair(3, 4),
//	std::make_pair(0, 4),
//	std::make_pair(0, 5) };

size_t ColouredCountries[N];
int ResK(-1);
int CurK(0);

//bool isNeighbour(size_t x, size_t y)
//{
//	if (x > y) std::swap(x, y);
//	return Neighbours.find(std::make_pair(x, y)) != Neighbours.end();
//}
bool RESULT;
void Try(size_t i)
{
	if (i == N)
	{
		for (size_t j = 0; j < N; ++j)
		{
			std::cout << ColouredCountries[j] << ' ';
		}
		std::cout << '\n';
		RESULT = true;
	}
	else
	{
		int k = 0;
		while (k<=ResK)
		{
			bool found(true);
			size_t i0 = 0;
			while (i0 < i && found)
			{
				if (isNeighbour(i0, i) && ColouredCountries[i0] == k)
					found = false;
				else
					i0 += 1;
			}
			if (found)
			{
				ColouredCountries[i] = k;
				Try(i + 1);
			}
			else k += 1;
		}
		if (!RESULT)
		{
			ResK += 1;
			ColouredCountries[i] = ResK;
			Try(i + 1);
			ResK -= 1;
		}
	}
}
int main()
{

	Try(0);
	/*if (ResK > 0)
	{
		for (auto x : ColouredCountries)
			std::cout << x << ' ';
		std::cout << '\n';
		std::cout << ResK;
	}
	else
		std::cout << "Impossible";*/
 
 std::cin.get();
	return 0;
}
