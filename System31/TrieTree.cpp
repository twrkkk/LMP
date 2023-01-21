#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

struct NODE
{
	NODE* ptrs[26];
	bool eow = false;
	NODE()
	{
		for (int i = 0; i < 26; ++i)
			ptrs[i] = nullptr;
	}
};

using TrieTree = NODE*;

void init(TrieTree& root)
{
	root = nullptr;
}

bool empty(TrieTree root)
{
	return root == nullptr;
}

void add(TrieTree& t, const std::string word, size_t i)
{
	if (!t)
	{
		t = new NODE;
	}
	if ((word.length()) - 1 < i)
		t->eow = true;
	else
		add(t->ptrs[word[i] - 'a'], word, i + 1);
}

bool all_ptr_empty(TrieTree t)
{
	bool res = true;
	size_t i = 0;
	while (i < 26 && res)
		if (!t->ptrs[i])
			++i;
		else
			res = false;
	return res;
}

void del(TrieTree& t, const std::string word, size_t i)
{
	if (t)
		if (i <= word.length() - 1)
			del(t->ptrs[word[i] - 'a'], word, i + 1);
		else
		{
			t->eow = false;
			if (all_ptr_empty(t))
			{
				delete t;
				t = nullptr;
			}
		}
}

TrieTree& find_root(TrieTree& t, const std::string word, size_t i)
{
	if (t)
	{
		if (i <= word.length() - 1)
			find_root(t->ptrs[word[i] - 'a'], word, i + 1);
		else return t;
	}
}

void print(TrieTree t, std::string word)
{
	if (t->eow)
	{
		std::cout << word << '\n';
	}
	for (size_t i = 0; i < 26; ++i)
	{
		if (t->ptrs[i])
		{
			print(t->ptrs[i], word + char(i + 'a'));
		}
	}
}

void print_2(TrieTree t, std::string word, int& count)
{
	if (t->eow)
	{
		count++;
		std::cout << word << '\n';
	}
	for (size_t i = 0; i < 26; ++i)
	{
		if (t->ptrs[i])
		{
			print_2(t->ptrs[i], word + char(i + 'a'), count);
		}
	}
}

bool task_1(TrieTree& t, const std::string word, size_t i)
{
	bool result = false;
	TrieTree root = nullptr;
	if (t)
	{
		if (i < word.length())
			task_1(t->ptrs[word[i] - 'a'], word, i + 1);
		else root = t;
	}
	int count = 0;
	if (root)
	{
		print_2(root, word, count);
		std::cout << count << '\n';
		result = true;
	}
	return result;
}

void clear(TrieTree& t)
{
	for (size_t i = 0; i < 26; ++i)
		if (t->ptrs[i])
			clear(t->ptrs[i]);
	delete t;
	t = nullptr;
}

bool include(std::string word, std::string set)
{
	bool* flags = new bool[set.length()]{ 0 };

	int pos = 0;
	for (size_t i = 0; i < word.length(); i++)
	{
		pos = set.find(word[i]);
		if (pos != -1)
			flags[pos] = true;
	}

	bool res = true;
	size_t i = 0;
	while (i < set.length() && res)
	{
		if (!flags[i])
			res = false;
		i++;
	}

	return res;
}

//void task(TrieTree& t, std::string set, std::string word)
//{
//    /*if (t->eow)
//    {
//        bool* flags = new bool[set.length()]{ 0 };
//
//        int pos = 0;
//        for (size_t i = 0; i < word.length(); i++)
//        {
//            pos = set.find(word[i]);
//            if (pos != -1)
//                flags[pos] = true;
//        }
//
//        bool res = true;
//        size_t i = 0;
//        while (i < set.length() && res)
//        {
//            if (!flags[i])
//                res = false;
//            i++;
//        }
//
//        if (res)
//            std::cout << word << '\n';
//    }*/
//
//    for (size_t i = 0; i < 26; ++i)
//    {
//        if (t->ptrs[i])
//        {
//            int pos = set.find(i+'a');
//            if (pos != -1)
//            {
//                word += char(i + 'a');
//                if (include(word, set))
//                {
//                    if (!empty(t) && all_ptr_empty(t) && !t->eow)
//                        clear(t);
//                }
//                else
//                {
//                    task(t->ptrs[i], set, word);
//                }
//            }        
//        }
//    }
//}

