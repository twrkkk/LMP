﻿#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>

using std::cin;
using std::cout;

using TInfo = int;
struct NODE
{
	TInfo info;
	NODE* left, * right;
	int count = 1;
	NODE() {}
	NODE(TInfo info, NODE* left = nullptr, NODE* right = nullptr) : info(info), left(left), right(right) {}
	~NODE()
	{
		left = nullptr;
		right = nullptr;
	}
};

using Tree = NODE*;

Tree Build_Balans(std::ifstream& file, int count)
{
	Tree result = nullptr;
	if (count)
	{
		int count_left = count / 2;
		int count_right = count - count_left - 1;
		int x;
		file >> x;
		result = new NODE(x);
		result->left = Build_Balans(file, count_left);
		result->right = Build_Balans(file, count_right);
	}
	return result;
}

void Clear(Tree& t)
{
	if (t)
	{
		Clear(t->left);
		Clear(t->right);
		delete t;
		t = nullptr;
	}
}

void Print(Tree t, int level)
{
	if (t)
	{
		Print(t->right, level + 1);
		for (int i = 0; i < level; i++)
			std::cout << ' ';
		std::cout << t->info << '\n';
		Print(t->left, level + 1);
	}
}

int count_even(Tree t)
{
	int result = 0;
	if (t)
		result = (t->info % 2 == 0 ? 1 : 0) + count_even(t->right) + count_even(t->left);
	return result;
}

using TElem = Tree;

//int count_even_stack(Tree root)
//{
//	int result = 0;
//	STACK s;
//	Tree t = root;
//	while (t)
//	{
//		result += (t->info % 2 == 0 ? 1 : 0);
//		if (t->left)
//		{
//			if (t->right)
//				s.push(t->right);
//			t = t->left;
//		}
//		else
//			if (t->right)
//				t = t->right;
//			else
//				if (s.empty())
//					t = t->right;
//				else
//					if (s.empty())
//						t = nullptr;
//					else
//						t = s.pop();
//	}
//	return result;
//}

//int count_even_queue(Tree root)
//{
//	int result = 0;
//	Tree t = root;
//	QUEUE q;
//	q.enqueue(t);
//	while (!q.empty())
//	{
//		t = q.dequeue();
//		result += (t->info % 2 == 0 ? 1 : 0);
//		if (t->left)
//			q.unqueue(t->left);
//		if (t->right)
//			q.unqueue(t->right);
//	}
//	return result;
//}

void add(Tree& t, TInfo elem)
{
	if (!t)
		t = new NODE(elem);
	else
		if (elem < t->info)
			add(t->left, elem);
		else
			if (elem > t->info)
				add(t->right, elem);
			else
				t->count++;
}

Tree search(const Tree& root, TInfo elem)
{
	Tree t = root, ptr = nullptr;
	while (t && !ptr)
	{
		if (elem < t->info)
			t = t->left;
		else
			if (elem > t->info)
				t = t->right;
			else
				ptr = t;
	}
	return ptr;
}

Tree Build_Search(std::string file_name)
{
	std::ifstream file(file_name);
	Tree root = nullptr;
	int elem;
	while (file >> elem)
		add(root, elem);
	file.close();
	return root;
}

void print_order(Tree t)
{
	if (t)
	{
		print_order(t->left);
		for (int i = 1; i <= t->count; ++i)
			std::cout << t->info << ' ';
		print_order(t->right);
	}
}

void find_element(Tree& r, Tree& q)
{
	if (r->right)
		find_element(r->right, q);
	else
	{
		q->info = r->info;
		q->count = r->count;
		q = r;
		r = r->left;
	}
}

bool delete_element(Tree& t, TInfo elem)
{
	bool result = false;
	if (t)
	{
		if (elem < t->info)
			result = delete_element(t->left, elem);
		else
			if (elem > t->info)
				result = delete_element(t->right, elem);
			else
			{
				if (t->count > 1)
					t->count--;
				else
				{
					Tree q = t;
					if (!t->right)
						t = q->left;
					else
						if (!t->left)
							t = q->right;
						else
							find_element(q->left, q);
					delete q;
				}
				result = true;
			}
	}
	return result;
}

