#include "AirTicket.h"

Ticket::Ticket(std::ifstream& file)
{
	std::getline(file, target);
	std::getline(file, plane_model);
	std::getline(file, FIO);
	file >> number;
	int day = 0, month = 0, year = 0;
	file >> day >> month >> year;
	set_date(day, month, year);
	//Date date(day, month, year);
	file.ignore();
	std::string delim_line;
	std::getline(file, delim_line);
}

int Ticket::compare(const Ticket& ticket)
{
	int result = 1;
	if (target < ticket.get_target() ||
		target == ticket.get_target() && (date.compare(ticket.date)) < 0 ||
		target == ticket.get_target() && (date.compare(ticket.date)) == 0 && number < ticket.get_number())
		result = -1;
	else if (target == ticket.get_target() && date.compare(ticket.date) == 0 && number == ticket.get_number())
		result = 0;

	return result;
}

std::string Ticket::get_target() const
{
	return target;
}

std::string Ticket::get_plane_model()const
{
	return plane_model;
}

std::string Ticket::get_FIO()const
{
	return FIO;
}

int Ticket::get_number() const
{
	return number;
}

Date Ticket::get_date() const
{
	return date;
}

void Ticket::set_date(int d, int m, int y)
{
	date.set_day(d);
	date.set_month(m);
	date.set_year(y);

}

void Ticket::print()
{
	std::cout << target << '\n';
	std::cout << number << '\n';
	std::cout << plane_model << '\n';
	std::cout << FIO << '\n';
	date.print();
	std::cout << '\n';
}

int Date::get_day() const
{
	return day;
}

int Date::get_month() const
{
	return month;
}

int Date::get_year() const
{
	return year;
}

void Date::set_day(int d) 
{
	day = d;
}

void Date::set_month(int m)
{
	month = m;
}

void Date::set_year(int y)
{
	year = y;
}
