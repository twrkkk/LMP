#include <iostream>
#include <Windows.h>

//У игрока имеется набор костей домино(необязательно полный).Найти последовательность
//выкладывания этих костей таким образом, чтобы получившаяся в результате цепочка была максимальной длины.
#include <set>
#include <utility>
#include <vector>
using std::pair;
using std::set;

using Tdomino = pair<int, int>;
std::vector<Tdomino> solution;
const std::vector<Tdomino> data_dominos = { Tdomino(2,3), Tdomino(4,3), Tdomino(3,5), Tdomino(6,5), Tdomino(2,1), Tdomino(1,3)};
int N = data_dominos.size();

set<Tdomino> optimal_sol, curr_sol;

void try_dominos(int ind = 0, int last = -1) {
		bool was_push = false;
		for (int i = 0; i < N; ++i) {
			if ((data_dominos[i].first == last || data_dominos[i].second == last || last == -1) && curr_sol.find(data_dominos[i]) == curr_sol.end()
				&& curr_sol.find(Tdomino(data_dominos[i].second, data_dominos[i].first)) == curr_sol.end()) {
				was_push = true;

				Tdomino put_d = (data_dominos[i].second == last ? Tdomino(data_dominos[i].second, data_dominos[i].first) : data_dominos[i]);
				curr_sol.insert(put_d);

				solution.push_back(put_d);
				try_dominos(ind + 1, put_d.second);
				solution.pop_back();
				curr_sol.erase(put_d);
			}
		}
		if (!was_push) {//all is used
			if (optimal_sol.size() < curr_sol.size() || optimal_sol.empty()) {
				optimal_sol = curr_sol;
				for (auto d : solution)
					std::cout << d.first << '-' << d.second << "   ";
				std::cout << "\n----------------------\n";
			}
		}
}


int main() {

	try_dominos();
	std::cin.ignore().get();
}