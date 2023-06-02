#include <iostream>

const int N = 5;
struct item
{
	int weight;
	int price;
	bool in_bag;
};
item Items[N];
int res = 0;
bool bag[N];
int money=0;
bool flag = false;
void task1(int V)
{
	for (int i = 0; i < N; i++)
	{
		if (Items[i].weight <= V && !Items[i].in_bag)
		{
			Items[i].in_bag = true;
			money += Items[i].price;
			task1(V - Items[i].weight);
			money -= Items[i].price;
			Items[i].in_bag = false;
		}
	}
	if (res < money)
	{
		res = money;
		for (int i = 0; i < N; i++)
			bag[i] = Items[i].in_bag;
	}
}

void task2(int V, int S)
{
	if (S <= 0)
	{
		flag = true;
		res = money;
		for (int i = 0; i < N; i++)
			bag[i] = Items[i].in_bag;
	}
	for (int i = 0; i < N && !flag; i++)
	{
		if (Items[i].weight <= V && !Items[i].in_bag)
		{
			Items[i].in_bag = true;
			money += Items[i].price;
			task2(V - Items[i].weight, S-Items[i].price);
			money -= Items[i].price;
			Items[i].in_bag = false;
		}
	}

}


int main()
 {
	
	for (int i = 0; i < N; i++)
	{
		std::cin >> Items[i].weight >> Items[i].price;
		Items[i].in_bag = false;
	}
	//task1(5);
	//std::cout << res << "\n";
	//for (int i = 0; i < N; i++)
	//	if (bag[i])
	//		std::cout << i << " ";
	task2(5,6);
	if (flag)
	{
		std::cout << res << "\n";
		for (int i = 0; i < N; i++)
			if (bag[i])
				std::cout << i << " ";
	}
	else std::cout << -1;
}