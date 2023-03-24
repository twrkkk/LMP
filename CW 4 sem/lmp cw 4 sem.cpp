#include <iostream>
#include <set>
#include <map>
#include <list>
#include <sstream>
#include <fstream>
#include <functional>
#include <algorithm>


/*
	Дан файл, содержащий несколько строк, необходимо найти номер строки, которая содержит
	наибольшее кол-во слов с повторяющимися буквами
*/

int countWordWithRepetitonSymb(std::string line)
{
	auto to_lower = [](std::string str)
	{
		std::string result;
		int size = str.size();
		for (int i = 0; i < size; i++)
			result += tolower(str[i]);
		return result;
	};

	auto is_repeated_symb = [](std::string word)
	{
		std::map<char, int> dict;
		bool flag = false;
		int i = 0;
		int size = word.size();
		while (!flag && i < size)
		{
			if (dict.find(word[i]) == dict.end())
				dict.insert(std::pair<char, int>(word[i], 1));
			else
				flag = true;
			++i;
		}

		return flag;
	};

	std::stringstream ss(to_lower(line));
	std::string word;
	int count = 0;
	while (ss >> word)
	{
		if (is_repeated_symb(word))
			++count;
	}

	return count;
}

int task(std::ifstream& file)
{
	std::string line;
	int maxCount = -1e6;
	int lineNumber = 0;
	int result = 0;
	while (std::getline(file, line))
	{
		int count = countWordWithRepetitonSymb(line);
		if (count > maxCount)
		{
			maxCount = count;
			result = lineNumber;
		}
		lineNumber++;
	}

	return result;
}

/*
	Распечатать все слова файла, рядом со словами перечислить номера строк, в которых встречается это слово.
*/

using Dictionary = std::map<std::string, std::set<int>>;

void print(Dictionary& dict)
{
	for (auto word : dict)
	{
		std::cout << word.first << ' ';
		for (auto lines : word.second)
		{
			std::cout << lines << ' ';
		}
		std::cout << '\n';
	}
}

void add_to_dict(std::string word, int lineNumber, Dictionary& dict)
{
	if (dict.find(word) == dict.end())
	{
		std::set<int> set;
		set.insert(lineNumber);
		dict.emplace(word, set);
	}
	else
	{
		dict[word].insert(lineNumber);
	}
}

void task_2(std::ifstream& file)
{
	Dictionary dict;
	std::string line;
	int i = 0;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string word;
		while (ss >> word)
		{
			add_to_dict(word, i, dict);
		}
		++i;
	}

	print(dict);
}

/*
	найти слова, которые встречается один раз в тексте и обладают заданным свойством
*/

using set = std::set<std::string>;
using dict = std::map<std::string, int>;
set task_1(std::ifstream& file, std::string begin, std::function<bool(std::string, std::string)> lambda)
{
	auto to_lower = [](std::string word)
	{
		int size = word.size();
		std::string result;
		for (int i = 0; i < size; i++)
			result += tolower(word[i]);

		return result;
	};

	set set;
	dict map;
	std::string line;
	//create map
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string word;
		while (ss >> word)
		{
			word = to_lower(word);
			if (map.find(word) == map.end())
				map.emplace(word, 1);
			else
				map[word]++;
		}
	}
	//analize words frequency
	for (auto pair : map)
		if (pair.second == 1 && lambda(pair.first, begin))
			set.emplace(pair.first);

	return set;
}

int find_extremum(int* arr, int size, std::function<bool(int, int)> lambda)
{
	int extr = arr[0];
	int pos = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (lambda(extr, arr[i]))
		{
			extr = arr[i];
			pos = i;
		}
	}

	return pos;
}


int main()
{
	std::ifstream file("text.txt");

	//std::cout << task(file);
	//task_2(file);

	auto lambda = [](std::string word, std::string begin) {
		bool flag = true;
		int size = std::min(word.size(), begin.size());
		int i = 0;
		while (flag && i < size)
		{
			flag = word[i] == begin[i];
			++i;
		}

		return flag && i == size;
	};

	std::set<std::string> set = task_1(file, "st", lambda);
	for (auto e : set)
		std::cout << e << '\n';

}