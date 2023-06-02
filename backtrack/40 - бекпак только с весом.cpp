#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item
{
    int weight, sell;
    bool in_bag;
    Item(int w, int s)
    {
        weight = w;
        sell = s;
        in_bag = 0;
    }
};

void func(vector<Item> &vec, int maxV, int curV, int &maxS, int curS, std::vector<Item>& currentSet, std::vector<Item>& maxSet, int curI = -1)
{
    if (curV > maxV) {
        return;
    }

    if (curS > maxS) {
        maxS = curS;
        maxSet = currentSet;
    }

    for (size_t i = 0; i < vec.size(); ++i) {
        if (!vec[i].in_bag)
        {
            Item curItem = vec[i];
            vec[i].in_bag = true;
            currentSet.push_back(curItem);
            func(vec, maxV, curV + curItem.weight, maxS, curS + curItem.sell, currentSet, maxSet, i);
            currentSet.pop_back();
            vec[i].in_bag = false;
        }
        
    }
}

std::vector<Item> findMaxValue(std::vector<Item>& items, int maxWeight) {
    int currentValue = 0;
    int currentWeight = 0;
    int maxS = 0;
    std::vector<Item> currentSet;
    std::vector<Item> maxSet;

    func(items, maxWeight, currentWeight, maxS, currentValue, currentSet, maxSet);

    return maxSet;
}

int main()
{
    setlocale(0, "ru");
    // Пример входных данных
    std::vector<Item> items = { {2, 3}, {3, 4}, {4, 5}, {5, 6} };
    int maxWeight = 10;

    std::vector<Item> maxSet = findMaxValue(items, maxWeight);

    // Выводим результат
    std::cout << "Максимальная стоимость предметов, помещающихся в рюкзак весом " << maxWeight << ":\n";
    for (const Item& item : maxSet) {
        std::cout << "Вес: " << item.weight << ", Стоимость: " << item.sell << std::endl;
    }

    return 0;
}