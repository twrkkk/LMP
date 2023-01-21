#include <iostream>
#include <fstream>
#include "DLIST.h"

using std::cin;
using std::cout;
using std::ifstream;

//bool task_1(DLIST& list)
//{
//	int counter = 0;
//	auto isEven = [](TInfo elem) {return elem % 2 == 0; };
//	ptrNODE p = list.get_end();
//	bool find = false;
//	while (p && !find)
//	{
//		if (isEven(p->info))
//			counter++;
//
//		if (counter != 2)
//			p = p->prev;
//		else
//			find = true;
//	}
//	if (find)
//		list.Delete(p);
//	return find;
//}
/*
удалить центральный элемент если список содержит нечетное кол-во элементов
*/
bool task_1(DLIST& list)
{
	bool result = false;
	ptrNODE p = list.get_begin(), q = list.get_end();
	while (p != q && p->next != q)
	{
		p = p->next;
		q = q->prev;
	}

	if (p == q)
	{
		result = true;
		list.del_after(p->prev->prev->next);
	}
	return result;
}

/*
если список содержит четное кол-во элементов то вставить в центр сумму всех чисел
*/
bool task_2(DLIST& list)
{
	bool result = false;
	ptrNODE p = list.get_begin(), q = list.get_end();
	int sum = p->info + q->info;
	while (p != q && p->next != q)
	{
		p = p->next;
		q = q->prev;
		sum += p->info + q->info;
	}

	if (p->next == q)
	{
		result = true;
		list.add_after(p, sum);
	}
	return result;
}

/*
удалить центральный элемент если список содержит нечетное кол-во элементов
*/

bool task(DLIST& list)
{
	bool result = false;
	ptrNODE p = list.get_begin(), q = list.get_end();
	while (p->next != q && p != q)
	{
		p = p->next;
		q = q->prev;
	}

	if (p == q)
	{
		result = true;
		list.del_after(p->prev);
	}
	return result;
}

int main()
{
	ifstream file("numbers.txt");
	if (file)
	{
		DLIST list(file);
		std::ofstream out("output.txt");
		list.print(cout);
		if (task(list))
		{
			list.print(out);
		}
		else
		{
			out << "no elem\n";
			list.print(out);
		}
		out.close();
	}
	else
		cout << "NO FILE\n";
	file.close();
}
