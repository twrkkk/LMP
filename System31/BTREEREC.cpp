#include <iostream>
#include <fstream>
#include <string>
#include <queue>


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

//int task(Tree& t)
//{
//	int result = 0;
//	if (t)
//	{
//		result = (t->info % 2 != 0 ? 1 : 0) + task(t->left) + task(t->right);
//	}
//	return result;
//}


TInfo recursion_task(Tree t)
{
	TInfo result = 0;
	if (t)
	{
		if (t->left)
			result = recursion_task(t->left);
		else if (t->right)
			result = recursion_task(t->right);
		else
			result = t->info;
	}

	return result;
}

TInfo non_recursion(Tree root)
{
	std::queue<Tree> q;
	q.push(root);
	int count = 1;
	TInfo result = 0;
	bool flag = false;
	while (!q.empty() && !flag)
	{
		int countNext = 0;
		for (int i = 1; i <= count; i++)
		{
			Tree t = q.front();
			q.pop();
			if (t->left)
			{
				q.push(t->left);
				++countNext;
			}
			else if (t->right)
			{
				q.push(t->right);
				++countNext;
			}
			else if (i == 1) // first in queue - left elem
			{
				flag = true;
				result = t->info;
			}

			/*	if (t->right && !flag)
				{
					q.push(t->right);
					++countNext;
				}*/
		}
		count = countNext;
	}
	return result;
}

/*
Дано бинарное дерево Т. Найти сумму листьев.
*/

int sum_of_sheet(Tree t)
{
	int sum = 0;
	if (t)
	{
		sum += sum_of_sheet(t->left);
		sum += sum_of_sheet(t->right);
		if (!t->left && !t->right)
		{
			sum += t->info;
		}
	}
	return sum;
}

/*
В бинарном дереве Т удалить листовые элементы.
*/

void del_sheets(Tree& t)
{
	if (t)
	{
		if (!t->left && !t->right) // t is sheet
		{
			/*if (parent->left == t) parent->left = nullptr;
			else if (parent->right == t) parent->right = nullptr;
			delete t;
			t = nullptr;
			parent->count--;*/
			Clear(t);
		}
		else
		{
			del_sheets(t->left);
			del_sheets(t->right);
		}

	}
}

/*
Дано бинарное дерево Т. Найти количество отрицательных элементов
*/

int count_negative_elems(Tree t)
{
	int count = 0;
	if (t)
	{
		if (t->info < 0) ++count;
		count += count_negative_elems(t->left);
		count += count_negative_elems(t->right);
	}
	return count;
}

/*
Дано бинарное дерево Т. Найти максимальный по модулю элемент
*/

int max_abs_elem(Tree t)
{
	int result = 0;
	if (t)
	{
		result = std::max(max_abs_elem(t->left), max_abs_elem(t->right));
		if (std::abs(t->info) > result)
			result = std::abs(t->info);
	}
	return result;
}

/*
Дано бинарное дерево Т. Найти значение самого левого листа.
*/

int left_sheet(Tree t)
{
	int result = 0;
	if (t)
	{
		if (t->left)
		{
			result = left_sheet(t->left);
		}
		else if (t->right)
		{
			result = left_sheet(t->right);
		}
		else
		{
			result = t->info;
		}
	}
	return result;
}

/*
Дано бинарное дерево Т. Заменить отрицательные элементы на их абсолютные величины
*/

void change_negative_elems(Tree t)
{
	if (t)
	{
		if (t->info < 0)
			t->info = -t->info;
		if (t->left)
			change_negative_elems(t->left);
		if (t->right)
			change_negative_elems(t->right);
	}
}

/*
Дано бинарное дерево Т. Напечатать значения листьев.
*/

void print_sheet_info(Tree t)
{
	if (t)
	{
		if (!t->left && !t->right)
		{
			std::cout << t->info << ' ';
		}
		else
		{
			print_sheet_info(t->left);
			print_sheet_info(t->right);
		}
	}
}

/*
Дано бинарное дерево Т. Проверить входит ли элемент Е в дерево Т.
*/

bool contains(Tree t, int elem)
{
	bool result = false;
	if (t)
	{
		if (t->info == elem)
			result = true;

		if (!result)
		{
			result = contains(t->left, elem) || contains(t->right, elem);
		}
	}
	return result;
}

/*
Дано бинарное дерево Т. Вычислить число элементов на n-м уровне.
*/

int count_elem(Tree t, int n, int level)
{
	int count = 0;
	if (t)
	{
		if (level == n)
			++count;

		if (count == 0)
		{
			count = count_elem(t->left, n, level + 1) + count_elem(t->right, n, level + 1);
		}
	}
	return count;
}

/*
дано бинарное дерево. удалить все элементы ниже n уровня
*/

void delete_elems(Tree& t, int n, int level)
{
	if (level > n)
	{
		Clear(t);
	}
	if (t)
	{
		delete_elems(t->left, n, level + 1);
		delete_elems(t->right, n, level + 1);
	}
}

/*
Дано бинарное дерево описать структуру+
рекурсивную функцию удаления (всех) элементов после первого нечётного по каждой ветке (если нечётных в ветке нет то ветка не изменяется )
*/

bool delete_after_odd(Tree& t)
{
	bool result = false;
	if (t)
	{
		if (std::abs(t->info) % 2 != 0)
		{
			Clear(t->left);
			Clear(t->right);
			result = true;
		}
		else
		{
			result = result || delete_after_odd(t->left);
			result = result || delete_after_odd(t->right);
		}
	}
	return result;
}

/*
Дано бинарное дерево Т. Построить его копию без листьев.
*/

Tree copy_without_sheets(Tree root) {
	if (!root) return nullptr;
	if (!root->left && !root->right) return nullptr;
	Tree new_root = new NODE(root->info);
	new_root->left = copy_without_sheets(root->left);
	new_root->right = copy_without_sheets(root->right);
	return new_root;
}

/*
дано бинарное дерево. удалить все элементы ниже n уровня
*/

void delete_tree(Tree& t, int n, int level)
{
	if (t)
	{
		if (level > n)
		{
			Clear(t);
		}
		if (t&&t->left)
			delete_tree(t->left, n, level + 1);
		if(t&&t->right)
			delete_tree(t->right, n, level + 1);
			
	}
}

void main()
{
	std::ifstream file("numbers.txt");
	int count;
	file >> count;
	Tree root = Build_Search("numbers.txt");

	std::cout << "Binary Search Tree \n";
	Print(root, 0);
	std::cout << '\n';

	//std::cout << sum_of_sheet(root);

	//del_sheets(root);
	//Print(root, 0);

	//std::cout << count_negative_elems(root);

	//std::cout << max_abs_elem(root);

	//std::cout << left_sheet(root);

	//change_negative_elems(root);

	//print_sheet_info(root);

	//std::cout << contains(root, -30);

	//std::cout << count_elem(root, 2, 0);

	//std::cout << delete_elems(root, 2, 0);

	//delete_elems(root, 2, 0);

	//std::cout<<delete_after_odd(root);

	//Tree newtree = copy_without_sheets(root);
	//Print(newtree, 0);

	delete_tree(root, 2, 0);
	Print(root, 0);

	//std::cout << "Left Sheet : ";
	//std::cout << recursion_task(root);
	//std::cout << non_recursion(root);
	std::cout << '\n';

	Clear(root);
	std::cin.get();
}