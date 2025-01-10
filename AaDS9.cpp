#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <cstdlib>
#include <ctime>
#include <string>
/*
1 - 

*/
using namespace std;

#define V 10
int currentV = 8;
double mutationRate = 0.1;
int populationSize;
int child;
int evoCount;

struct individual {
    string gnome;
    int fitness;
};

int cities[V][V] = {
    { INT_MAX, 2, 4, 3, 2, 10, 5, 9, INT_MAX, INT_MAX },
    { 5, INT_MAX, 17, 30, 25, 15, 2, 10, INT_MAX, INT_MAX },
    { 9, 15, INT_MAX, 6, 1, 20, 3, 2, INT_MAX, INT_MAX },
    { 9, 5, 4, INT_MAX, 6, 10, 5, 9, INT_MAX, INT_MAX },
    { 2, 8, 7, 10, INT_MAX, 5, 20, 1, INT_MAX, INT_MAX },
    { 10, 5, 2, 10, 15, INT_MAX, 7, 3, INT_MAX, INT_MAX },
    { 5, 2, 3, 5, 2, 1, INT_MAX, 6, INT_MAX, INT_MAX },
    { 9, 10, 2, 9, 10, 3, 6, INT_MAX, INT_MAX, INT_MAX }
};

int rand_num(int start, int end) {
    return start + rand() % (end - start);
}

bool repeat(string s, char ch) {
    return s.find(ch) != string::npos;
}

string create_gnome() {
    string gnome = "0";
    while (gnome.size() < currentV) {
        int temp = rand_num(1, currentV);
        if (!repeat(gnome, temp + '0')) {
            gnome += (temp + '0');
        }
    }
    gnome += gnome[0];
    return gnome;
}

int cal_fitness(string gnome) {
    int f = 0;
    for (int i = 0; i < gnome.size() - 1; i++) {
        int from = gnome[i] - '0';
        int to = gnome[i + 1] - '0';
        if (cities[from][to] == INT_MAX) return INT_MAX;
        f += cities[from][to];
    }
    return f;
}

string crossover(string parent1, string parent2) {

    string child = parent1.substr(0, 2);


    for (size_t i = 2; i < parent2.size(); ++i) {
        char city = parent2[i];
        if (child.size() < parent1.size() && !repeat(child, city)) {
            child += city;
        }
    }


    for (size_t i = 0; i < parent1.size(); ++i) {
        char city = parent1[i];
        if (child.size() < parent1.size() && !repeat(child, city)) {
            child += city;
        }
    }


    if (!child.empty() && child[0] != child.back()) {
        child += child[0];
    }

    return child;
}

string mutatedGene(string gnome) {
    if (static_cast<double>(rand()) / RAND_MAX <= mutationRate) {
        int r = rand_num(1, currentV - 1);
        int r1 = rand_num(1, currentV - 1);
        if (r1 != r) {
            swap(gnome[r], gnome[r1]);
        }
    }
    return gnome;
}

bool lessthan(struct individual t1, struct individual t2) {
    return t1.fitness < t2.fitness;
}

void printGraph() {
    cout << "\nТекущий граф:\n";
    for (int i = 0; i < currentV; i++) {
        for (int j = 0; j < currentV; j++) {
            if (cities[i][j] != INT_MAX) {
                cout << "Город " << i << " - Город " << j << ": " << cities[i][j] << "\n";
            }
        }
    }
}

void Genetic_algo() {
    vector<individual> population;
    for (int i = 0; i < populationSize; i++) {
        individual temp;
        temp.gnome = create_gnome();
        temp.fitness = cal_fitness(temp.gnome);
        population.push_back(temp);
    }

    int gen = 1;

    while (gen <= evoCount) {
        sort(population.begin(), population.end(), lessthan);

        cout << "\nПоколение " << gen << ":\n";
        for (const auto& ind : population) {
            cout << "Индивид: " << ind.gnome << " | Путь: " << ind.fitness << "\n";
        }

        cout << "\nЛучший индивид в поколении " << gen << ": " << population[0].gnome
            << " | Путь: " << population[0].fitness << "\n";

        vector<individual> new_population;
        for (int i = 0; i < child; i++) {
            individual parent1 = population[rand_num(0, populationSize)];
            individual parent2 = population[rand_num(0, populationSize)];

            string new_gnome = crossover(parent1.gnome, parent2.gnome);
            new_gnome = mutatedGene(new_gnome);

            individual new_ind;
            new_ind.gnome = new_gnome;
            new_ind.fitness = cal_fitness(new_gnome);
            new_population.push_back(new_ind);
        }
        for (const auto& ind : new_population) {
            population.push_back(ind);
        }

        sort(population.begin(), population.end(), lessthan);
        population.resize(populationSize);
        gen++;
    }

    cout << "\nИтоговый индивид: " << population[0].gnome
        << " | Путь индивида: " << population[0].fitness << "\n";
}

