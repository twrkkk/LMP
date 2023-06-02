#include<iostream>
using std::cin; using std::cout;
#include<Windows.h>
#include <utility>
using std::pair;
using std::make_pair;
#include <iomanip>
using std::setw;
const int n = 5;
//���� �� ���� �����������, ��� ������������� ������� ����� �����������
//���� �� ���� ���������, �� ������ ����� ������������, ��������, ������, ������� ������ ������ bool\
(���������� �� �� ������� �� �����) ��� ������ ������� enum �� R,B

pair<int, int> RED[n] { make_pair(27,0),make_pair(91,17),make_pair(11,-11),make_pair(5,0),make_pair(6,1) };
pair<int, int> BLUE[n]{ make_pair(0,2),make_pair(2,0),make_pair(0,-2),make_pair(-2,0),make_pair(7,-1) };
size_t solution[n]{0};//��� ������� ����� ����� ��������������� ������ �� ������� ������� ������//��������� ������������ ��������
size_t curr_sol[n]{ 0 };//���� ����� �� ��� ���������� � ������� �������

//��������: ��� �� ������� ������ ���� ��� �� ����������, �������� � ����������� blue ������� ���� bool ��� ���������� �����\
�����: ��������� ��� �������(�� �� ���������� �� �������)\
�� �� ���������� � �� ������, ��� ��������� ����� ������������� ����������� ����������� �� �����

bool usedBLUE[n]{false};//������� �������������� ��� //�� ����� ���� ��� ������ ���� availBLUE, �� c++ �� ��������� ����������� false :(

unsigned int sumSegments(0);
unsigned int currSegments(0);//���� �������� ����� ���������� ������ � i � Try, �� ����� ��� ���������� ���������� ���������, ������� ����� ���������, ����� �������� �����
//����� ���� ����� ���������� ���������� ����� �� ���� ���������, � ������������� ���� ������ ����� � ����������� ������������ ����������=>\
=>���� ���� ��� ���� ����� � ���� �� ���� ����, ���������� �� ����� ����� 0

unsigned int dist_sqr(pair<int, int> x, pair<int, int> y)//������ ���������� ����� ������ ���, ������ ���������� ����������� ���������
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

double dist(size_t sltn[])//"��������" ���������� ����������� � ������ ��������, ����� ��������� ����������� ���������� �����
{
	double res(0);

	for (size_t i = 0; i < n; ++i)
		res += dist_sqrt(RED[i], BLUE[sltn[i]]);

	return res;
}

void Try(int i) //����� ������ �����, ������� void//i - ����� ������� �����, � ������� ����������� ����\
���� ����� ���������� bool ��� ��� ���� ��� �� �����, �� ����� � ��� ����� �� ������� ��������
{
	for (int k = 0; k < n; ++k)//������� ����� �����
	{
		if (!usedBLUE[k])
		{
			//���������� ����
			usedBLUE[k] = true;//����� ����� ������ ������
			curr_sol[i] = k;//������ i-��� ������� �������� k-��� �����
			unsigned long dist(dist_sqr(RED[i], BLUE[k]));
			currSegments += dist; //��������� k-��� ������� � ��������� �����
			if (currSegments < sumSegments || sumSegments == 0)//< �� <= : ��������� ����������� �������	
				if( i < n - 1)
					Try(i + 1);//������� ��������� �������				
				else
				{
					cout << '(' << currSegments << ')'<<'\n';
					print_solution(curr_sol);
					cout << '\n';
					sumSegments = currSegments;
					for (size_t l = 0; l < n; ++l)
						solution[l] = curr_sol[l];
				}
		

			//����� � ����� ������
			usedBLUE[k] = false;//k-��� ����� ����� ������ ��������
			if(currSegments)currSegments -= dist;//�������� k-��� ������� �� ������� �����
			//curr_sol[i] = k;//�������� �� ����� �� ��� ����� ������������
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
