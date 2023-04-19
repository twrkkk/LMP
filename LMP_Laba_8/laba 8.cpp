#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct TProgression {
	std::string progression;
	int length;
};

void Try(const vector<int>& z, int n, int start, int step, TProgression& out)
{
	int i = start;
	while (i + 1 < n && z[i + 1] - z[i] == step)
	{
		out.progression += std::to_string(z[i + 1]) + " ";
		++i;
		++out.length;
	}
}

int main() {
	int n;
	cout << "Enter array size (>=2)\n";
	do {
		cin >> n;
	} while (n <= 1);

	vector<int> z(n);

	cout << "Enter array\n";
	for (int i = 0; i < n; i++) {
		cin >> z[i];
	}

	auto predicate = [](int x, int y) {return x < y; };
	std::sort(z.begin(), z.end(), predicate);

	TProgression curr;
	TProgression result;
	result.length = -1;
	bool flag = true;
	for (int i = 1; i < n && flag; i++)
	{
		curr.length = 2;
		curr.progression = std::to_string(z[i - 1]) + " " + std::to_string(z[i]) + " ";
		flag = (n - i + 1) > result.length;
		if (flag)
		{
			Try(z, n, i, z[i] - z[i - 1], curr);
			if (curr.length > result.length)
			{
				result = curr;
			}
		}
	}

	cout << result.progression << '\n';

	return 0;
}