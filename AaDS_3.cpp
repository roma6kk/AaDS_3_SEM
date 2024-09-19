#include <iostream>
using namespace std;
const int V = 9;

void Dijkstra(int GR[V][V], int st);

int main()
{
	setlocale(LC_ALL, "Rus");
	int start;
	int GR[V][V] = {
			{0,  7,  10, 0,  0,  0,  0 , 0,  0},
			{7,  0,  0,  0,  0,  9,  27, 0,  0},
			{10, 0,  0,  0,  31, 8,  0,  0,  0},
			{0,  0,  0,  0,  32, 0,  0,  17, 21},
			{0,  0,  31, 32, 0,  0,  0,  0,  0},
			{0,  9,  8,  0,  0,  0,  0,  11, 0},
			{0,  27, 0,  0,  0,  0,  0,  0,  15},
			{0,  0,  0,  17, 0,  11, 0,  0,  15},
			{0,  0,  0,  21, 0,  0,  15, 15, 0} };
	
	char symb[40];
	bool pr = false;
    cout << "Введите начальную вершину: ";
	while (pr == false) {
		cin >> symb;
		if (symb[1] == '\0' && (symb[0] == 'A' || symb[0] == 'B' || symb[0] == 'C' ||
			symb[0] == 'D' || symb[0] == 'E' || symb[0] == 'F' ||
			symb[0] == 'G' || symb[0] == 'H' || symb[0] == 'I'))
			pr = true;
		else
			cout << "Неверный ввод. Введите ещё раз: ";
	}
	int letter = (int)symb[0] - 65;
	Dijkstra(GR, letter);
}
void Dijkstra(int GR[V][V], int st) {
    int distance[V], index, u, m = st + 1;
    bool visited[V];

    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }
    distance[st] = 0;

    for (int count = 0; count < V - 1; count++) {
        int min = INT_MAX;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && distance[i] <= min) {
                min = distance[i];
                index = i;
            }
        }
        u = index;
        visited[u] = true;

        for (int i = 0; i < V; i++) {
            if (!visited[i] && GR[u][i] && distance[u] != INT_MAX && distance[u] + GR[u][i] < distance[i]) {
                distance[i] = distance[u] + GR[u][i];
            }
        }
    }

    cout << "Длина маршрутов:\n";
    for (int i = 0; i < V; i++) {
        if (distance[i] != INT_MAX)
            cout << "Из вершины " << (char)(m + 64) << " в " << (char)(i + 65) << " : " << distance[i] << endl;
        else
            cout << "Из вершины " << (char)(m + 64) << " в " << (char)(i + 65) << " : недоступен" << endl;
    }
}