#pragma once
#include <string>

enum Gender
{
	Male,
	Female
};

class Persone
{
public:
	virtual void print(std::ostream& out) = 0;
	Persone() { FIO = "", gender = Male; }
	Persone(std::string _FIO, Gender _gender) : FIO(_FIO), gender(_gender) {}
	std::string get_FIO() { return FIO; }
protected:
	std::string FIO;
	Gender gender;
};