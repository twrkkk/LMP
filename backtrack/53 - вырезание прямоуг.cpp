#include <iostream>
#include <Windows.h>

#include <algorithm>
#include "Rectangle.h"
#include <set>
using std::set;

const int a = 10;
const int b = 6;
int c = 3, d = 2;

set<Rectangle_> optimal, current;//solutions: the leftest point, width - dy, hight - dx

const int new_pnt = 4; //count next points
const int new_rct = 2; //count rectangles

int dx[new_rct] = { d, c};
int dy[new_rct] = { c, d};


bool is_free(const Rectangle_ & r) {
	bool res = true;
	if (!current.empty()) {
		set<Rectangle_>::iterator end = current.end(),
			it = current.begin();
		while (it != end && it->point.x + it->dx < r.point.x)
			++it;
		while (res && it != end) {
			res = it->not_cover(r);
			++it;
		}
	}
	return res;
}

Point get_dpnext(const Rectangle_& curr, int i) {
	Point dpnext[4] = { Point(curr.dx + curr.point.x, curr.point.y), Point(curr.point.x, curr.point.y + curr.dy),
				Point(curr.point.x - curr.dx, curr.point.y), Point(curr.point.x, curr.point.y - curr.dy) };
	return dpnext[i];
};

bool is_available(const Point& p) {
	return (p.x >= 0 && p.x < a && p.y >= 0 && p.y < b);
}

bool cut(Point p) {//p - current position
	bool was_cut = false;
	for (int i = 0; i < new_rct; ++i) {
		Rectangle_ curr_rct(p, dx[i], dy[i]);
		if (is_available(Point(p.x + dx[i] - 1, p.y + dy[i] - 1)) 
			&& is_free(curr_rct)) {

			current.emplace(p, dx[i], dy[i]);//
			was_cut = true;
			bool is_next = false;

			int max_x = a - ((c < d) ? c : d),
				max_y = b - ((c < d) ? c : d);

			Point pnext(p.x + dx[i], p.y);
			while (pnext.x <= max_x) {
				if (is_available(pnext) && is_free(Rectangle_(pnext,1,1)))
						is_next = cut(pnext);
				++pnext.x;
			}
			
			pnext = Point(p.x - dx[i], p.y);
			while (pnext.x >=0) {
				if (is_available(pnext) && is_free(Rectangle_(pnext, 1, 1)))
					is_next = cut(pnext);
				--pnext.x;
			}

			pnext = Point(p.x, p.y + dy[i]);
			while (pnext.y <= max_y) {
				if (is_available(pnext) && is_free(Rectangle_(pnext, 1, 1)))
					is_next = cut(pnext);
				++pnext.y;
			}

			pnext = Point(p.x, p.y - dy[i]);
			while (pnext.y >= 0) {
				if (is_available(pnext) && is_free(Rectangle_(pnext, 1, 1)))
					is_next = cut(pnext);
				--pnext.y;
			}


			if (!is_next) {

				if (current.size() > optimal.size() || (current.size() == optimal.size() && current!=optimal)) {
					optimal = current;

					int i = 0;
					for (auto rectangle : optimal) {
						std::cout << '\n' << ++i << " rectangle: " << rectangle;
					}
					std::cout << '\n';
				}
			}

			current.erase(curr_rct);
		}
	}
	return was_cut;
}

int main() {
	SetConsoleOutputCP(1251);
	/*std::cout << "\nВведите c и d - параметры вырезаемой области из прямоугольника " << a << " x " << b << ":\n";
	std::cin >> c >> d;*/
	int Scd = c * d, Sab = a * b;

	if (Scd > Sab || !Scd) {
		std::cout << "Вырезаемая область больше исходной.\n";
		/*std::cout << "Вырезаемая область больше исходной. Решить задачу, поменяв параметрами? (Y/N)\n";
		char c; std::cin >> c;
		if (c == 'Y' || c == 'y')
			cut_try();*/
	}
	else if (Sab == Scd)
		std::cout << "\nВырезаемая область равна исходной.\n";
	else {
		cut(Point(0, 0));
		std::cout << "\nOPTIMAL [count = " << optimal.size() << " ]";
		int i = 0;
		for (auto rectangle : optimal) {
			std::cout << '\n' << ++i << " rectangle: " << rectangle;
		}
		std::cout << '\n';
	}
	std::cin.ignore().get();
}