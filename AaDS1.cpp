#include <iostream>
using namespace std;

void hanoi(int discCount, int from, int to)
{
    if (discCount == 1)
        cout << "����������� ���� 1 � " << from << " �� " << to << " ��������\n";
    else
    {
        int tmp = 6 - from - to;
        hanoi(discCount - 1, from, tmp);
        cout << "����������� ���� " << discCount << " � " << from << " �� " << to << " ��������\n";
        hanoi(discCount - 1, tmp, to);
    }

    return;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int N;
    cout << "������� ����� ������ N: ";
    while (true)
    {
        cin >> N;

        if (cin.fail() || N <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "�������� ����. ������� ����� N ������: ";
        }
        else
            break;
    }

    int i;
    cout << "������� ����� ���������� ������� i: ";
    while (true)
    {
        cin >> i;

        if (cin.fail() || i < 1 || i > 3)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "�������� ����. ������� ����� i ������: ";
        }
        else
            break;
    }

    int k;
    cout << "������� ����� ��������� ������� k: ";
    while (true)
    {
        cin >> k;

        if (cin.fail() || k < 1 || k > 3 || k == i)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "�������� ����. ������� ����� k ������: ";
        }
        else
            break;
    }

    cout << endl;

    hanoi(N, i, k);

    return 0;
}