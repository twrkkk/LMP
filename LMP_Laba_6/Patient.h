#pragma once
#include "Persone.h"

class Patient : public Persone
{
private:
	size_t age;
	std::string insurance;
public:
	Patient() : Persone() { age = 0, insurance = ""; }
	Patient(std::string _FIO, Gender _gender, size_t _age, std::string _insurance): Persone(_FIO, _gender)
	{
		age = _age;
		insurance = _insurance;
	}
	std::string get_insurance() const { return insurance; }
	void print(std::ostream& out) override
	{
		out << FIO << ' ' << gender_to_string[gender] << ' ' << age << ' ' << insurance << '\n';
	}
};