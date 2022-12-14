#pragma once
#include "Patient.h"
#include "Doctor.h"
#include <list>
#include <memory>
#include <fstream>
#include <map>
#include <iterator>
#include <functional>
#include <algorithm>


std::map <std::string, Gender> convert_gender = {
	{"Male", Male},
	{"Female", Female}
};

std::map <std::string, Category> convert_category = {
	{"First", First},
	{"Second", Second},
	{"Third", Third},
	{"Highest", Highest},
};

std::map <std::string, Qualification> convert_qualification = {
	{"Dentist", Dentist},
	{"Surgeon", Surgeon},
	{"Psychiatrist", Psychiatrist},
	{"Cardiologist", Cardiologist},
};

using Iter = std::list< std::shared_ptr <Persone> >::iterator;

class Polyclinic
{
private:
	std::string name;
	std::list< std::shared_ptr <Persone> > persons;
public:
	Polyclinic(std::string _name) : name(_name) {};
	Polyclinic(std::string _name, std::ifstream& file) : name(_name) { set_persons(file); };
	void set_persons(std::ifstream& file)
	{
		std::string enum_help;
		std::string FIO; Gender gender; size_t age; std::string insurance;
		Qualification qualification; size_t work_experience; Category category;
		std::string buffer;

		while (!file.eof())
		{
			char c;
			file >> c;
			std::getline(file, buffer);
			std::getline(file, FIO);
			std::getline(file, enum_help);
			gender = convert_gender[enum_help];

			if (c == '1') // patient
			{
				file >> age;
				std::getline(file, buffer);
				std::getline(file, insurance);
				std::shared_ptr<Persone> p;
				const Patient& patient = *new Patient(FIO, gender, age, insurance);
				p = std::make_shared<Patient>(patient);
				persons.push_back(p);
			}
			else if (c == '2') // doctor
			{
				std::getline(file, enum_help);
				qualification = convert_qualification[enum_help];
				file >> work_experience;
				std::getline(file, buffer);
				std::getline(file, enum_help);
				category = convert_category[enum_help];
				std::shared_ptr<Persone> p;
				const Doctor& doctor = *new Doctor(FIO, gender, qualification, work_experience, category);
				p = std::make_shared<Doctor>(doctor);
				persons.push_back(p);
			}
			std::getline(file, buffer); // ----------
		}

		sort();

		file.close();
	}

	void sort()
	{
		auto compare = [](std::shared_ptr <Persone> persone_1, std::shared_ptr <Persone> persone_2) {
			return (persone_1.get()->get_FIO() < persone_2.get()->get_FIO());
		};
		persons.sort(compare);
	}

	void delete_person()
	{
		persons.remove_if([](std::shared_ptr<Persone> ptr) {
			bool result = false;
			Patient* object = dynamic_cast<Patient*>(ptr.get());
			if (object != nullptr)
				result = object->get_insurance()[0] == '0';
			return result;
			});
	}
	void print(std::ostream& out)
	{
		for (Iter it = persons.begin(); it != persons.end(); it++)
		{
			Patient* object = dynamic_cast<Patient*>(it->get());
			if (object != nullptr)
				object->print(out);
			else
				(dynamic_cast<Doctor*>(it->get()))->print(out);
		}
	}

};