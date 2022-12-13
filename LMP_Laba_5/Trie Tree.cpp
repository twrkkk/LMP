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

bool all_flags_true(bool* flags, size_t count)
{
    bool res = true;
    for (size_t i = 0; i < count && res; i++)
    {
        if (!flags[i])
            res = false;
    }
    return res;
}

void reset_all_flags(bool* flags, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        flags[i] = false;
    }
}

void task_11_help(TrieTree& t, std::string set, std::string word, bool* flags)
{
    if (t->eow)
    {
        bool res = all_flags_true(flags, set.length());
        
        if (res)
        {
            std::cout << word << '\n';
            reset_all_flags(flags, set.length());
        }
    }
    for (size_t i = 0; i < 26; ++i)
    {
        if (t->ptrs[i])
        {
            int pos = set.find(i + 'a');
            if (pos != -1)
            {
                flags[pos] = true;
                task_11_help(t->ptrs[i], set, word + char(i + 'a'), flags);
            }
        }
    }
}

void task_11(TrieTree& t, std::string set)
{
    bool* flags = new bool[set.length()]{0};
    if (t)
        task_11_help(t, set, "", flags);
}

void clear(TrieTree& t)
{
    for (size_t i = 0; i < 26; ++i)
        if (t->ptrs[i])
            clear(t->ptrs[i]);
    delete t;
    t = nullptr;
}


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
            task_11(root, set);

            std::cout << "-----------------------\n";
            
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
