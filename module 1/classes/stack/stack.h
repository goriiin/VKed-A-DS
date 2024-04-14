//
// Created by dmitry on 19.03.2024.
//

#ifndef MODULE_1_STACK_H
#define MODULE_1_STACK_H

#include "../vector/vector.h"

template<typename T>
class stack {
    vector<T> data;
public:
    void push(T num) {
        data.push_back(num);
    }

    T pop() {
        auto num = data[data.size() - 1];
        data.pop_back();

        return num;
    }

    T top(){
        return data[data.size()-1];
    }

    T size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }
};

#endif //MODULE_1_STACK_H
