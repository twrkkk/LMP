#pragma once

#include "Point.h"
#include <iostream>

struct Rectangle_{
	Point point;
	int dx, dy;

	Rectangle_(int x = 0, int y = 0, int dx = 0, int dy = 0) : dx(dx), dy(dy) {
		point = Point(x, y);
	}
	Rectangle_(Point p = Point(0,0), int dx = 0, int dy = 0) : point(p), dx(dx), dy(dy) {}
	Rectangle_(const Rectangle_ & r) {
		point = r.point;
		dx = r.dx;
		dy = r.dy;
	}
	Rectangle_& operator=(const Rectangle_& r) {
		if (this != &r) {
			point = r.point;
			dx = r.dx;
			dy = r.dy;
		}
		return *this;
	}
	bool not_cover(const Rectangle_& r) const{
		return (r.point.x > point.x + dx - 1 || //r leftest point righter than this rightest				this | r
			r.point.x + r.dx-1 < point.x ||//r rightest point lefter than this leftest						r | this
			r.point.y > dy - 1 + point.y  ||//r lowest point higher than this highest						this/r
			r.point.y + r.dy -1< point.y); //r highest point lower than this lowest							r/this
	}
	bool operator==(const Rectangle_& r) const {
		return point == r.point && dx == r.dx && dy == r.dy;
	}
 	bool operator<(const Rectangle_& r) const {
		return (point < r.point || (point == r.point && dx + dy < r.dy + r.dx));
	}
	friend std::ostream& operator<<(std::ostream& out, const Rectangle_& r) {
		out << " [ ( " << r.point.x << ", " << r.point.y << ") to ( " << r.point.x + r.dx-1 << ", " << r.point.y + r.dy-1 << ")] ";
		return out;
	}
};