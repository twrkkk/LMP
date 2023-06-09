#include <fstream>
#include <iostream>
#include <Windows.h>
#include "data.h"
#include "Sequence.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

const int number_of_files = 3;
const int start_seria_size = 2;

void Create_File(std::string filename, int cnt)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);
	srand(GetTickCount64());
	stor_str tmp;
	//std::vector<int>a = { 41, 37, 0, 53, 43, 43, 21, 24, 20, 26 };
	for (int i = 0; i < cnt; ++i)
	{
		tmp.key = rand() % 100;
		//tmp.key = a[i];
		tmp.data = rand() % 100;
		file.write((char*)&tmp, sizeof(stor_str));
	}
	file.close();
}

bool CheckFile(std::string filename)
{
	std::ifstream file(filename, std::ios::in | std::ios::binary);
	stor_str x, y;
	bool check(true);
	bool eof = false;
	while (!file.eof() && check)
	{
		x = y;
		eof = (bool)file.read((char*)&y, sizeof(stor_str));
		check = x.key <= y.key;
	}
	file.close();
	return check;
}

void Print(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary);

	if (!file) {
		std::cout << "Failed to open the file." << std::endl;
		return;
	}

	stor_str number;
	while (file.read((char*)&number, sizeof(stor_str)))
	{
		std::cout << number.key << ' ';
	}
	std::cout << std::endl;
	file.close();
}

void Print_Files()
{
	std::cout << "----------------------------------- \n";
	for (int i = 0; i < number_of_files; ++i)
	{
		std::string name = "f" + std::to_string(i) + ".txt";
		std::cout << name << ' ';
		Print(name.c_str());
	}
}

void Inner_Sorting(std::vector <stor_str>& arr, std::function <bool(stor_str, stor_str)> cmp = [](stor_str x, stor_str y)->bool {return x.key < y.key; })
{
	std::sort(arr.begin(), arr.end(), cmp);
}

void Distribute(Sequence& f0, std::string filename, Sequence f[number_of_files], std::map<int, int> Q, bool start = false)
{
	f0.StartRead(filename);
	for (int i = 0; i < number_of_files; ++i)
	{
		std::string name = "f" + std::to_string(i) + ".txt";
		f[i].StartWrite(name);
	}

	int ord = 0;

	if (start)
	{
		while (!f0.eof)
		{
			size_t i(0);
			std::vector <stor_str> arr;
			while (!f0.eof && i < f0.count)
			{
				if (!f0.eof)
				{
					stor_str tmp = f0.elem;
					arr.push_back(tmp);
					i += 1;
				}
				f0.ReadNext();
			};
			Inner_Sorting(arr);
			size_t c = arr.size();
			i = 0;
			while (i < c)
			{
				f[Q[ord]].elem = arr[i];
				f[Q[ord]].file.write((char*)&f[Q[ord]].elem, sizeof(stor_str));
				i += 1;
			}
			ord = (ord + 1) % number_of_files;
		}
	}
	else
	{
		while (!f0.eof)
		{
			f[Q[ord]].CopyRun(f0, f0.count);
			ord = (ord + 1) % number_of_files;
		}
	}
	f0.Close();
	for (int i = 0; i < number_of_files; ++i)
		f[i].Close();
}


void Merge(Sequence& f0, std::string filename, Sequence f[number_of_files], std::map<int, int> Q, std::function <bool(stor_str, stor_str)> cmp = [](stor_str x, stor_str y)->bool {return x.key < y.key; })
{
	f0.StartWrite(filename);
	for (int i = 0; i < number_of_files; ++i)
	{
		std::string name = "f" + std::to_string(i) + ".txt";
		f[i].StartRead(name);
	}

	size_t readed[number_of_files];
	int without_eof(number_of_files);
	int without_eor(number_of_files);
	int MinElem;
	for (int i = 0; i < without_eof;)
	{
		if (f[Q[i]].eof)
		{
			std::swap(Q[i], Q[without_eof - 1]);
			without_eof--;
		}
		else
			i++;
	}
	while (without_eof > 1)
	{
		without_eor = without_eof;
		for (int i = 0; i < without_eof; ++i)
		{
			readed[i] = 0;
		}

		while (without_eor > 1)
		{
			MinElem = 0;
			for (int i = 0; i < without_eor; ++i)
			{
				if (f[Q[MinElem]].elem.key > f[Q[i]].elem.key)
				{
					MinElem = i;
				}
			}
			f0.Copy(f[Q[MinElem]]);
			readed[Q[MinElem]]++;
			if (readed[Q[MinElem]] == f0.count || f[Q[MinElem]].eof)
			{
				std::swap(Q[MinElem], Q[without_eor - 1]);
				--without_eor;
			}
		}
		f0.CopyRun(f[Q[0]], f0.count - readed[Q[0]]);
		for (int i = 0; i < without_eof;)
		{
			if (f[Q[i]].eof)
			{
				std::swap(Q[i], Q[without_eof - 1]);
				without_eof--;
			}
			else
				i++;
		}
	}
	f0.CopyRun(f[Q[0]], f0.count - readed[Q[0]]);

	f0.Close();
	for (int i = 0; i < number_of_files; ++i)
	{
		f[i].Close();
	}
}

void Sorting(std::string filename, size_t n)
{
	Sequence f0, f[number_of_files];
	std::map<int, int> Q;
	for (int i = 0; i < number_of_files; ++i)
	{
		Q[i] = i;
	}
	f0.count = start_seria_size;
	Distribute(f0, filename, f, Q, true);
	Print_Files();
	Merge(f0, filename, f, Q);
	Print("data.txt");
	f0.count *= number_of_files;
	for (int i = 0; i < number_of_files; ++i)
		f[i].count *= number_of_files;
	while (f0.count < n)
	{
		Distribute(f0, filename, f, Q);
		Print_Files();
		Merge(f0, filename, f, Q);
		Print("data.txt");
		f0.count *= number_of_files;
		for (int i = 0; i < number_of_files; ++i)
			f[i].count *= number_of_files;
	}
	remove("f1.txt");
	for (int i = 0; i < number_of_files; ++i)
	{
		std::string name = "f" + std::to_string(i) + ".txt";
		remove(name.c_str());
	}
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	size_t n = 25;
	Create_File("data.txt", n);
	Print("data.txt");
	Sorting("data.txt", n);
	Print("data.txt");
	if (CheckFile("data.txt"))
		std::cout << "File is ordered";
	else
		std::cout << "Not ordered";

	std::cin.get();
	return 0;
}
