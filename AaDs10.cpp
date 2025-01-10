#include <iostream>
#include <Windows.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int n;
double alpha;
double beta;
int iter;
double evaporationPercentage;
double amountOfPheromonesFromOneAnt;
int amountOfAnts = 1;
vector<vector<int>> matrix;
vector<vector<double>> pheromones;

double calculatePathLength(const vector<int>& path) {
    double length = 0.0;
    for (int i = 0; i < path.size() - 1; i++) {
        length += matrix[path[i]][path[i + 1]];
    }
    length += matrix[path.back()][path[0]];
    return length;
}

void changePheromones(const vector<vector<int>>& paths) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pheromones[i][j] *= (1 - evaporationPercentage);
        }
    }

    for (const auto& path : paths) {
        double length = calculatePathLength(path);
        for (int i = 0; i < path.size() - 1; i++) {
            pheromones[path[i]][path[i + 1]] += amountOfPheromonesFromOneAnt / length;
            pheromones[path[i + 1]][path[i]] += amountOfPheromonesFromOneAnt / length;
        }
        pheromones[path.back()][path[0]] += amountOfPheromonesFromOneAnt / length;
        pheromones[path[0]][path.back()] += amountOfPheromonesFromOneAnt / length;
    }
}

void printAdjacencyMatrix() {
    cout << "Матрица смежности:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void printDistances() {
    cout << "Расстояния между городами:\n";
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Расстояние от города " << i + 1 << " до города " << j + 1 << ": "
                << matrix[i][j] << endl;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Введите количество городов: ";
    cin >> n;

    // Генерация случайных расстояний между городами
    matrix.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0; // Расстояние до самого себя
            }
            else if (i < j) {
                // Генерируем расстояние только для верхней половины матрицы
                matrix[i][j] = rand() % 100 + 1; // Случайное расстояние от 1 до 100
                matrix[j][i] = matrix[i][j]; // Делаем расстояние симметричным
            }
        }
    }

    printAdjacencyMatrix();
    printDistances(); // Вывод расстояний между городами

    cout << "Введите значение альфа: ";
    cin >> alpha;
    cout << "Введите значение бета: ";
    cin >> beta;
    cout << "Введите количество итераций: ";
    cin >> iter;

    pheromones.resize(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                pheromones[i][j] = 1.0; // Инициализация феромонов
            }
        }
    }

    cout << "Введите коэффициент испарения феромонов за цикл (<1): ";
    cin >> evaporationPercentage;
    cout << "Введите количество феромонов, оставляемое одним муравьем: ";
    cin >> amountOfPheromonesFromOneAnt;

    int thebestlength = 10000000;
    vector<int> thebestpath(n);

    for (int i = 0; i < iter; i++) {
        vector<vector<int>> paths(amountOfAnts, vector<int>(n));
        for (int cur_ant = 0; cur_ant < amountOfAnts; cur_ant++) {
            vector<bool> visited(n, false);
            int startCity = rand() % n;
            paths[cur_ant][0] = startCity;
            visited[startCity] = true;

            for (int phase = 1; phase < n; phase++) {
                int currentCity = paths[cur_ant][phase - 1];
                double totalProbability = 0.0;
                vector<double> probabilities(n, 0.0); 
                for (int cur_city = 0; cur_city < n; cur_city++) {
    if (!visited[cur_city] && matrix[currentCity][cur_city] > 0) {
        probabilities[cur_city] = pow(pheromones[currentCity][cur_city], alpha) *
            pow(1.0 / matrix[currentCity][cur_city], beta);
        totalProbability += probabilities[cur_city];
    }
}

double randomValue = (double)rand() / RAND_MAX * totalProbability;
for (int cur_city = 0; cur_city < n; cur_city++) {
    if (!visited[cur_city] && matrix[currentCity][cur_city] > 0) {
        randomValue -= probabilities[cur_city];
        if (randomValue <= 0) {
            paths[cur_ant][phase] = cur_city;
            visited[cur_city] = true;
            break;
        }
    }
}
            }
        }

        double bestLength = 10000000;
        vector<int> bestPath;

        for (const auto& path : paths) {
            double length = calculatePathLength(path);
            if (length < bestLength) {
                bestLength = length;
                bestPath = path;
            }
        }

        if (thebestlength > bestLength) {
            thebestlength = bestLength;
            thebestpath = bestPath;
        }

        cout << "Текущая итерация " << i + 1 << '\n';
        cout << "Лучший путь: ";
        for (int city : thebestpath) {
            cout << city + 1 << " ";
        }
        cout << "\nДлина пути: " << thebestlength << '\n';
        changePheromones(paths);
    }

    return 0;
}