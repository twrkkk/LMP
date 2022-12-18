#include <iostream>
#include "Polyclinic.h"

int main()
{
	std::ifstream file("data.txt");
	if (file)
	{
		std::string name = "abc";
		Polyclinic p("xyz");
		p.set_persons(file);
		p.print(std::cout);
	}
}

