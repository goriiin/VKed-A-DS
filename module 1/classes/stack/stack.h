//
// Created by dmitry on 19.03.2024.
//

#ifndef MODULE_1_STACK_H
#define MODULE_1_STACK_H


#include "../vector/vector.h"

class stack {
    vector<int> data;
public:
    void push(int num);
    int pop();
    int size() const;
    bool empty() const;
};

void stack::push(int num) {
    data.push_back(num);
}

int stack::pop() {
    if (data.size() == 0)
        return -1;
    auto num = data[data.size()-1];
    data.pop_back();

    return num;
}

int stack::size() const{
    return data.size();
}

bool stack::empty() const{
    return data.empty();
}

#endif //MODULE_1_STACK_H