void task(TrieTree& t, std::string set, std::string word)
{
	bool flag = true;
	int i = 0;
	while (i < 26 && flag)
	{
		if (t->ptrs[i])
		{
			if (include(word, set))
			{
				clear(t);
				flag = false;
			}
			else
				task(t->ptrs[i], set, word + char(i + 'a'));
		}
		i++;
	}

	if (!empty(t) && all_ptr_empty(t) && !t->eow)
	{
		delete t;
		t = nullptr;
	}
}

using std::cin;
using std::cout;

//void task_11_help(TrieTree& t, std::string set, std::string word)
//{
//    if (t->eow)
//    {
//        bool* flags = new bool[set.length()]{ 0 };
//
//        int pos = 0;
//        for (size_t i = 0; i < word.length(); i++)
//        {
//            pos = set.find(word[i]);
//            if (pos != -1)
//                flags[pos] = true;
//        }
//
//        bool res = true;
//        size_t i = 0;
//        while (i < set.length() && res) 
//        {
//            if (!flags[i])
//                res = false;
//            i++;
//        }
//
//        if (res)
//            std::cout << word << '\n';
//    }
//
//    for (size_t i = 0; i < 26; ++i)
//    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
//        if (t->ptrs[i])
//        {
//            int pos = set.find(i + 'a');
//            if (pos != -1)
//            {
//                task_11_help(t->ptrs[i], set, word + char(i + 'a'));
//            }
//        }
//    }
//}

/*

int main()
{
	bool flag = true;
	while (flag)
	{
		std::ifstream file("D.txt");
		if (file)
		{
			TrieTree root;
			init(root);
			std::string word;
			while (std::getline(file, word))
			{
				if (word.length())
					add(root, word, 0);
			}
			print(root, "");

			std::cout << "-----------------------\n";

			std::string set;
			std::cout << "Enter set \n";
			std::cin >> set;
			std::cout << "-----------------------\n";
			task(root, set, "");

			print(root, "");
			clear(root);
		}
		else
		{
			std::cout << "Error\n";
		}
		std::cout << "Continue? 1 - YES / 0 - NO \n";
		std::cin >> flag;
	}
}
*/

/*
Дано Trie-дерево. Посчитать количество слов, начинающихся с заданной последовательности
*/

int count_words(TrieTree& t, std::string key, size_t ind)
{
	int result = 0;
	if (t->eow && ind >= key.length())
	{
		++result;
	}
	for (size_t i = 0; i < 26; i++)
	{
		if (t->ptrs[i])
		{
			if (ind < key.length() && key[ind] == 'a' + i)
			{
				result += count_words(t->ptrs[i], key, ind + 1);
			}
			else if (ind >= key.length())
			{
				result += count_words(t->ptrs[i], key, ind);

			}
		}
	}
	return result;
}

/*
Дано Trie-дерево. Найти все слова, имеющие заданное окончание.
*/
void find_all_words(TrieTree& t, std::string word, std::string key)
{
	if (t->eow)
	{
		bool result = true;
		for (size_t i = 0; i < key.length() && result; i++)
		{
			if (key[key.length() - i - 1] != word[word.length() - i - 1])
				result = false;
		}
		if (result)
			cout << word << '\n';
	}
	for (size_t i = 0; i < 26; i++)
	{
		if (t->ptrs[i])
			find_all_words(t->ptrs[i], word + char('a' + i), key);
	}
}

/*
Дано Trie-дерево. Определить количество слов, содержащих заданную букву А
*/
int count(TrieTree t)
{
	int result = 0;
	if (t->eow)
		++result;
	for (size_t i = 0; i < 26; i++)
	{
		if (t->ptrs[i])
			result += count(t->ptrs[i]);
	}
	return result;
}

int count_words(TrieTree& t, char A)
{
	int result = 0;
	for (size_t i = 0; i < 26; i++)
	{
		if (t->ptrs[i])
		{
			if (char('a' + i) != A)
				result += count_words(t->ptrs[i], A);
			else
				result += count(t->ptrs[i]);
		}
	}
	return result;
}

/*
найти все формы данного слова
*/

