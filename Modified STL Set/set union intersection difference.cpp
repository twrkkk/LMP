#include <iostream>
#include <set>
#include <algorithm>

std::set<int> set_intersect(std::set<int> set1, std::set<int> set2)
{
	std::set<int> res;
	for (int s1 : set1)
	{
		if (set2.find(s1) != set2.end())
			res.insert(s1);
	}
	return res;
}

std::set<int> set_union(std::set<int> set1, std::set<int> set2)
{
	std::set<int> res;
	for (int elem : set1)
		if (res.find(elem) == res.end())
			res.insert(elem);
	for (int elem : set2)
		if (res.find(elem) == res.end())
			res.insert(elem);

	return res;
}

std::set<int> set_difference(std::set<int> reduced, std::set<int> subtractible)
{
	std::set<int> res;
	for (int elem : reduced)
		if (subtractible.find(elem) == subtractible.end())
			res.insert(elem);
	return res;
}

int main()
{
	std::set<int> s = { 1,2,6,10,12,15,19 };
	std::set<int> s2 = { 8,3,1,15,19 };
	std::set<int> s3;
	std::set<int> s4;
	std::set<int> s5;

	s3 = set_intersect(s, s2);
	s4 = set_union(s, s2);
	s5 = set_difference(s, s2);

	for (int elem : s3)
		std::cout << elem << ' ';
	std::cout << '\n';
	for (int elem : s4)
		std::cout << elem << ' ';
	std::cout << '\n';
	for (int elem : s5)
		std::cout << elem << ' ';

}
