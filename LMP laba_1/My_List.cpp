#include "My_List.h"
#include <functional>
#define _CRTDBG_MAP_ALLOC_
#include <crtdbg.h>
#define DBG_NEW new(_NORMAL_BLOCK, __FILE, __LINE__)
#define newDBG_NEW

LIST::~LIST()
{
	while (!empty())
		del_from_head();
	delete head;
	_CrtDumpMemoryLeaks();
}

bool LIST::empty()
{

	return !head->next;
}

void LIST::add_to_head(TInfo elem)
{
	add_by_pointer(head->next, elem);
	if (head == tail)
		tail = tail->next;
	++size;
}

void LIST::add_to_tail(TInfo elem)
{
	add_by_pointer(tail->next, elem);
	tail = tail->next;
	tail->next = nullptr;
}

void LIST::add_after(ptrNODE ptr, TInfo elem)
{
	if (ptr)
	{
		add_by_pointer(ptr->next, elem);
		if (ptr == tail)
			tail = tail->next;
	}
}

void LIST::del_from_head()
{
	if (head->next)
	{
		del_by_pointer(head->next);
		if (!head->next)
			tail = head;
		--size;
	}
}

void LIST::del_after(ptrNODE ptr)
{
	if (ptr && ptr->next)
	{
		if (ptr->next == tail)
			tail = ptr;
		del_by_pointer(ptr->next);
		if (empty())
			tail = head;
		--size;
	}
}

void LIST::create_by_stack(std::ifstream& file)
{
	TInfo elem;
	while (file >> elem)
		add_to_head(elem);
}

void LIST::create_by_queue(std::ifstream& file)
{
	TInfo elem;
	while (file >> elem)
		add_to_tail(elem);
}

void LIST::create_by_order(std::ifstream& file)
{
	TInfo elem;
	ptrNODE p = nullptr;
	auto find_place = [this](TInfo elem) ->ptrNODE
	{
		ptrNODE result = head;
		while (result->next && result->next->info < elem)
			result = result->next;
		return result;
	};
	while (file >> elem)
	{
		p = find_place(elem);
		add_after(p, elem);
	}
}

void LIST::print()
{
	ptrNODE p = head->next;
	if (empty())
		std::cout << "no elem\n";
	while (p)
	{
		std::cout << p->info << ' ';
		p = p->next;
	}
}

void LIST::sorting()
{
	auto switch_pointers =
		[](ptrNODE q, ptrNODE p)
	{
		ptrNODE tmp = p->next;
		p->next = tmp->next;
		tmp->next = q->next;
		q->next = tmp;
	};
	ptrNODE h = head->next->next, h_prev = head->next;
	while (h)
	{
		if (h_prev->info > h->info)
		{
			ptrNODE p = head;
			while (p->next != h && p->next->info < h->info)
				p = p->next;
			switch_pointers(p, h_prev);
			h = h_prev->next;
		}
		else
		{
			h_prev = h;
			h = h->next;
		}
	}
	tail = h_prev;
}

void LIST::set_tail(ptrNODE _tail)
{
	tail = _tail;
}