Tree Build_Formula(std::ifstream& file)
{
	char c = file.get();
	Tree result = new NODE(' ');
	if (c >= '0' && c <= '9')
		result->info = c;
	else
	{
		result->left = Build_Formula(file);
		result->info = file.get();
		result->right = Build_Formula(file);
		c = file.get();
	}
	return result;
}

std::string print_to_string(const Tree& t)
{
	std::string result = "";
	if (!t->left && !t->right)
		result += t->info;
	else
		result = '(' + print_to_string(t->left) + std::to_string(t->info) + print_to_string(t->right) + ')';
	return result;
}

int calc(const Tree& t)
{
	int result;
	if (!t->left && !t->right)
		result = t->info - '0';
	else
	{
		int left = calc(t->left);
		int right = calc(t->right);
		switch (t->info)
		{
		case '+': result = left + right;
			break;
		case '*': result = left * right;
			break;
		case '-': result = left - right;
			break;
		}
	}
	return result;
}

//int queue_tree_sum(Tree t)
//{
//	int sum = 0;
//	std::queue<Tree> q;
//	q.push(t);
//	Tree elem;
//	int count = 1;
//	int level = 0;
//	while (!q.empty())
//	{
//		int countNext = 0;
//		sum = 0;
//		for (size_t i = 0; i < count; i++)
//		{
//			elem = q.front();
//			sum += elem->info;
//			cout << level << ' ' << elem->info << '\n';
//			if (i == level)
//				cout << sum << '\n';
//			q.pop();
//			if (elem->left)
//			{
//				q.push(elem->left);
//				++countNext;
//			}
//			if (elem->right)
//			{
//				q.push(elem->right);
//				++countNext;
//			}
//		}
//		++level;
//		count = countNext;
//	}
//	return sum;
//}

void stack_tree(Tree t)
{
	std::stack<Tree> s;
	s.push(t);
	Tree elem = s.top();
	while (!s.empty())
	{
		elem = s.top();
		cout << elem->info;
		s.pop();
		if (elem->right)
			s.push(elem->right);
		if (elem->left)
			s.push(elem->left);

	}
}

int queue_tree_sum(Tree t)
{
	int sum = 0;
	std::queue<Tree> q;
	q.push(t);
	while (!q.empty())
	{
		Tree elem = q.front();
		q.pop();
		sum += elem->info;
		if (std::abs(elem->info) % 2 == 0)
		{
			if (elem->left)
				q.push(elem->left);
			if (elem->right)
				q.push(elem->right);
		}
	}
	return sum;
}

int queue_tree_level_sum(Tree t, int n)
{
	int sum = 0;
	std::queue<Tree> q;
	q.push(t);
	int count = 1;
	int level = 0;
	while (!q.empty() && level <= n)
	{
		int countNext = 0;
		for (size_t i = 0; i < count; i++)
		{
			Tree elem = q.front();
			sum += elem->info;
			q.pop();
			if (elem->left)
			{
				q.push(elem->left);
				++countNext;
			}
			if (elem->right)
			{
				q.push(elem->right);
				++countNext;
			}
		}
		++level;
		count = countNext;
	}
	return sum;
}

/*
найти сумму элементов выше уровня n, включая n
*/
int sum(Tree t, int n)
{
	int result = 0;
	std::queue<Tree> q;
	q.push(t);
	int count = 1;
	int level = 0;
	while (!q.empty() && level <= n)
	{
		int countNext = 0;
		for (size_t i = 0; i < count; i++)
		{
			Tree elem = q.front();
			result += elem->info;
			q.pop();
			if (elem->left)
			{
				q.push(elem->left);
				++countNext;
			}
			if (elem->right)
			{
				q.push(elem->right);
				++countNext;
			}
		}
		count = countNext;
		++level;
	}
	return result;
}

int main()
{
	std::ifstream file("numbers.txt");
	if (file)
	{
		Tree root = Build_Search("numbers.txt");
		Print(root, 0);
		//cout << queue_tree_level_sum(root, 2);
		cout << sum(root, 2);
		cout << '\n';
		//stack_tree(root);
	}
	else
		cout << "no file \n";
}
