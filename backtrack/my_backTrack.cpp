#include <iostream>
#include <vector>
#include <Windows.h>


//using std::vector;
//
//vector<vector<int>> graph;
//vector<bool> visited;
//vector<int> path;
//int cur_len;
//int max_len;
//int n;
//
//bool graph_dfs(int cur_vertex, int start_vertex)
//{
//	visited[cur_vertex] = true;
//	bool result = false;
//	for (int i = 0; i < n; i++)
//	{
//		if (graph[cur_vertex][i] > 0 && 
//			!visited[cur_vertex] && 
//			cur_len + graph[cur_vertex][i] < max_len)
//		{
//			path.push_back(cur_vertex);
//			cur_len += graph[cur_vertex][i];
//			result = graph_dfs(graph[cur_vertex][i], start_vertex);
//			cur_len -= graph[cur_vertex][i];
//		}
//	}
//
//	if (path.size() == n)
//	{
//
//	}
//
//	return result;
//}

const int m = 2;
const int n = 3;
//int table[m][n];
int helper[m][n];
int max_s = 0;
int cur_sum = 0;

#include <iostream>
#include <vector>
#include <algorithm>

int findMaxCoinsRecursive(const std::vector<std::vector<int>>& grid, int row, int col) {
	// row col - target
	if (row == 0 && col == 0) {
		// Базовый случай: достигнута верхняя левая клетка
		return grid[0][0];
	}

	if (row < 0 || col < 0) {
		// Базовый случай: выход за границы квадрата
		return 0;
	}

	// Рекурсивно ищем максимальную сумму монет для предыдущей клетки
	int maxCoinsUp = findMaxCoinsRecursive(grid, row - 1, col);
	int maxCoinsLeft = findMaxCoinsRecursive(grid, row, col - 1);

	// Выбираем путь с максимальной суммой монет
	return max(maxCoinsUp, maxCoinsLeft) + grid[row][col];
}

int numProg(int start, int x) {
	if (x < start) return 0;
	if (x == start) return 1;
	return numProg(start + 1, x) + numProg(start * 3, x);
}

/*
Два игрока, Петя и Ваня, играют в следующую игру. Перед игроками лежат две кучи камней. Игроки ходят по очереди, первый ход делает Петя. За один ход игрок может добавить в одну из куч (по своему выбору) один камень или увеличить количество камней в куче в два раза. Например, пусть в одной куче 10 камней, а в другой 5 камней; такую позицию в игре будем обозначать (10, 5). Тогда за один ход можно получить любую из четырёх позиций: (11, 5), (20, 5), (10, 6), (10, 10). Для того чтобы делать ходы, у каждого игрока есть неограниченное количество камней.
Игра завершается в тот момент, когда суммарное количество камней в кучах становится не менее 77. Победителем считается игрок, сделавший последний ход, т.е. первым получивший такую позицию, при которой в кучах будет 77 или больше камней.
В начальный момент в первой куче было семь камней, во второй куче – S камней; 1 ≤ S ≤ 69.
Будем говорить, что игрок имеет выигрышную стратегию, если он может выиграть при любых ходах противника. Описать стратегию игрока – значит описать, какой ход он должен сделать в любой ситуации, которая ему может встретиться при различной игре противника. В описание выигрышной стратегии не следует включать ходы играющего по этой стратегии игрока, не являющиеся для него безусловно выигрышными, т.е. не являющиеся выигрышными независимо от игры противника.
Известно, что Ваня выиграл своим первым ходом после неудачного первого хода Пети. Укажите минимальное значение S, когда такая ситуация возможна.
19. ответ 18
*/
bool F(int x, int y, int p) {
	if (x + y >= 77 && p == 3) {
		return true;
	}
	if (x + y < 77 && p == 3) {
		return false;
	}

	return F(x + 1, y, p + 1) || F(x * 2, y, p + 1) || F(x, y + 1, p + 1) || F(x, y * 2, p + 1);
}

/*
Для игры, описанной в предыдущем задании, найдите два таких значения S, при которых у Пети есть выигрышная стратегия, причём одновременно выполняются два условия:
− Петя не может выиграть за один ход;
− Петя может выиграть своим вторым ходом независимо от того, как будет ходить Ваня.
Найденные значения запишите в ответе в порядке возрастания.
20. ответ 31 34 
*/

