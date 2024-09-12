#include <iostream>
using namespace std;

void hanoi(int discCount, int from, int to)
{
    if (discCount == 1)
        cout << "Переместить диск 1 с " << from << " на " << to << " стержень\n";
    else
    {
        int tmp = 6 - from - to;
        hanoi(discCount - 1, from, tmp);
        cout << "Переместить диск " << discCount << " с " << from << " на " << to << " стержень\n";
        hanoi(discCount - 1, tmp, to);
    }

    return;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int N;
    cout << "Введите число дисков N: ";
    while (true)
    {
        cin >> N;

        if (cin.fail() || N <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный ввод. Введите число N заново: ";
        }
        else
            break;
    }

    int i;
    cout << "Введите номер начального стержня i: ";
    while (true)
    {
        cin >> i;

        if (cin.fail() || i < 1 || i > 3)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный ввод. Введите число i заново: ";
        }
        else
            break;
    }

    int k;
    cout << "Введите номер конечного стержня k: ";
    while (true)
    {
        cin >> k;

        if (cin.fail() || k < 1 || k > 3 || k == i)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный ввод. Введите число k заново: ";
        }
        else
            break;
    }

    cout << endl;

    hanoi(N, i, k);

    return 0;
}