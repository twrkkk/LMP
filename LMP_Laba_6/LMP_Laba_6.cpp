#include <iostream>
#include "Polyclinic.h"

int main()
{
	std::ifstream file("data.txt");
	if (file)
	{
		std::string name = "abc";
		Polyclinic p("xyz", file);
		//p.set_persons(file);
		p.print(std::cout);
		std::cout << "---------------------------\n";
		p.delete_person();
		p.print(std::cout);
	}
}

