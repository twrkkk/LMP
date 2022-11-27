#pragma once//������ ���������� ���������� ��� ��� (����� �� ���� ����������� �����������)
#include <iostream>
#include <fstream>
#include "AirTicket.h"

using TInfo = Ticket;//���� ����������

struct NODE //c�������� ����
{
	TInfo info;
	NODE* next, * prev;
	NODE(TInfo info, NODE* next = nullptr, NODE* prev = nullptr) :info(info), next(next), prev(prev) {} //�����������
	~NODE()//����������
	{
		next = nullptr;
		prev = nullptr;
	}
};

using ptrNODE = NODE*;//��������� ����

struct DLIST
{
private:
	ptrNODE begin, end;//�������� ���������� � ���������� ����
	size_t size;
public:
	DLIST() { begin = nullptr; end = nullptr; }//������� ������ ���������
	DLIST(std::ifstream& file);
	void first_node(const Ticket& ticket);
	bool empty();
	void add_after(ptrNODE ptr, const Ticket& ticket);
	void add_before(ptrNODE ptr, const Ticket& ticket);
	void print();
	~DLIST();
	Ticket& Delete(ptrNODE& ptr);//���������� ����
	ptrNODE& del_before(ptrNODE& ptr);
	ptrNODE& del_after(ptrNODE& ptr);
	ptrNODE get_begin() const
	{
		return begin;
	}
};
