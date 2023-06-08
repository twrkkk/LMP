#pragma once
#include<fstream>
#include <iostream>
#include "data.h"
class Sequence
{
private:


public:
	std::fstream file;//откуда
	int count;
	stor_str elem;
	bool eof;
	void ReadNext() {
		if (file.read((char*)&elem, sizeof(stor_str)))
			eof = false;
		else
			eof = true;
	}
	;
	void StartRead(std::string filename)
	{
		if (file.is_open())
			file.close();
		file.open(filename, std::ios::in | std::ios::binary);
		ReadNext();
	};
	void StartWrite(std::string filename)
	{
		if (file.is_open())
			file.close();
		file.open(filename, std::ios::out | std::ios::binary);
	};
	void Close()
	{
		if (file.is_open())
			file.close();
	};
	void Copy(Sequence& x) {
		elem = x.elem;
		file.write((char*)&elem, sizeof(stor_str));
		x.ReadNext();

	};
	void CopyRun(Sequence& x, size_t c)//c - сколько осталось скопировать, поскольку мы можем ориентироваться только на количество/конец файла
	{
		while (c && !x.eof)
		{
			Copy(x);
			c -= 1;
		}
	}

	/*void Distribute(Sequence& f0, std::string filename, Sequence& f1, Sequence& f2);
	void Merge(Sequence& f0, std::string filename, Sequence& f1, Sequence& f2);
	void Sorting(std::string filename, size_t n);*/
};