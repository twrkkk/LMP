#pragma once
#include "Persone.h"
#include <map>

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

std::map <Category, std::string> category_to_string = {
	{First, "First"},
	{Second, "Second"},
	{Third, "Third"},
	{Highest, "Highest"},
};

std::map <Qualification, std::string> qualification_to_string = {
	{Dentist, "Dentist"},
	{Surgeon, "Surgeon"},
	{Psychiatrist, "Psychiatrist"},
	{Cardiologist, "Cardiologist"},
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
		out << FIO << ' ' << gender_to_string[gender] << ' ' << qualification_to_string[qualification] << ' ' << work_experience << ' ' << category_to_string[category] << '\n';
	}
};