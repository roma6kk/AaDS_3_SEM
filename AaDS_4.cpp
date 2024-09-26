#include<iostream>
using namespace std;
int main()
{
	setlocale(0, "rus");
	const int N = 6;
	int D[N][N] =
	{
		{0,28,21,59,12,27},
		{7,0,24,INT_MAX, 21,9},
		{9,32,0,13,11, INT_MAX},
		{8, INT_MAX, 5,0,16,INT_MAX},
		{14,13,15,10,0,22},
		{15,18,INT_MAX,INT_MAX,6,0}
	};
	int S[N][N] =
	{
		{0,2,3,4,5,6},
		{1,0,3,4,5,6},
		{1,2,0,4,5,6},
		{1,2,3,0,5,6},
		{1,2,3,4,0,6},
		{1,2,3,4,5,0}
	};
    int new_dist;
    for (int m = 0; m < N; m++) { 
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (D[i][m] != INT_MAX && D[m][j] != INT_MAX) { 
                    new_dist = D[i][m] + D[m][j];
                    if (new_dist < D[i][j]) {
                        D[i][j] = new_dist;
                        S[i][j] = S[i][m]; 
                    }
                }
            }
        }
    }

    cout << "Матрица D:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (D[i][j] == INT_MAX)
                cout << "INF ";
            else
                cout << D[i][j] << ' ';
        }
        cout << endl;
    }

    cout << "Матрица S:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << S[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}