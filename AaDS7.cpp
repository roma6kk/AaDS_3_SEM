#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> LIS(const std::vector<int>& sequence) {
    if (sequence.empty()) return {};

    std::vector<int> lengths(sequence.size(), 1);
    std::vector<int> previous(sequence.size(), -1);

    for (size_t i = 1; i < sequence.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (sequence[i] > sequence[j] && lengths[i] < lengths[j] + 1) {
                lengths[i] = lengths[j] + 1;
                previous[i] = j;
            }
        }
    }

    int maxLength = 0;
    int maxIndex = 0;
    for (size_t i = 0; i < lengths.size(); ++i) {
        if (lengths[i] > maxLength) {
            maxLength = lengths[i];
            maxIndex = i;
        }
    }

    std::vector<int> lis;
    for (int i = maxIndex; i != -1; i = previous[i]) {
        lis.push_back(sequence[i]);
    }

    std::reverse(lis.begin(), lis.end());
    return lis;
}

int main() {
    setlocale(0, "rus");
    int N;
    std::cout << "Введите количество элементов: ";
    std::cin >> N;

    std::vector<int> sequence(N);
    std::cout << "Введите элементы последовательности: ";
    for (int i = 0; i < N; ++i) {
        std::cin >> sequence[i];
    }

    std::vector<int> lis = LIS(sequence);

    std::cout << "Длина максимальной возрастающей подпоследовательности: " << lis.size() << std::endl;
    std::cout << "Одна из таких подпоследовательностей: ";
    for (int num : lis) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}