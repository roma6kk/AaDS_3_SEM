#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <Windows.h>

using namespace std;

struct Node {
    string symbols;
    int freq;
    Node* left;
    Node* right;

    Node(const string& s, int f) : symbols(s), freq(f), left(nullptr), right(nullptr) {}
};

struct CompareChar {
    bool operator()(Node* left, Node* right) {
        if (left->freq == right->freq) {
            return left->symbols > right->symbols;
        }
        return left->freq > right->freq;
    }
};

void generateCodes(Node* root, const string& str, unordered_map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[root->symbols[0]] = str;
    }
    generateCodes(root->left, str + "0", codes);
    generateCodes(root->right, str + "1", codes);
}

unordered_map<char, int> calculateFrequency(const string& text) {
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }
    return freq;
}

void displayVector(const vector<Node*>& vec) {
    cout << setw(7) << "Символы" << " | " << setw(5) << "Частота\n";
    for (const auto& node : vec) {
        cout << setw(7) << node->symbols << " | " << setw(5) << node->freq << '\n';
    }
    cout << "-----------------------\n";
}

Node* createHuffmanTree(const unordered_map<char, int>& freq) {
    vector<Node*> charVec;

    for (const auto& pair : freq) {
        charVec.push_back(new Node(string(1, pair.first), pair.second));
    }

    sort(charVec.begin(), charVec.end(), CompareChar());

    cout << "Начальные символы:\n";
    displayVector(charVec);

    while (charVec.size() > 1) {
        Node* left = charVec.back(); charVec.pop_back();
        Node* right = charVec.back(); charVec.pop_back();

        Node* newNode = new Node(left->symbols + right->symbols, left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        charVec.push_back(newNode);
        sort(charVec.begin(), charVec.end(), CompareChar());
    }

    return charVec.front();
}

void printTree(Node* root, int space = 0, int height = 10) {
    if (root == nullptr) return;

    space += height;
    printTree(root->right, space);

    cout << endl;
    for (int i = height; i < space; i++) {
        cout << " ";
    }
    cout << root->symbols << " (" << root->freq << ")\n";

    printTree(root->left, space);
}

void printResults(const unordered_map<char, int>& freq, const unordered_map<char, string>& codes, const string& input) {
    cout << "\nКоды символов:\n";
    for (const auto& pair : codes) {
        cout << pair.first << " : " << pair.second << "\n";
    }

    cout << "\nВыходная последовательность:\n";
    for (char ch : input) {
        cout << codes.at(ch);
    }
    cout << '\n';
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string input;
    cout << "Введите текст: ";
    getline(cin, input);

    auto freq = calculateFrequency(input);
    Node* root = createHuffmanTree(freq);

    unordered_map<char, string> codes;
    generateCodes(root, "", codes);

    cout << "\nДерево Хаффмана:\n";
    printTree(root);

    printResults(freq, codes, input);

    return 0;
}