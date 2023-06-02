#include <iostream>
#include <vector>


using namespace std;

struct Domino // структура одной доминошки
{
    int left, right;
    bool in;
    Domino(int l, int r)
    {
        left = l;
        right = r;
        in = false;
    }
};

// основная функция, где curL - тек. длина, maxL - макс. длина, curVec - текущий набор доминошек
// maxVec - набор доминошек самой большой длины, prevL - левый край цепочки, prevR - правый край цепочки
void find_max_len(vector<Domino>& vec, int curL, int &maxL, vector<Domino>& curVec, vector<Domino>& maxVec, int prevL, int prevR)
{
       
    if (curL > maxL)
    {
        maxL = curL;
        maxVec = curVec;
    }
    for (int i = 0; i < vec.size(); ++i)
    {
        Domino curTile = vec[i];
        if (!vec[i].in)
        {
            if ((prevL != -1) && (prevR != -1))
            {
                if (curTile.left == prevR)
                {
                    vec[i].in = true;
                    ++curL;
                    curVec.push_back(curTile);
                    find_max_len(vec, curL, maxL, curVec, maxVec, prevL, curTile.right);
                    curVec.pop_back();
                    --curL;
                    vec[i].in = false;
                }
                if (curTile.right == prevR)
                {
                    swap(curTile.left, curTile.right);
                    vec[i].in = true;
                    ++curL;
                    curVec.push_back(curTile);
                    find_max_len(vec, curL, maxL, curVec, maxVec, prevL, curTile.right);
                    curVec.pop_back();
                    --curL;
                    vec[i].in = false;
                }
                if (curTile.left == prevL)
                {
                    swap(curTile.left, curTile.right);
                    vec[i].in = true;
                    ++curL;
                    curVec.insert(curVec.begin(), curTile);
                    find_max_len(vec, curL, maxL, curVec, maxVec, curTile.left, prevR);
                    curVec.pop_back();
                    --curL;
                    vec[i].in = false;
                }
                if (curTile.right == prevL)
                {
                    vec[i].in = true;
                    ++curL;
                    curVec.insert(curVec.begin(), curTile);
                    find_max_len(vec, curL, maxL, curVec, maxVec, curTile.left, prevR);
                    curVec.pop_back();
                    --curL;
                    vec[i].in = false;
                }
            }
            else
            {
                vec[i].in = true;
                ++curL;
                curVec.insert(curVec.begin(), curTile);
                find_max_len(vec, curL, maxL, curVec, maxVec, curTile.left, curTile.right);
                curVec.pop_back();
                --curL;
                vec[i].in = false;
            }
        }
        
        

    }
}

// обёртка для вызова основной функции
vector<Domino> task1(vector<Domino>& vec)
{
    int maxL = 0, curL = 0;
    vector<Domino> curVec;
    vector<Domino> MaxVec;
    find_max_len(vec, curL, maxL, curVec, MaxVec, -1, -1);
    return MaxVec;
}
int main()
{
    vector<Domino> dominos = { Domino(1,2), Domino(3,4), Domino(4,3), Domino(4,2), Domino(5,1), Domino(5,6)};
    vector<Domino> maxTile = task1(dominos);
    for (auto item : maxTile)
    {
        cout << "(" << item.left << "," << item.right << ")" << " ";
    }

}

