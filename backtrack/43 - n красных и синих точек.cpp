#include<iostream>
using std::cin; using std::cout;
#include<Windows.h>
#include <utility>
using std::pair;
using std::make_pair;
#include <iomanip>
using std::setw;
const int n = 5;
//если не даны упорядочено, для оптимальности решения можно упорядочить
//если не даны раздельно, то просто можно использовать, например, кортеж, который хранит первым bool\
(отвечающий за то красная ли точка) или вообще создать enum из R,B

pair<int, int> RED[n] { make_pair(27,0),make_pair(91,17),make_pair(11,-11),make_pair(5,0),make_pair(6,1) };
pair<int, int> BLUE[n]{ make_pair(0,2),make_pair(2,0),make_pair(0,-2),make_pair(-2,0),make_pair(7,-1) };
size_t solution[n]{0};//это индексы синих точек соответствующих идущим по порядку красным точкам//хранилище оптимального варианта
size_t curr_sol[n]{ 0 };//тоже самое но оно изменяемое в течение попыток

//алгоритм: идём по красным точкам пока они не закончатся, помечаем в соразмерном blue массиве типа bool уже посещённые точки\
конец: перебрали все красные(мы их перебираем по порядку)\
мы не спускаемся в те случаи, где суммарная длина непревосходит накопленную оптимальную до этого

bool usedBLUE[n]{false};//сначала неиспользованы все //на самом деле тут раньше было availBLUE, но c++ по умолчанию распихивает false :(

unsigned int sumSegments(0);
unsigned int currSegments(0);//этот параметр можно передавать вместе с i в Try, но вроде как глобальное используем остальное, поэтому зачем усложнять, важен алгоритм вроде
//любая пара чисел однозначно определяет точку на этой плоскости, и существование двух разных точек с одинаковыми координатами невозможно=>\
=>пока есть два вида точек и хотя бы одна пара, расстояние не будет равно 0

unsigned int dist_sqr(pair<int, int> x, pair<int, int> y)//вместо вычисления корня каждый раз, просто сравниваем подкоренные выражения
{
	return (x.first - y.first)*(x.first - y.first)+(x.second - y.second)*(x.second - y.second);
}
double dist_sqrt(pair<int, int> x, pair<int, int> y)
{
	return sqrt(dist_sqr(x, y));
}

void print_solution(size_t sltn[])
{
	for (size_t i = 0; i < n; ++i)
		cout <<  'R' << i << " (" << setw(3)<<RED[i].first << ", " << setw(3) << RED[i].second << ") <-> B" << sltn[i] << " (" << setw(3) << BLUE[sltn[i]].first << ", "\
		<< setw(3) << BLUE[sltn[i]].second << ")  = " << dist_sqrt(RED[i], BLUE[sltn[i]]) << '\n';
}

double dist(size_t sltn[])//"реальное" расстояние вычисляется в идеале единожды, после получения оптимальной комбинации точек
{
	double res(0);

	for (size_t i = 0; i < n; ++i)
		res += dist_sqrt(RED[i], BLUE[sltn[i]]);

	return res;
}

void Try(int i) //ответ всегда будет, поэтому void//i - номер красной точки, к которой подбирается пара\
была мысль возвращать bool как тот факт был ли спуск, но вроде и без этого всё логично работает
{
	for (int k = 0; k < n; ++k)//перебор синих точек
	{
		if (!usedBLUE[k])
		{
			//составляем пару
			usedBLUE[k] = true;//синяя точка теперь занята
			curr_sol[i] = k;//парная i-той красной является k-тая синяя
			unsigned long dist(dist_sqr(RED[i], BLUE[k]));
			currSegments += dist; //учитываем k-тый отрезок в суммарной длине
			if (currSegments < sumSegments || sumSegments == 0)//< на <= : последнее оптимальное решение	
				if( i < n - 1)
					Try(i + 1);//пробуем следующую красную				
				else
				{
					cout << '(' << currSegments << ')'<<'\n';
					print_solution(curr_sol);
					cout << '\n';
					sumSegments = currSegments;
					for (size_t l = 0; l < n; ++l)
						solution[l] = curr_sol[l];
				}
		

			//откат в любом случае
			usedBLUE[k] = false;//k-тая синяя точка теперь доступна
			if(currSegments)currSegments -= dist;//вычитаем k-тый отрезок из текущей суммы
			//curr_sol[i] = k;//отменять не нужно тк это будет перезаписано
		}
	}
}
int main()
{
	Try(0);
	cout << "Segments' lengths summ: " <<std::setprecision(5)<< dist(solution)<<'\n';
	cout << "The segments:\n";
	print_solution(solution);

	cin.get();
	return 0;
}
