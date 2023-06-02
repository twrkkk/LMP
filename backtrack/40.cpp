#include <iostream>
#include <string>
#include <utility>
#include<Windows.h>
const size_t N = 10;
const size_t V = 100;

struct things
{
	size_t Weight;
	size_t Price;
	things(std::pair<size_t, size_t> e=std::make_pair<size_t,size_t>(0,0)) :Weight(e.first), Price(e.second) {};
	friend std::ostream& operator<< (std::ostream& out, const things& thing)
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
bool bestThingsUsed[N]{ 0 };
size_t curWeight;
size_t curPrice;
size_t bestPrice;

bool RESULT{ false };
void Try(bool prevTry)
{
	if (!prevTry)
	{
		if (curPrice > bestPrice)
		{
			bestPrice = curPrice;
			for (size_t k = 0; k < N; ++k)
				bestThingsUsed[k] = ThingsUsed[k];
			for (size_t k = 0; k < N; ++k)
				if (bestThingsUsed[k])
					std::cout << given[k]<<' ';
			std::cout << '(' << curWeight << ',' << curPrice << ')';
			std::cout << '\n';
			RESULT= true;
		}
    }
	else
	{
		for (size_t j = 0; j < N; ++j)
		{
			if (!ThingsUsed[j] && curWeight + given[j].Weight <= V)
			{
				curWeight += given[j].Weight;
				curPrice += given[j].Price;
				ThingsUsed[j] = true;
				Try(true);
				curWeight -= given[j].Weight;
				curPrice -= given[j].Price;
				ThingsUsed[j] = false;
			}
			else
				if (curWeight + given[j].Weight > V||j==9) Try(false);
		}
	}
}

int main()
{
	srand(GetTickCount64());
	std::cout << "given\n";
	for (size_t i = 0; i < N; ++i)
	{
		given[i].Weight = rand()%50;
		given[i].Price = rand()%50;
		std::cout << given[i] << ' ';
	}
	std::cout << '\n';
	Try(-1);
	std::cout << "result\n";
	if (RESULT)
		for (size_t k = 0; k < N; ++k)
		{if (bestThingsUsed[k])std::cout << given[k] << ' ';}
	else std::cout << "No result";
	std::cin.get();
	return 0;
}