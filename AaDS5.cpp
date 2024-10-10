#include <iostream>
#include <climits>

using namespace std;

const int VERT = 8;
int infCost = 1e9;
int visited[VERT];

int componentSv(int i)
{
    while (visited[i] != i)
    {
        i = visited[i];
    }
    return i;
}

void componentsToUnion(int i, int j)
{
    int a = componentSv(i);
    int b = componentSv(j);
    visited[a] = b;
}

void KrasklAlg(int graph[VERT][VERT])
{
    int min;
    int edgesCount = 0;
    for (int i = 0; i < VERT; i++)
    {
        visited[i] = i;
    }

    while (edgesCount < VERT - 1)
    {
        min = infCost;
        int a = infCost, b = infCost;
        for (int i = 0; i < VERT; i++)
        {
            for (int j = 0; j < VERT; j++)
            {
                if (componentSv(i) != componentSv(j) && graph[i][j] < min && graph[i][j] != 0)
                {
                    min = graph[i][j];
                    a = i;
                    b = j;
                }
            }
        }
        componentsToUnion(a, b);
        edgesCount++;
        cout << a + 1 << " - " << b + 1 << " :  " << graph[a][b] << endl;
    }
}

void PrimsAlg(int graph[VERT][VERT], int startVertex)
{
    bool visited[VERT] = { false };
    visited[startVertex] = true;
    int edgesCount = 0;

    while (edgesCount < VERT - 1)
    {
        int min = infCost;
        int a = -1, b = -1;

        for (int i = 0; i < VERT; i++)
        {
            if (visited[i])
            {
                for (int j = 0; j < VERT; j++)
                {
                    if (!visited[j] && graph[i][j] < min && graph[i][j] != 0)
                    {
                        min = graph[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }

        if (a != -1 && b != -1)
        {
            cout << a + 1 << " - " << b + 1 << " : " << graph[a][b] << endl;
            visited[b] = true;
            edgesCount++;
        }
    }
}

int main()
{
    setlocale(0, "Russian");
    int graph[VERT][VERT] =
    {
        {0, 2, INT_MAX, 8, 2, INT_MAX, INT_MAX, INT_MAX},
        {2, 0, 3, 10, 5, INT_MAX, INT_MAX, INT_MAX},
        {INT_MAX, 3, 0, INT_MAX, 12, INT_MAX, INT_MAX, 7},
        {8, 10, INT_MAX, 0, 14, 3, 1, INT_MAX},
        {2, 5, 12, 14, 0, 11, 4, 8},
        {INT_MAX, INT_MAX, INT_MAX, 3, 11, 0, 6, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, 1, 4, 6, 0, 9},
        {INT_MAX, INT_MAX, 7, INT_MAX, 8, INT_MAX, 9, 0}
    };

    cout << "Алгоритм Прима: " << endl;
    cout << "Введите начальную вершину (1 - 8): ";
    int startVertex;
    cin >> startVertex;
    startVertex--; 

    cout << "Путь" << "  : " << "Вес" << endl;
    PrimsAlg(graph, startVertex);

    cout << "Алгоритм Краскала: " << endl;
    cout << "Путь" << "  : " << "Вес" << endl;
    KrasklAlg(graph);



    return 0;
}
