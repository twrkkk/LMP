#include <iostream>
#include <map>

using std::cin;
using std::cout;
using std::string;

std::multimap<char, int> freq_dict(string word)
{
	std::multimap<char, int> result;
	int size = word.size();
	std::multimap<char, int>::iterator it;
	for (int i = 0; i < size; i++)
	{
		it = result.find(word[i]);
		if (it == result.end())
			result.insert(std::pair<char, int>(word[i], 1));
		else
			++it->second;
	}
	return result;
}

int main()
{
	string word;
	cin >> word;
	std::multimap<char, int> map = freq_dict(word);
	for(auto pair: map)
		cout << pair.first << ' ' << pair.second << '\n';
}
