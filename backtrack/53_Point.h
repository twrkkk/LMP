#pragma once
#include <iostream>
struct Point {
	int x, y;
	Point(int x = 0, int y = 0): x(x), y(y){}
	Point(const Point& p) {
		x = p.x;
		y = p.y;
	}
	Point& operator=(const Point& p) {
		if (this != &p) {
			x = p.x;
			y = p.y;
		}
		return *this;
	}
	bool operator<(const Point& p) const {
		return (x < p.x || (x == p.x && y < p.y));
	}
	bool operator>(const Point& p) const {
		return p < *this;
	}
	bool operator<=(const Point& p) const {
		return (x <= p.x && y <= p.y);
	}
	bool operator>=(const Point& p) const {
		return (x >= p.x && y >= p.y);
	}
	bool operator==(const Point&p) const {
		return (x == p.x && y == p.y);
	}
	Point operator+(const Point& p) const {
		return Point(p.x + x, p.y + y);
	}
	friend std::ostream& operator<<(std::ostream& out, const Point& p) {
		out << " ( " << p.x << ", " << p.y << ") ";
		return out;
	}
};