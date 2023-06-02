#include <iostream>
#include <vector>

// Функция для проверки, можно ли раскрасить страну в данный цвет
bool isValidColor(const std::vector<std::vector<int>>& adjacencyMatrix, int country, int color, const std::vector<int>& colors) {
    // Проверяем все соседние страны
    for (int neighbor = 0; neighbor < adjacencyMatrix.size(); neighbor++) {
        if (adjacencyMatrix[country][neighbor] == 1 && colors[neighbor] == color) {
            return false; // Найден сосед с таким же цветом
        }
    }
    return true; // Все соседи имеют разные цвета
}

// Функция для раскраски карты с использованием backtracking
bool colorMapBacktracking(const std::vector<std::vector<int>>& adjacencyMatrix, int numColors, std::vector<int>& colors, int country) {
    // Базовый случай: все страны раскрашены
    if (country == adjacencyMatrix.size()) {
        return true;
    }

    // Перебираем все возможные цвета для текущей страны
    for (int color = 1; color <= numColors; color++) {
        // Проверяем, можно ли раскрасить страну в данный цвет
        if (isValidColor(adjacencyMatrix, country, color, colors)) {
            colors[country] = color; // Раскрашиваем страну
            // Рекурсивно раскрашиваем следующую страну
            if (colorMapBacktracking(adjacencyMatrix, numColors, colors, country + 1)) {
                return true; // Найдено решение
            }
            colors[country] = 0; // Отменяем раскраску текущей страны
        }
    }

    return false; // Не удалось найти решение
}

// Функция-обертка для вызова функции с использованием backtracking
std::vector<int> colorMap(const std::vector<std::vector<int>>& adjacencyMatrix, int numColors) {
    std::vector<int> colors(adjacencyMatrix.size(), 0); // Вектор для хранения цветов стран

    if (colorMapBacktracking(adjacencyMatrix, numColors, colors, 0)) {
        return colors; // Найдено решение
    }
    else {
        return std::vector<int>(); // Не удалось найти решение
    }
}

int main() {
    setlocale(0, "ru");
    // Пример входных данных
    std::vector<std::vector<int>> adjacencyMatrix = {
        {0, 1, 1, 0, 1},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}
    };

    int numColors = 3; // Количество доступных цветов

    std::vector<int> colors = colorMap(adjacencyMatrix, numColors);

    // Выводим результат раскраски карты
    if (!colors.empty()) {
        std::cout << "Результат раскраски карты:\n";
        for (int i = 0; i < colors.size(); i++) {
            std::cout << "Страна " << i + 1 << ": Цвет " << colors[i] << std::endl;
        }
    }
    else {
        std::cout << "Невозможно раскрасить карту с заданными условиями.\n";
    }

    return 0;
}
