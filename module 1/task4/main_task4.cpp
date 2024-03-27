#include <iostream>
#include "../classes/functor/functor.h"
#include "../classes/heap/heap.h"
#include "../classes/pair/pair.h"
#include "../classes/vector/vector.h"

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
    bool isOver() const{
        return ptr == arr.size();
    }

    T& getThis() const{
        return arr[ptr];
    }
    T& getNext(){
        return arr[++ptr];
    }
};


int main() {
    heap<pair<int, int>, PairFunctor<int, int>> h;  // пара из значения и массива, где мы смещаем указатель

}