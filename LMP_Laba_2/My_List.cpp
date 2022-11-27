#include "My_list.h"
#include <functional>

ptrNODE find_place(ptrNODE begin, const Ticket& ticket)
{
	ptrNODE p = begin;
	while (p && p->info.compare(ticket) < 0)
		p = p->next;
	return p;
}

DLIST::DLIST(std::ifstream& file)
{
	Ticket ticket(file);
	first_node(ticket);
	ptrNODE place;
	while (!file.eof())
	{
		Ticket ticket(file);
		place = find_place(begin, ticket);
		if (place)
			add_before(place, ticket);
		else
			add_after(end, ticket);
	}
	file.close();
}

void DLIST::first_node(const Ticket& ticket)
{
	begin = new NODE(ticket);
	end = begin;
}

bool DLIST::empty()
{
	return begin == nullptr;
}

void DLIST::add_after(ptrNODE ptr, const Ticket& ticket)
{
	ptrNODE p = new NODE(ticket, ptr->next, ptr);
	if (ptr == end)
		end = p;
	else
		ptr->next->prev = p;
	ptr->next = p;
}

void DLIST::add_before(ptrNODE ptr, const Ticket& ticket)
{
	ptrNODE p = new NODE(ticket, ptr, ptr->prev);
	if (ptr == begin)
		begin = p;
	else
		ptr->prev->next = p;
	ptr->prev = p;
}

void DLIST::print()
{
	ptrNODE ptr = begin;
	while (ptr)
	{
		ptr->info.print();
		ptr = ptr->next;
	}
}

DLIST::~DLIST()
{
	while (!empty())
		Delete(begin);
}

ptrNODE& DLIST::del_after(ptrNODE& ptr)
{
	ptrNODE tmp = ptr->next;
	ptr->next = tmp->next;
	if (!tmp->next)
		end = ptr;
	else
		tmp->next->prev = ptr;
	
	static ptrNODE a;
	a = tmp->next;

	delete tmp;
	size--;
	return a;
}

ptrNODE& DLIST::del_before(ptrNODE& ptr)
{
	ptrNODE tmp = ptr->prev;
	ptr->prev = tmp->prev;
	if (!tmp->prev)
		begin = ptr;
	else
		tmp->prev->next = ptr;

	static ptrNODE a;
	a = tmp->next;

	delete tmp;
	size--;
	return a;
}

Ticket& DLIST::Delete(ptrNODE& ptr)
{
	ptrNODE p = ptr;
	if (ptr == begin)
	{
		begin = p->next;
		ptr = begin;
		if (p->next)
			p->next->prev = nullptr;
	}
	else
		if (ptr == end)
		{
			end = p->prev;
			ptr = end;
			if (p->prev)
				p->prev->next = nullptr;
		}
		else
		{
			ptr = ptr->next;
			p->next->prev = p->prev;
			p->prev->next = p->next;
		}
	static Ticket ticket;
	ticket = p->info;
	delete p;
	return ticket;
}
