//
// Created by dmitry on 03.04.2024.
//

#ifndef MODULE_1_PARTITION_H
#define MODULE_1_PARTITION_H

#include "../vector/vector.h"
#include "functor.h"


// Ищем медиану 3х чисел в диапазоне
template <typename T, class Comparator = BaseFunctor<T>>
int med(vector<T>& arr, int l, int r, Comparator cmp = Comparator()){
    T a = arr[l], b = arr[r], c = arr[(r-l)/2];

    // b < a
    if (cmp(b, a)){
        // a < c
        if (cmp(a, c))
            // b < a < c
            return l;
        // b < c < a
        return (r-l)/2;
    }
    if (cmp(b,c))
        // a < b < c
        return r;

    // находим меньшее
    return (cmp(c, a) ? l:(r-l)/2);
}

template <typename T, class Comparator = BaseFunctor<T>>
int partition(vector<T>& arr, int l, int r, Comparator cmp = Comparator()) {
    if (r-l == 0)
        return 0;

    std::swap( arr[r-1], arr[med(arr,l,r,cmp)] );
    T& pivot = arr[r-1];
    // i -- начало, j -- конец группы > pivot
    int i = l, j = l+1;

    // пока не дойдем до элемента предшетствующего pivot
    while (j != r-2){
        if (cmp(pivot, arr[j]))
            ++j;
        else if (cmp(arr[j] < pivot)){
            std::swap(arr[i], arr[j]);
            ++j;
            ++i;
        }
    }

    std::swap( arr[i], arr[r - 1] );
    return i;
}
#endif //MODULE_1_PARTITION_H
