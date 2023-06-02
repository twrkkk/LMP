#include <iostream>
#include <fstream>
using std::ofstream;
#include<list>
using std::list;
#include <string>
using std::string;
struct domino_chip
{
	size_t half1;
	size_t half2;
	domino_chip(int x1, int x2=0)  
	{
		half1 = x1;
		half2 = x2;
	};
};

const size_t N = 15;//количество костей
list<size_t> domino_line;//хранит последовательное расположение костяшек
list<size_t> domino_line_result;
size_t count_chip;
size_t count_chip_result;
ofstream file("output.txt");
domino_chip chips[N]{ {0,0}/*, {0,1},{0,2},{0,3},{0,4}*//*,{0,5}*//*,{0,6}, { 1,1 }, { 1,2 }, { 1,3 }, { 1,4 }, { 1,5 }, { 1,6 }, { 2,2 }*/, { 2,3 },{2,4}, {2,5},{2,6},{3,3},{3,4},{3,5},{3,6}, { 4,4 }, { 4,5 }, { 4,6 }, { 5,5 }, { 5,6 }, { 6,6 } };
bool used_chips[N];
bool max_RESULLT(false);
bool include_chip(list<size_t>& line, domino_chip& chip, bool reverse);
void exclude_chip(list<size_t>& line);//удаляет последнюю добавленную фишку
string print_line(list<size_t>& line);
void Try(size_t i)//i-тую кость(по счёту) пытаемся присоедить
{
  if(!max_RESULLT)
	{
	if (i == N)//пытаемся присоединить несуществующую кость
		{
		if (count_chip > count_chip_result || count_chip_result == 0)
		{			
			count_chip_result = count_chip;
			domino_line_result = domino_line;
			print_line(domino_line_result);
			if (count_chip_result == N) max_RESULLT = true;
		}
		}
	else
	{
		bool used_once{ false };
		for (size_t j = 0; j < N; ++j)
		{
			if (!used_chips[j])
				for (size_t reverse = 0; reverse < 2; ++reverse)//пробуем обе стороны фишки
				{
					if (chips[j].half1 == chips[j].half2) reverse = 1;//на случай если фишка 00, 11, 22, и тд т.е. с одинаковыми сторонами
					if (include_chip(domino_line, chips[j], reverse))// если фишку удалось присоединить
					{
						used_once = true;
						used_chips[j] = true;
						count_chip += 1;
						Try(i + 1);
						used_chips[j] = false;
						count_chip -= 1;
						exclude_chip(domino_line);
					}
				}
		}
		if (!used_once)Try(i + 1);
	}
	}
}

bool include_chip(list<size_t>& line, domino_chip& chip, bool reverse)
{
	bool result = false;
	size_t left = chip.half1;
	size_t right = chip.half2;
	if (reverse) std::swap(left, right);
	if (line.empty())
	{
		result = true;
		line.push_back(left); line.push_back(right);
	}
	else
	{
		size_t last = line.back();
		if (last == left)
		{
			result = true;
			line.push_back(left); line.push_back(right);
		}
	}
	return result;
}

void exclude_chip(list<size_t>& line)
{
	list<size_t>::iterator left = line.end();
	list<size_t>::iterator right = left;
	left--; left--;
	line.erase(left, right);
}

string print_line(list<size_t>& line)
{
	string result ="";
	size_t pairs = line.size()/2;
	list<size_t>::iterator begin = line.begin();
	for (size_t i = 0; i < pairs; ++i)
	{
		size_t left = *begin;
		begin++;
		size_t right = *begin;
		begin++;
		result += "[" +std::to_string(left)+ std::to_string(right) + "]";
	}
	return result;
}


int main()
{
	Try(0);
	std::cout << "count: "<<count_chip_result<<'\n'<< print_line(domino_line_result);
	std::cin.get();
	return 0;
}
