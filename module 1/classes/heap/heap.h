//
// Created by dmitry on 21.03.2024.
//

#ifndef MODULE_1_HEAP_H
#define MODULE_1_HEAP_H

//#include "../vector/vector.h"
#include <iostream>
#include "../vector/vector.h"
#include "../functor/functor.h"


template <typename T, class Compare = BaseFunctor<T>>
class heap{
    Compare cmp;
    vector<T> data;
    void siftDown(int index){
        T leftSon = 2 * index + 1;
        T rightSon = 2 * index + 2;

        int minIndex = index;
        if (leftSon < data.size() && cmp(data[leftSon], data[minIndex]))
            minIndex = leftSon;

        if (rightSon < data.size() && cmp(data[rightSon], data[minIndex]))
            minIndex = rightSon;

        if (minIndex != index){
            std::swap(data[index], data[minIndex]);
            siftDown(minIndex);
        }

    }
    void siftUp(int index){
        while (index > 0){
            int parent = (index - 1) / 2;
            if (!cmp(data[index], data[parent]))
                return;

            std::swap(data[parent], data[index]);
            index = parent;
        }
    }
    void buildHeap(){
        for (int i = data.size()/2 - 1; i>= 0; --i){
            siftDown(i);
        }
    }
public:
    heap() = default;
    heap(const Compare& cmp) : cmp(cmp){}
    void out(){
        while (data.size()){
            std::cout << ExtractHead() << " ";
        }
        std::cout << std::endl;
    }
    void insert(T elem){
        data.push_back(elem);
        siftUp(data.size()-1);
    }
    T PeekHead() const{
        return data[0];
    }
    T ExtractHead(){
        std::swap(data[0], data[data.size() - 1]);
        auto head = data[data.size() - 1];

        data.pop_back();
        siftDown(0);
        return head;
    }
};


#endif //MODULE_1_HEAP_H
