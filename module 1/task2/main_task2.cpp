#include <iostream>
#include "../vector/vector.h"

class SearchIntersection{
private:
    vector<int> A;
    vector<int> B;
    vector<int> answer;

    // принимает сам массив, диапазон и число, которое ищем
    int binSearch(int num, const std::pair<int, int> &scope) {
        auto l = scope.first, r = scope.second;

        while (l < r) {
            auto m = (l + r) / 2;
            if (A[m] > num)
                r = m;
            else
                l = m+1;
        }
        if (A[l-1] == num)
            return l-1;

        return -1;
    }

    int expSearch(int num) {
        if (A.size() == 0) {
            return -1;
        }

        auto range = 1;
        while (range < A.size() && A[range] < num) {
            range *= 2;
        }

        auto end = std::min(range + 1, (int)A.size());

        return binSearch(num, {range / 2, end});
    }
    void Intersection() {
        for (int i = 0; i < B.size(); ++i) {
            auto ind = expSearch(B[i]);
            if (ind == -1)
                continue;

            answer.push_back(A[ind]);
        }

    }
public:
    SearchIntersection(std::istream &in, std::ostream &out){
        int N1, N2;
        in >> N1;
        in >> N2;

        A.input(in, N1);
        B.input(in, N2);

        Intersection();

        answer.out(out);
    }
};


int main() {
   SearchIntersection Ans(std::cin, std::cout);
}