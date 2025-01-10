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
            int r = rand() % 100; // ��������� ����� �������
            if (!checked[r]) {
                checked[r] = true;
                if (boxes[r] == i + 1) {
                    found = 1; // ����������� ����� ���� �����
                    break;
                }
            }
        }

        if (found == 0) {
            return false; // ���� ���� �� ���� �� �����, ���������� false
        }
    }
    return true; // ��� ����� ���� ������
}

bool boxNumberSelection(const vector<int>& boxes) {
    for (int i = 0; i < 100; i++) {
        int currentBox = i; // �������� � �������, ��������������� ������ ������������
        vector<bool> checked(100, false);
        int found = 0;

        for (int j = 0; j < 50; j++) {
            if (checked[currentBox]) break; // ���� ��� ��������� ��� �������
            checked[currentBox] = true;

            if (boxes[currentBox] == i + 1) {
                found = 1; // ����������� ����� ���� �����
                break;
            }
            currentBox = boxes[currentBox] - 1; // ������� � ��������� �������
        }

        if (found == 0) {
            return false; // ���� ���� �� ���� �� �����, ���������� false
        }
    }
    return true; // ��� ����� ���� ������
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned int>(time(0)));

    int rounds;
    cout << "������� ���������� ������� ���������: ";
    cin >> rounds;

    int randomSuccess = 0;
    int numberSelectionSuccess = 0;

    for (int r = 0; r < rounds; r++) {
        vector<int> boxes(100);
        for (int i = 0; i < 100; i++) {
            boxes[i] = i + 1; // ���������� �������� 1-100
        }
        random_shuffle(boxes.begin(), boxes.end()); // ������������� �������

        // �������� ���������� ������
        if (randomSelection(boxes)) {
            randomSuccess++;
        }

        // �������� ������ �� ������
        if (boxNumberSelection(boxes)) {
            numberSelectionSuccess++;
        }
    }

    cout << "��������� ��������: " << randomSuccess << " �������� �������\n";
    cout << "������� ������ � �������: " << numberSelectionSuccess << " �������� �������\n";

    return 0;
}
