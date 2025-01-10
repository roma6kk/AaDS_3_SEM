#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <Windows.h>
#include <ctime>

using namespace std;

bool randomSelection(const vector<int>& boxes) {
    for (int i = 0; i < 100; i++) {
        vector<bool> checked(100, false);
        int found = 0;

        for (int j = 0; j < 50; j++) {
            int r = rand() % 100; // Случайный выбор коробки
            if (!checked[r]) {
                checked[r] = true;
                if (boxes[r] == i + 1) {
                    found = 1; // Заключенный нашел свой номер
                    break;
                }
            }
        }

        if (found == 0) {
            return false; // Если хотя бы один не нашел, возвращаем false
        }
    }
    return true; // Все нашли свои номера
}

bool boxNumberSelection(const vector<int>& boxes) {
    for (int i = 0; i < 100; i++) {
        int currentBox = i; // Начинаем с коробки, соответствующей номеру заключенного
        vector<bool> checked(100, false);
        int found = 0;

        for (int j = 0; j < 50; j++) {
            if (checked[currentBox]) break; // Если уже открывали эту коробку
            checked[currentBox] = true;

            if (boxes[currentBox] == i + 1) {
                found = 1; // Заключенный нашел свой номер
                break;
            }
            currentBox = boxes[currentBox] - 1; // Переход к следующей коробке
        }

        if (found == 0) {
            return false; // Если хотя бы один не нашел, возвращаем false
        }
    }
    return true; // Все нашли свои номера
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned int>(time(0)));

    int rounds;
    cout << "Введите количество раундов сравнений: ";
    cin >> rounds;

    int randomSuccess = 0;
    int numberSelectionSuccess = 0;

    for (int r = 0; r < rounds; r++) {
        vector<int> boxes(100);
        for (int i = 0; i < 100; i++) {
            boxes[i] = i + 1; // Заполнение номерами 1-100
        }
        random_shuffle(boxes.begin(), boxes.end()); // Перемешивание коробок

        // Проверка случайного выбора
        if (randomSelection(boxes)) {
            randomSuccess++;
        }

        // Проверка выбора по номеру
        if (boxNumberSelection(boxes)) {
            numberSelectionSuccess++;
        }
    }

    cout << "Случайным способом: " << randomSuccess << " успешных исходов\n";
    cout << "Выбором номера в коробке: " << numberSelectionSuccess << " успешных исходов\n";

    return 0;
}
