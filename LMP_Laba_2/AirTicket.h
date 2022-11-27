#pragma once
#include <string>
#include <iostream>
#include <fstream>

//using Date = int[3];

struct Date
{
private:
	int day, month, year;
public:
	Date() { day = 0; month = 0; year = 0; }
	Date(int a, int b, int c) { day = a; month = b; year = c; }
	int compare(const Date& date)
	{
		int result = 1;

		(year > date.get_year()) ? result = 1 : (month < date.get_month()) ? result = -1 :
			month > date.get_month() ? result = 1 : (month < date.get_month()) ? result = -1 :
			(day > date.get_day()) ? result = 1 : (day < date.get_day()) ? result = -1 : result = 0;

		return result;	
	}

	int get_day() const;
	int get_month() const;
	int get_year() const;

	void set_day(int d) ;
	void set_month(int m) ;
	void set_year(int y) ;

	void print()
	{
		std::cout << day << ' ' << month << ' ' << year << '\n';
	}
};

struct Ticket
{
private:
	std::string target, plane_model, FIO;
	int number;
	Date date;
public:
	Ticket() {};
	Ticket(std::ifstream&);

	int compare(const Ticket&);

	std::string get_target() const;
	std::string get_plane_model() const;
	std::string get_FIO() const;
	int get_number() const;
	Date get_date() const;
	void set_date(int, int, int);
	
	void print();
};