void forms(TrieTree t, std::string word)
{
	if (t->eow)
	{
		cout << word << '\n';
	}
	for (size_t i = 0; i < 26; i++)
	{
		if (t->ptrs[i])
			forms(t->ptrs[i], word + char('a' + i));
	}
}

void find_forms(TrieTree t, std::string word, std::string key, int ind)
{
	if (key.length() == ind)
	{
		forms(t, word);
	}
	for (size_t i = 0; i < 26; i++)
	{
		if (t->ptrs[i])
		{
			if (ind < key.length() && char('a' + i) == key[ind])
				find_forms(t->ptrs[i], word + char('a' + i), key, ind + 1);
		}
	}
}

/*
распечатать все лозы
*/
void print_all_lose(TrieTree& t, std::string word)
{
	if (all_ptr_empty(t))
	{
		cout << word << '\n';
	}
	for (size_t i = 0; i < 26; i++)
	{
		if (t->ptrs[i])
			print_all_lose(t->ptrs[i], word + char('a' + i));
	}
}

/*
построить копию дерева
*/
TrieTree copy(TrieTree t)
{
	TrieTree result = nullptr;
	if (t)
	{
		result = new NODE(*t);
		for (size_t i = 0; i < 26; i++)
		{
			if (t->ptrs[i])
				result->ptrs[i] = copy(t->ptrs[i]);
		}
	}
	return result;
}

/*
удалить слова начинающиеся с заданной подстроки
*/
bool del_words(TrieTree& t, std::string key, int ind)
{
	bool result = false;
	if (ind < key.size())
	{
		if (t->ptrs[key[ind] - 'a'])
		{
			result = del_words(t->ptrs[key[ind] - 'a'], key, ind + 1);
			if (all_ptr_empty(t) && !t->eow)
			{
				delete t;
				t = nullptr;
			}
		}
	}
	else
	{
		clear(t);
	}
	return result;
}

/*
Дано Trie-дерево. Удалить все слова четной длины.
*/

bool del_even_words(TrieTree& t, int len)
{
	bool result = false;
	if (t->eow && len % 2 == 0)
	{
		result = true;
		t->eow = false;
		if (all_ptr_empty(t))
		{
			delete t;
			t = nullptr;
		}
	}
	for (size_t i = 0; i < 26; i++)
	{
		if (t && t->ptrs[i])
		{
			result = del_even_words(t->ptrs[i], len + 1);
		}
	}
	return result;
}



/*
построить копию дерева, в конец каждого слова дописать а
*/
TrieTree copy_a(TrieTree t)
{
	TrieTree result = nullptr;
	if (t)
	{
		result = new NODE(*t);
		if (t->eow)
		{
			result->eow = false;
			TrieTree a = new NODE();
			a->eow = true;
			result->ptrs[0] = a;
		}
		for (size_t i = 0; i < 26; i++)
		{
			if (t->ptrs[i])
				result->ptrs[i] = copy_a(t->ptrs[i]);
		}
	}
	return result;
}

/*
построить копию дерева, в конец каждого слова дописать а
*/
TrieTree copy_aaa(TrieTree t)
{
	TrieTree result = nullptr;
	if (t)
	{
		result = new NODE(*t);
		if (t->eow)
		{
			result->eow = false;
			TrieTree a = new NODE();
			a->eow = true;
			result->ptrs[0] = a;
		}
		for (size_t i = 0; i < 26; i++)
		{
			if (t->ptrs[i])
			{
				result->ptrs[i] = copy_aaa(t->ptrs[i]);
			}
		}

	}
	return result;
}

int main()
{
	std::ifstream file("D.txt");
	if (file)
	{
		TrieTree root;
		init(root);
		std::string word = "";
		while (std::getline(file, word))
		{
			if (word.length() > 0)
				add(root, word, 0);
		}
		print(root, "");

		//cout << count_words(root, "do", 0);
		// 
		//find_all_words(root, "", "do");
		// 
		//cout << count_words(root, 'b');
		// 
		//find_forms(root, "", "abc", 0);
		// 
		//print_all_lose(root, "");
		// 
		//TrieTree newTree = copy(root);
		//print(newTree, "");

		//del_words(root, "abcd", 0);
		//del_even_words(root, 0);
		//print(root, "");
		TrieTree newTree = copy_aaa(root);
		print(newTree, "");

		clear(root);
	}
	else
		cout << "no file\n";
}