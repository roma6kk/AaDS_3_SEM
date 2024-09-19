#include <iostream>
#include <vector>

using namespace std;

int CheckArr[10] = { false };
bool adjacencyMatrix[10][10] =
{
    {0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
};
int listOfRibsFrom[11] = { 1, 1, 2, 2, 3, 4, 4, 5, 6, 7, 9 };
int listOfRibsTo[11] = { 2, 5, 7, 8, 8, 6, 9, 6, 9, 8, 10 };
vector<vector<int>> adjacencyList(10);
void buildAdjacencyList() {
    for (int i = 0; i < 11; i++) {
        int from = listOfRibsFrom[i] - 1;
        int to = listOfRibsTo[i] - 1;
        adjacencyList[from].push_back(to);
        adjacencyList[to].push_back(from);
    }
}
void dfs(int v) {
    cout << v + 1 << ' ';
    CheckArr[v] = true;
    for (int i = 0; i < 10; i++) {
        if (adjacencyMatrix[v][i] == 1 && !CheckArr[i])
            dfs(i);
    }
}
void bfs(int start) {
    int queue[10]; 
    int front = 0, back = 0;

    queue[back++] = start;
    CheckArr[start] = true;

    while (front < back) {
        int u = queue[front++];
        cout << u + 1 << ' ';
        for (int i = 0; i < 10; i++) {
            if (!CheckArr[i] && adjacencyMatrix[u][i] == 1) {
                queue[back++] = i; 
                CheckArr[i] = true;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    buildAdjacencyList();
    cout << "Поиск в ширину через матрицу смежности: ";
    bfs(0);
    cout << "\n";
    for (int i = 0; i < 10; i++) {
        CheckArr[i] = 0;
    }
    cout << "Поиск в глубину через матрицу смежности: ";
    dfs(0);
    cout << "\n";
    return 0;
}
