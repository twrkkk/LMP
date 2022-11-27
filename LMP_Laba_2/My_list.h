#pragma once//следит подключена библиотека или нет (чтобы не было повтороного подключения)
#include <iostream>
#include <fstream>
#include "AirTicket.h"

using TInfo = Ticket;//ввод псевдонима

struct NODE //cтруктура узла
{
	TInfo info;
	NODE* next, * prev;
	NODE(TInfo info, NODE* next = nullptr, NODE* prev = nullptr) :info(info), next(next), prev(prev) {} //конструктор
	~NODE()//деструктор
	{
		next = nullptr;
		prev = nullptr;
	}
};

using ptrNODE = NODE*;//псевдоним узла

struct DLIST
{
private:
	ptrNODE begin, end;//создание заглавного и последнего узла
	size_t size;
public:
	DLIST() { begin = nullptr; end = nullptr; }//создаст пустые указатели
	DLIST(std::ifstream& file);
	void first_node(const Ticket& ticket);
	bool empty();
	void add_after(ptrNODE ptr, const Ticket& ticket);
	void add_before(ptrNODE ptr, const Ticket& ticket);
	void print();
	~DLIST();
	Ticket& Delete(ptrNODE& ptr);//выкидываем узел
	ptrNODE& del_before(ptrNODE& ptr);
	ptrNODE& del_after(ptrNODE& ptr);
	ptrNODE get_begin() const
	{
		return begin;
	}
};
