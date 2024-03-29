#include <iostream>
#include "../classes/random/functor.h"
#include "../classes/heap/heap.h"
#include "../classes/pair/pair.h"


template<typename T1, typename T2>
struct PairFunctor{
    bool operator () (const pair<T1, T2>& l, const pair<T1, T2>& r){
        return l.first < r.first;
    }
};

template<typename T>
class vecWrapper{
    vector<T> arr;
    int ptr = 0;
public:
    vecWrapper() = default;
    vecWrapper(const vecWrapper& initVec) {
        arr = initVec.arr;
        ptr = initVec.ptr;
    }

    vecWrapper& operator=(const vecWrapper& vec) {
        arr = vec.arr;
        ptr = vec.ptr;
        return *this;
    }

    void input(std::istream &in, int count) {
        arr.input(in, count);
    }

    void out(std::ostream &out) const {
        arr.out(out);
    }

    int size () const {
        return arr.size();
    }

    int getNext(){
        return ((ptr < arr.size()-1)? ++ptr : -1);
    }

    T& operator [](int index) {
        return arr[index];
    }

    T& operator [](int index) const {
        return arr[index];
    }

};

void ans(std::istream &in, std::ostream &out){
    heap<pair<int, int>, PairFunctor<int, int>> Heap;  // пара из значения и массива, где мы смещаем указатель

    int count = 0;
    in >> count;
    vector<vecWrapper<int>> input;
    int sumSize = 0;
    for (int i = 0; i < count; ++i) {
        int size = 0;
        in >> size;
        vecWrapper<int> a;
        a.input(in, size);
        input.push_back(a);
        sumSize+= input[i].size();
    }


    for (int i = 0; i < count; ++i) {
        Heap.insert( pair(input[i][0], i));
    }

    vector<int> answer;
    for(int i = 0; i < sumSize; ++i){
        auto headVal = Heap.ExtractHead();
        answer.push_back(headVal.first);
        auto ind = input[headVal.second].getNext();
        if (ind >= 0){
            Heap.insert({input[headVal.second][ind], headVal.second});

        }

    }

    answer.out(out);
}


int main() {
    ans(std::cin, std::cout);
}