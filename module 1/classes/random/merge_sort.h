//
// Created by dmitry on 28.03.2024.
//

#ifndef MODULE_1_MERGE_SORT_H
#define MODULE_1_MERGE_SORT_H

#include "../vector/vector.h"
#include "functor.h"

struct line {
    int start;
    int end;
};

template<typename T, class Compare = BaseFunctor<T>>
void merge(vector<T> &original, const line &left, const line &right, Compare cmp = BaseFunctor<T>()) {
    int l_ptr = 0, r_ptr = 0;
    vector<T> left_buf, right_buf;
    for (int i = left.start; i <= left.end; ++i) {
        left_buf.push_back(original[i]);
    }
    for (int i = right.start; i <= right.end; ++i) {
        right_buf.push_back(original[i]);
    }


    for (int i = left.start; i <= right.end; ++i) {
        if (l_ptr >= left_buf.size()) {
            original[i] = right_buf[r_ptr++];
        } else if (r_ptr >= right_buf.size()) {
            original[i] = left_buf[l_ptr++];
        } else if (cmp(left_buf[l_ptr], right_buf[r_ptr])) {
            original[i] = left_buf[l_ptr++];

        } else {
            original[i] = right_buf[r_ptr++];
        }
    }
}

template<typename T, class Compare = BaseFunctor<T>>
void mergeSort(vector<T> &array, Compare cmp = BaseFunctor<T>()) {
    int split_size = 1, size = array.size();

    while (split_size < size) {
        for (int i = 0; i < size - split_size; i += 2 * split_size) {
            merge(
                    array,
                    {i, i + split_size - 1},
                    {i + split_size, std::min(i + 2 * split_size - 1, size - 1)},
                    cmp
            );
        }
        split_size *= 2;
    }
}

#endif //MODULE_1_MERGE_SORT_H
