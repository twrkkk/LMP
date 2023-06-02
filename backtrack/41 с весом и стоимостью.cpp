#include <iostream>
#include <string>
#include <utility>
#include<Windows.h>
const size_t N = 10;
const size_t V = 150;
const size_t S = 90;

struct things
{
	size_t Weight;
	size_t Price;
	things(std::pair<size_t, size_t> e = std::make_pair<size_t, size_t>(0, 0)) :Weight(e.first), Price(e.second) {};
	friend std::ostream& operator<< (std::ostream& out,const things&thing)
	{
		out << '(' << thing.Weight << ", " << thing.Price << ')';
		return out;

	}
};

things given[N]/*{
std::make_pair<size_t,size_t>(7,12),
std::make_pair<size_t,size_t>(12,304),
std::make_pair<size_t,size_t>(101,4),
std::make_pair<size_t,size_t>(73,3),
std::make_pair<size_t,size_t>(56,3),
std::make_pair<size_t,size_t>(56,34),
std::make_pair<size_t,size_t>(20,14),
std::make_pair<size_t,size_t>(11,34),
std::make_pair<size_t,size_t>(450,34),
std::make_pair<size_t,size_t>(100,0)}*/;

bool ThingsUsed[N]{ 0 };
size_t curWeight;
size_t curPrice;
bool Try(int prevTh)
{
	int nextTh = -1;
	bool result = false;
	do
	{
		++nextTh;
		if (!ThingsUsed[nextTh] && curWeight + given[nextTh].Weight <= V)
		{
			curPrice += given[nextTh].Price;
			curWeight += given[nextTh].Weight;
			ThingsUsed[nextTh] = true;
			result = Try(nextTh);
			//попытка не удалась, откат:
			if (!result)
			{
				curPrice -= given[nextTh].Price;
				curWeight -= given[nextTh].Weight;
				ThingsUsed[nextTh] = false;
			}
		}
		else
			if(curPrice>S)
			result = true;

	} while (!result && nextTh != N - 1);//не нашли что-нибудь или не исчерпали все предметы


	return result;
}

int main()
{
	srand(GetTickCount64());
	std::cout << "given\n";
	for (size_t i = 0; i < N; ++i)
	{
		given[i].Weight = rand() % 50;
		given[i].Price = rand() %50;
		std::cout << given[i] << ' ';
	}
	std::cout << '\n';
	std::cout << "result\n";
	if (Try(-1))
	{
		size_t weight(0), price(0);

	for (size_t k = 0; k < N; ++k)
	{
		if (ThingsUsed[k])
		{
			std::cout << given[k]<<' ';
			weight += given[k].Weight;
			price += given[k].Price;
		}
	}
	std::cout << "\nWeight: " << weight << "\nPrice: " << price;
	}
	else std::cout << "No result";

 std::cin.get();
	return 0;
}