bool F(int x, int y, int p) {
	if (x + y >= 77 && p == 4) {
		return true;
	}
	if (x + y < 77 && p == 4) {
		return false;
	}
	if (x + y >= 77) {
		return false;
	}

	if (p % 2 == 0) {
		return F(x + 1, y, p + 1) && F(x * 2, y, p + 1) && F(x, y + 1, p + 1) && F(x, y * 2, p + 1);
	}
	else {
		return F(x + 1, y, p + 1) || F(x * 2, y, p + 1) || F(x, y + 1, p + 1) || F(x, y * 2, p + 1);
	}
}

/*
Для игры, описанной в задании 19, найдите минимальное значение S, при котором одновременно выполняются два условия:
– у Вани есть выигрышная стратегия, позволяющая ему выиграть первым или вторым ходом при любой игре Пети;
– у Вани нет стратегии, которая позволит ему гарантированно выиграть первым ходом.
21. ответ 30
*/


bool F(int x, int y, int p) {
	if (x + y >= 77 && (p == 3 || p == 5)) {
		return true;
	}
	if (x + y < 77 && p == 5) {
		return false;
	}
	if (x + y >= 77) {
		return false;
	}

	if (p % 2 == 1) {
		return F(x + 1, y, p + 1) && F(x * 2, y, p + 1) && F(x, y + 1, p + 1) && F(x, y * 2, p + 1);
	}
	else {
		return F(x + 1, y, p + 1) || F(x * 2, y, p + 1) || F(x, y + 1, p + 1) || F(x, y * 2, p + 1);
	}
}

bool F1(int x, int y, int p) {
	if (x + y >= 77 && p == 3) {
		return true;
	}
	if (x + y < 77 && p == 3) {
		return false;
	}
	if (x + y >= 77) {
		return false;
	}

	if (p % 2 == 1) {
		return F1(x + 1, y, p + 1) && F1(x * 2, y, p + 1) && F1(x, y + 1, p + 1) && F1(x, y * 2, p + 1);
	}
	else {
		return F1(x + 1, y, p + 1) || F1(x * 2, y, p + 1) || F1(x, y + 1, p + 1) || F1(x, y * 2, p + 1);
	}
}

int main() {
	for (int s = 1; s < 70; s++) {
		if (F(s, 7, 1)) {
			std::cout << s << std::endl;
		}
	}

	std::cout << std::endl;

	for (int s = 1; s < 70; s++) {
		if (F1(s, 7, 1)) {
			std::cout << s << std::endl;
		}
	}

	return 0;
}

int main()
{
	//for (size_t i = 0; i < n; i++)
	//{
	//	map[0][i] = 1;
	//	map[i][3] = 1;
	//	map[i][0] = 1;
	//	map[n - 1][i] = 1;
	//}
	//map[n - 1][n - 1] = 1;

	//for (size_t i = 0; i < n; i++)
	//{
	//	for (size_t j = 0; j < n; j++)
	//	{
	//		visited[i][j] = false;
	//	}
	//}

	////for (size_t i = 0; i < n; i++)
	////{
	////	for (size_t j = 0; j < n; j++)
	////	{
	////		std::cout << map[i][j] << ' ';
	////	}
	////	std::cout << '\n';
	////}

	//Point start(1, 3), finish(n - 1, n - 1);
	//Try6(start, finish, 0);


	//for (size_t i = 0; i < m; i++)
	//{
	//	for (size_t j = 0; j < n; j++)
	//	{
	//		std::cout << table[i][j] << ' ';
	//	}
	//	std::cout << '\n';
	//}

	//for (int i = 1; i < m; i++)
	//	helper[i][0] += table[i - 1][0];
	//for (int i = 1; i < n; i++)
	//	helper[0][i] += table[0][i - 1];

	//max_sum();

	srand(GetTickCount());
	std::vector<std::vector<int>> table(m, std::vector<int>(n));


	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			table[i][j] = rand() % 100;
		}
	}

	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			std::cout << table[i][j] << ' ';
		}
		std::cout << '\n';
	}

	//int maxCoins = findMaxCoins(table);
	//std::cout << "Максимальная сумма монет: " << maxCoins << std::endl;
	//max_sum(table);
	std::cout << findMaxCoinsRecursive(table, m - 1, n - 1) << '\n';


	std::cout << numProg(1,20) << '\n';

	for (int s = 1; s < 70; s++) {
		if (F(s, 7, 1)) {
			std::cout << s << std::endl;
		}
	}

}