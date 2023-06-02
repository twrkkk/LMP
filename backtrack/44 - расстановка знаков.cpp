#include <Windows.h>
#include <iostream>
using std::cout;
#include<vector>;
using std::vector;
#include <string>
using std::string;
const size_t N = 15;
const int m = 122;
size_t digits[N];
int operations[N];//операции слева цифрами: -1, 0, 1

string get_result()
{
	string res("");
	for (size_t i = 0; i < N; ++i)
	{
		switch (operations[i])
		{
		case -1:
			res += '-';
			break;
		case 1:
			res += '+';
			break;
		}
			res +='0'+ digits[i];
	}
	return res;
}


bool Try(size_t i)//i--позиция операции
{

	bool result = false;
	if (i == N)//операции дальше выбирать нельзя
	{
		vector<int> numbers;

		//превращение операций и набора чисел в число
		size_t j = 0;
		while (j < N)
		{
			switch (operations[j])
			{
			case -1:
				numbers.push_back(-1 * digits[j]);
				break;
			case 1:
				numbers.push_back(digits[j]);
				break;
			case 0:
				if (j != 0)
				{
					numbers.back() = numbers.back() * 10 + (numbers.back() < 0 ? -1 : 1) * digits[j];
				}
				else
					numbers.push_back(digits[j]);
				break;
			}
			j += 1;
		}
		int res = 0;
		for (auto x : numbers)
			res += x;
		std::cout << get_result() << '\n';
		std::cout << '(' << res<<')';
		std::cout << '\n';
		result = res == m;
	}
	else
	{
		int j = -1;
		while (j <= 1&&!result)
		{
			operations[i] = j;
			result=Try(i + 1);
			if(!result) j+=1;//избыточно немного
		}
	}

	return result;

}


int main()
{
	srand(GetTickCount64());
	for (size_t i = 0; i < N; ++i)
		//digits[i] = i+1;
		digits[i] = rand()%10;
	if (Try(0))
	{
		std::cout << get_result() << '\n';
	}
	else
		std::cout<<"Impossible";


 std::cin.get();
	return 0;
}
