#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <Windows.h>

using namespace std;

struct Item {
    string name;
    int weight;
    int value;
};

void knapsack(const vector<Item>& items, int W) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    vector<vector<bool>> selected(n + 1, vector<bool>(W + 1, false));

    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= W; ++w) {
            if (items[i - 1].weight <= w) {
                int newValue = items[i - 1].value + dp[i - 1][w - items[i - 1].weight];

                if (newValue > dp[i - 1][w]) {
                    dp[i][w] = newValue;
                    selected[i][w] = true;
                }
                else {
                    dp[i][w] = dp[i - 1][w];
                    selected[i][w] = false;
                }
            }
            else {
                dp[i][w] = dp[i - 1][w];
                selected[i][w] = false;
            }
        }
    }

    vector<Item> selectedItems;
    int i = n, w = W;

    while (i > 0 && w > 0) {
        if (selected[i][w]) {
            selectedItems.push_back(items[i - 1]);
            w -= items[i - 1].weight;
        }
        --i;
    }

    cout << "Предметы, включенные в рюкзак:\n";
    for (int i = selectedItems.size() - 1; i >= 0; --i) {
        cout << "Название: " << selectedItems[i].name
            << ", Вес: " << selectedItems[i].weight
            << ", Значение: " << selectedItems[i].value << endl;
    }

    cout << "Максимальная ценность: " << dp[n][W] << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Item> items;
    string name;
    int weight, value, maxWeight;

    cout << "Введите максимальный вес рюкзака: ";
    cin >> maxWeight;

    cout << "Введите предметы (название вес стоимость), прекратите ввод, введя 'end':\n";
    while (true) {
        cin >> name;
        if (name == "end") break;
        cin >> weight >> value;

        if (cin.fail() ||  weight <= 0 || value <= 0) {
            cout << "Ошибка: вес и стоимость должны быть положительными целыми числами.\n";
            cin.clear();
            continue;
        }

        items.push_back({ name, weight, value });
    }

    if (cin.fail() || maxWeight <= 0) {
        cout << "Ошибка: максимальный вес должен быть положительным числом.\n";
        return 1;
    }

    knapsack(items, maxWeight);

    return 0;
}