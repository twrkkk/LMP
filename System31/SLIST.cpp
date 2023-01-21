#include <iostream>
#include <fstream>
#include <functional>
#include "My_List.h"

using std::cin;
using std::cout;

/*
Дан текстовый файл input.txt, в котором хранятся целые числа.
Создать упорядоченный по возрастанию список. Удалить предпоследнее четное число.
Полученную последовательность записать в текстовый файл output.txt.
Если четных чисел нет, то помимо последовательности в файл записать соответствующее сообщение.
*/

bool task_1(LIST& list)
{
	bool result = false;
	ptrNODE p = list.get_head();
	ptrNODE first = nullptr, second = nullptr;
	while (p->next)
	{
		if ((p->next->info % 2) == 0)
		{
			first = second;
			second = p;
		}
		p = p->next;
	}
	if (first && second)
	{
		list.del_after(first);
		result = true;
	}
	return result;
}

/*
Дан текстовый файл input.txt, в котором хранятся целые числа.
Создать упорядоченный по возрастанию список.
За первым нечетным числом вставить число равное квадрату последнего числа.
Полученную последовательность записать в текстовый файл output.txt.
Если нечетных чисел нет, помимо последовательности в файл записать соответствующее сообщение.
*/

bool task_2(LIST& list)
{
	bool result = false;
	ptrNODE first_odd(0), last_number(0), p = list.get_head();
	while (p->next)
	{
		last_number = p->next;
		if (!first_odd && (p->next->info % 2) != 0)
		{
			first_odd = p->next;
		}
		p = p->next;
	}
	if (first_odd && last_number)
	{
		list.add_after(first_odd, last_number->info * last_number->info);
		result = true;
	}
	return result;
}

/*
Дан текстовый файл input.txt, в котором хранятся целые числа.
Создать список по принципу очереди. Удалить все отрицательные числа.
Полученную последовательность записать в текстовый файл output.txt.
Если отрицательных чисел нет, то помимо последовательности в файл записать соответствующее сообщение.
*/

bool task_3(LIST& list)
{
	bool result = false;
	ptrNODE p = list.get_head();
	while (p && p->next)
	{
		if (p->next->info < 0)
		{
			list.del_after(p);
			result = true;
		}
		else
			p = p->next;
	}
	return result;
}

/*
Дан текстовый файл input.txt, в котором хранятся целые числа. Создать список по принципу очереди.
Удвоить все положительные числа (т.е. за каждым положительным числом вставить его копию).
Полученную последовательность записать в текстовый файл output.txt.
Если положительных чисел нет, то помимо последовательности в файл записать соответствующее сообщение.
*/

bool task_4(LIST& list)
{
	bool result = false;
	ptrNODE p = list.get_head()->next;
	while (p)
	{
		if (p->info > 0)
		{
			list.add_after(p, p->info);
			result = true;
			p = p->next->next;
		}
		else
			p = p->next;
	}
	return result;
}

/*
Дан текстовый файл input.txt, в котором хранятся целые числа.
Создать упорядоченный по возрастанию список.
Удалить первую подпоследовательность из нечетных чисел.
Полученную последовательность записать в текстовый файл output.txt.
Если нечетных чисел нет, то помимо последовательности в файл записать соответствующее сообщение.
*/

bool task_5(LIST& list)
{
	bool result = false;
	ptrNODE p = list.get_head();
	while (p->next)
	{
		if (p->next->info % 2 != 0)
		{
			list.del_after(p);
		}
		else
			p = p->next;
	}
	return result;
}

//bool task_5(LIST& list)
//{
//	bool result = false;
//	ptrNODE start(0), end(0), p = list.get_head();
//	while (p->next && (!start || !end))
//	{
//		if (std::abs(p->next->info % 2) != 0)
//		{
//			if (!start)
//				start = p;
//		}
//		else
//		{
//			if (!end && p->next->next)
//			{
//				end = p->next->next;
//			}
//		}
//		p = p->next;
//	}
//
//	while (start && end && start->next != end)
//	{
//		list.del_after(start);
//		result = true;
//	}
//	return result;
//}

