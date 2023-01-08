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