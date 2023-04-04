#include "HashTable.h"
#include "AirTicket.h"

int main()
{
	int size = 15;
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	std::ifstream file("tickets.txt");

	HashTable hash(file, size);


	/*std::cout << (hash.remove("aqua") ? "removed\n" : "not removed\n");
	TInfo pair;

	if (hash.find("abacus", pair)) {
		pair.print();
	}
	else {
		std::cout << "not found\n";
	}
	if (hash.add(std::make_pair("cow", "Корова"))) {
		std::cout << "add\n";
	}
	else {
		std::cout << "not add\n";
	}*/

	std::cout << (hash.remove("Voronezh Shein Evgeny Alexandrovich 10112022") ? "removed\n" : "not removed\n");
	std::cout << (hash.remove("Voronezh Shein Evgeny Alexandrovich 12112022") ? "removed\n" : "not removed\n");

	
	std::ifstream to_add("to_add.txt");
	Ticket newTicket(to_add);
	if (hash.add(newTicket))
		std::cout << "add\n";
	else
		std::cout << "not add\n";

	Ticket tick;
	if (hash.find("Anapa Shein Evgeny Alexandrovich 10112022", tick))
	{
		HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleHandle, (WORD) (0<<4 | 2<<4));
		std::cout << std::string(30, '*') << '\n';
		tick.print();
		SetConsoleTextAttribute(hConsoleHandle, (WORD) (15<<4 | 0<<4));
	}

	hash.print();

	std::cout << "Hello world!" << std::endl;

	std::cin.get();
}