/*
Дан текстовый файл input.txt, в котором хранятся целые числа. Создать упорядоченный по возрастанию список.
Удалить последнюю подпоследовательность из четных чисел. Полученную последовательность записать в текстовый файл output.txt.
Если нечетных чисел нет, то помимо последовательности в файл записать соответствующее сообщение.
*/

bool task_6(LIST& list)
{
	bool result = false;
	ptrNODE p = list.get_head(), start = p, end = p;
	while (p && p->next)
	{
		if (std::abs((p->next->info % 2)) == 0)
		{
			start = end = p;
			while (p->next && std::abs((p->next->info % 2)) == 0)
			{
				if (p->next)
					end = p->next;
				p = p->next;
			}
		}
		p = p->next;
	}

	result = start && end;
	if (start->next == list.get_tail())
	{
		list.del_after(start);
	}
	else if (end != list.get_tail())
	{
		if (end->next)
			end = end->next;
		while (start->next != end)
		{
			list.del_after(start);
		}
	}
	else
	{
		while (start->next)
		{
			list.del_after(start);
		}
	}

	return result;
}

/*
Дан текстовый файл input.txt, в котором хранятся целые числа. Создать упорядоченный по возрастанию список.
найти последнюю пару элементов оканчиваюющихся на цифру 7, удалить элементы между ними включая сами числа иначе оставить список без изменений
*/

bool task_7(LIST& list, std::function<bool(int number)> lambda)
{
	bool result = false;
	ptrNODE first = nullptr, second = nullptr, p = list.get_head();
	while (p->next)
	{
		if (lambda(std::abs(p->next->info)))
		{
			first = second;
			second = p;
		}
		p = p->next;
	}

	//cout << first->info << ' ' << second->info;
	result = first && second;

	if (second->next != list.get_tail())
	{
		if (second->next->next)
			second = second->next->next;
		while (first->next != second)
		{
			list.del_after(first);
		}
	}
	else
	{
		while (first->next)
			list.del_after(first);
	}
	return result;
}

/*
переставить последний кратный трем в начало списка
*/

bool task_8(LIST& list)
{
	bool result = false;
	ptrNODE p = list.get_head(), last = nullptr;

	while (p->next)
	{
		if (std::abs(p->next->info) % 3 == 0)
			last = p;
		p = p->next;
	}

	auto switch_pointers =
		[](ptrNODE q, ptrNODE p)
	{
		ptrNODE tmp = p->next;
		p->next = tmp->next;
		tmp->next = q->next;
		q->next = tmp;
	};

	if (last)
	{
		result = true;
		switch_pointers(list.get_head(), last);
		//switch_pointers(last,list.get_head()->next); если нужно поменять местами элемент last->next и list.get_head()->next
	}

	return result;
}

/*
Дан текстовый файл input.txt, в котором хранятся целые числа. Создать упорядоченный по возрастанию список.
найти последнюю пару элементов оканчиваюющихся на цифру 7, удалить элементы между ними включая сами числа иначе оставить список без изменений
*/

bool task(LIST& list, std::function<bool(int)> lambda)
{
	bool result = false;
	ptrNODE p = list.get_head(), first = nullptr, second = nullptr;
	while (p->next)
	{
		if (p->next->info % 7 == 0)
		{
			first = second;
			second = p;
		}
		p = p->next;
	}

	if (first && second)
	{
		result = true;
		if (second->next->next)
			second = second->next->next;
		while (first->next != second)
			list.del_after(first);
	}

	return result;
}

int main()
{
	std::ifstream file("numbers.txt");
	if (file)
	{
		LIST list;
		list.create_by_queue(file);
		list.print();
		std::ofstream out("output.txt");

		auto lambda = [](int number) {return (std::abs(number) % 10 == 7); };
		if (!task(list, lambda))
		{
			out << "no even elem\n";
		}

		ptrNODE p = list.get_head()->next;
		while (p)
		{
			out << p->info << ' ';
			p = p->next;
		}
		out << '\n';

		out.close();
	}
	file.close();
}
