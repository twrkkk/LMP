#pragma once
#include <iostream>
#include<fstream>
#include <string>
#include <algorithm>
#include <list>
#include <vector>
#include <Windows.h>
#include "AirTicket.h"

using TInfo = Ticket;
using THashTable = std::vector<std::list<TInfo>>;
using Iterator = std::list<TInfo>::iterator;

class HashTable
{
private:
	THashTable hashTable;
	size_t maxSize;
public:
	HashTable(size_t maxSize) : maxSize(maxSize)
	{
		hashTable.resize(maxSize);
	};
	HashTable(std::ifstream& file, size_t MaxSize);
	size_t hash(std::string key);
	Iterator find(std::string key);
	bool find(std::string key, TInfo& pair);
	bool remove(std::string key);
	bool add(TInfo pair);
	void print();
};

