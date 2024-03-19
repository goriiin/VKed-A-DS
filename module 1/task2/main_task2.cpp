#include <iostream>
#include "../vector/vector.h"

// принимает сам массив, диапазон и число, которое ищем
int binSearch(const vector<int> &vec, int num, const std::pair<int, int> &scope) {
    int l = scope.first, r = scope.second;
    while (l < r) {
        auto m = (l + r) / 2;
        if (vec[m] > num)
            r = m;
        else
            l = m+1;
    }
    if (vec[l-1] == num)
        return l-1;

    return -1;
}

int expSearch(const vector<int> &vec, int num) {
    if (vec.size() == 0) {
        return -1;
    }
    int range = 1;
    while (range < vec.size() && vec[range] < num) {
        range *= 2;
    }

    return binSearch(vec, num, {range / 2, std::min(range + 1, (int)vec.size())});
}

void Search(const vector<int> &A, const vector<int> &B, vector<int> &ans) {
    for (int i = 0; i < B.size(); ++i) {
        auto ind = expSearch(A, B[i]);
        if (ind == -1)
            continue;
        ans.push_back(A[ind]);
    }
}

int main() {
    int N1, N2;
    std::cin >> N1;
    std::cin >> N2;

    vector<int> A, B, answer;
    A.input(std::cin, N1);
    B.input(std::cin, N2);


    Search(A, B, answer);
    answer.out(std::cout);
}