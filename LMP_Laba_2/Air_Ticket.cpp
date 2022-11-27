#include <iostream>
#include <fstream>
#include <Windows.h>
#include "My_list.h"

bool task(DLIST& list, std::string place, Date& date)
{
	bool stop = false, result = false;
	ptrNODE p = list.get_begin();
	while (p && !stop)
	{
		if (p->info.get_target() > place || p->info.get_target() == place && p->info.get_date().compare(date) > 0) stop = true;
		else
		{
			if (p->info.get_target() == place && p->info.get_date().compare(date) == 0)
			{
				result = true;
				p = list.del_after(p->prev);
			}
		}
		if (!result)
			p = p->next;
	}


	return result;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::ifstream file("tickets.txt");
	if (file)
	{
		DLIST DL(file);
		DL.print();

		std::cout << "----------------------------\n";
		std::string place;
		std::cout << "Enter target\n";
		std::cin >> place;

		std::cout << "Enter date\n";
		int day, month, year;
		std::cin >> day >> month >> year;
		Date date(day, month, year);
		std::cout << "----------------------------\n";

		if (task(DL, place, date))
			DL.print();
		else
			std::cout << "error\n";
	}
	std::cin.get();
	return 0;
}