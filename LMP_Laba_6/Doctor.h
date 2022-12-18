#pragma once
#include "Persone.h"

enum Category
{
	First = 1,
	Second,
	Third,
	Highest
};

enum Qualification
{
	Dentist,
	Surgeon,
	Psychiatrist,
	Cardiologist
};
class Doctor : public Persone
{
private:
	Qualification qualification;
	size_t work_experience;
	Category category;
public:
	Doctor(std::string _FIO, Gender _gender, Qualification _qualification, size_t _work_experience, Category _category) : Persone(_FIO, _gender)
	{
		qualification = _qualification;
		work_experience = _work_experience;
		category = _category;
	}
	void print(std::ostream& out) override
	{
		out << FIO << ' ' << gender << ' ' << qualification << ' ' << work_experience << ' ' << category << '\n';
	}
};