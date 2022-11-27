#include "My_List.h"

using std::cin;
using std::cout;

bool task(LIST& list)
{
	auto get_first_digit = [](int number)
	{
		size_t result = 0;
		while (number)
		{
			result = number % 10;
			number /= 10;
		}
		return result;
	};

	bool result = false;
	ptrNODE beg = list.get_head(), p = beg;// , end = nullptr;
	size_t digit_1 = get_first_digit(beg->next->info), digit_2 = -1;
	while ( beg && beg->next && !result)
	{
		p = beg->next;
		while (p->next && !result)
		{
			digit_2 = get_first_digit(p->next->info);
			if (digit_1 == digit_2)
			{
				result = true;
			}
			else
				p = p->next;

		}

		if (!result)
		{
			beg = beg->next;
			if((beg->next != nullptr))
				digit_1 = get_first_digit(beg->next->info);
			else
			{
				beg = nullptr;
				p = nullptr;
			}
		}

	}

	//cout << beg->info << ' ' << p->info << '\n';

	auto switch_pointers =
		[&](ptrNODE q, ptrNODE p)
	{
		ptrNODE tmp = p->next;
		p->next = tmp->next;
		tmp->next = q->next;
		q->next = tmp;
		if (!p->next)
			list.set_tail(p);
	};

	if (beg && p)
	{
		result = true;
		switch_pointers(beg, p);

		if (beg->next->next != p)
			switch_pointers(p, beg->next); // не надо делать если они соседи
	}
	


	return result;
}

void list_to_stream(std::ostream& stream, LIST& list, bool result)
{
	ptrNODE p = list.get_head();
	while (p->next)
	{
		stream << p->next->info << ' ';
		p = p->next;
	}

	if (!result)
		stream << "\nno elem\n";
}

void clear_list(LIST& list)
{
	while(!list.empty())
		list.del_from_head();
}

void main()
{
	LIST list;
	std::ofstream output("output.txt");
	std::ifstream file("data.txt");
	if (file)
	{

		int choice = -1;

		do
		{

			if (!list.empty())
				clear_list(list);

			cout << "Choose how to create the list:\n" <<
				"1. Create by stack\n" <<
				"2. Create by queue\n" <<
				"3. Create by order\n" <<
				"4. Exit\n";

			bool error = false;
			do
			{
				cin >> choice;
				if (choice < 1 || choice > 4)
					error = true;
			} while (error);

			file.clear();
			file.seekg(0);

			switch (choice)
			{
			case 1:
				list.create_by_stack(file);
				break;
			case 2:
				list.create_by_queue(file);
				break;
			case 3:
				list.create_by_order(file);
				break;
			case 4:
				exit(0);
				break;
			}
			list.print();
			cout << '\n';

			bool result = task(list);
			list_to_stream(output, list, result);

			char a;
			cout << "Exit? (Y - YES, ANY KEY - NO)\n";
			cin >> a;
			if (a == 'y' || a == 'Y')
				choice = 4;

		} while (choice != 4);
		file.close();
		output.close();
	}
	else
		cout << "no file\n";
	std::cin.get();
}
