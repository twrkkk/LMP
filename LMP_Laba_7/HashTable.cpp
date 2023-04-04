#include "HashTable.h"
#include "AirTicket.h"

HashTable::HashTable(std::ifstream& file, size_t MaxSize)
{
	maxSize = MaxSize;
	hashTable.resize(maxSize);

	while (!file.eof())
	{
		TInfo ticket(file);
		size_t index = hash(ticket.get_key());
		if (std::find(hashTable[index].begin(), hashTable[index].end(), ticket) == hashTable[index].end())
		{
			hashTable[index].push_back(ticket);
		}
	}

	file.close();
}

size_t HashTable::hash(std::string key)
{
	size_t res = 0, len = key.length();
	for (int i = 0; i < len; ++i)
		res += key[i];
	return res % maxSize;
}

Iterator HashTable::find(std::string key)
{
	size_t index = hash(key);
	return std::find_if(hashTable[index].begin(), hashTable[index].end(), [&key](TInfo elem)->bool {return elem.get_key() == key; });

}

bool HashTable::find(std::string key, TInfo& pair)
{
	bool result = false;
	size_t index = hash(key);
	Iterator it = std::find_if(hashTable[index].begin(), hashTable[index].end(), [&key](TInfo elem)->bool {return elem.get_key() == key; });
	if (it != hashTable[index].end()) {
		pair = *it;
		result = true;
	}
	return result;
}

bool HashTable::remove(std::string key)
{
	bool result = false;
	Iterator it = find(key);
	size_t index = hash(key);
	if (it != hashTable[index].end()) {
		result = true;
		hashTable[index].remove(*it);
	}
	return result;
}

bool HashTable::add(TInfo info)
{
	bool res = false;
	size_t index = hash(info.get_key());
	if (std::find_if(hashTable[index].begin(), hashTable[index].end(), [&info](TInfo elem)->bool {return elem == info; }) == hashTable[index].end())
	{
		hashTable[index].push_back(info);
		res = true;
	}

	return res;
}

void HashTable::print()
{
	for (int i = 0; i < maxSize; i++)
	{
		for (auto info : hashTable[i])
		{
			std::cout << i << ": ";
			info.print();
		}
	}
}