void editGraph() {
    int choice;
    do {
        cout << "\nМеню редактирования:\n";
        cout << "1. Добавить город\n";
        cout << "2. Удалить город\n";
        cout << "3. Добавить дорогу\n";
        cout << "4. Удалить дорогу\n";
        cout << "5. Вернуться в главное меню\n";
        cout << "6. Показать граф\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            if (currentV >= V) {
                cout << "Невозможно добавить больше городов\n";
            }
            else {
                int newCity = currentV;
                for (int i = 0; i < currentV; i++) {
                    cities[i][newCity] = INT_MAX;
                    cities[newCity][i] = INT_MAX;
                }

                for (int i = 0; i < currentV; i++) {
                    int weight;
                    cout << "Введите расстояние от города " << i << " до нового города " << newCity << ": ";
                    cin >> weight;

                    cities[i][newCity] = weight;
                    cout << "Введите расстояние от нового города " << newCity << " до города " << i << ": ";
                    cin >> weight;
                    cities[newCity][i] = weight;
                }

                currentV++;
                cout << "Город добавлен. Текущее количество городов: " << currentV << ".\n";
            }
            break;
        }
        case 2:
            if (currentV <= 2) {
                cout << "Невозможно удалить последний город.\n";
            }
            else {
                currentV--;
                cout << "Город удалён. Текущее количество городов: " << currentV << ".\n";
            }
            break;

        case 3: {
            int from, to, weight1, weight2;
            cout << "Введите начальный город, конечный город и расстояние (от начального до конечного): ";
            cin >> from >> to >> weight1;

            if (from < currentV && to < currentV) {
                cout << "Введите расстояние (от конечного до начального): ";
                cin >> weight2;

                cities[from][to] = weight1;
                cities[to][from] = weight2;
                cout << "Дорога добавлена между городами " << from << " и " << to << ".\n";
            }
            else {
                cout << "Недопустимые номера городов.\n";
            }
            break;
        }
        case 4: {
            int from, to;
            cout << "Введите начальный и конечный город: ";
            cin >> from >> to;
            if (from < currentV && to < currentV) {
                cities[from][to] = INT_MAX;
                cities[to][from] = INT_MAX;
                cout << "Дорога удалена между городами " << from << " и " << to << ".\n";
            }
            else {
                cout << "Недопустимые номера городов.\n";
            }
            break;
        }

        case 5:
            cout << "Возвращение в главное меню.\n";
            break;

        case 6:
            printGraph();
            break;

        default:
            cout << "Недопустимый ввод.\n";
        }
    } while (choice != 5);
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    do {
        cout << "Введите размер популяции: ";
        cin >> populationSize;
    } while (populationSize <= 0);

    do {
        cout << "Введите количество потомков: ";
        cin >> child;
    } while (child <= 0);

    do {
        cout << "Введите количество поколений: ";
        cin >> evoCount;
    } while (evoCount <= 0);
    cout << "Введите вероятность мутации (от 0 до 1): ";
    cin >> mutationRate;
    if (mutationRate < 0 || mutationRate > 1) {
        cout << "Недопустимое значение для вероятности мутации.\n";
        return 1;
    }
    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Редактировать граф\n";
        cout << "2. Запустить генетический алгоритм\n";
        cout << "3. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            editGraph();
            break;
        case 2:
            Genetic_algo();
            break;
        case 3:
            cout << "Завершение программы.\n";
            break;
        default:
            cout << "Недопустимый ввод.\n";
        }
    } while (choice != 3);

    return 0;
}