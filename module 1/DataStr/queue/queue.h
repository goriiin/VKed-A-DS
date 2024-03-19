//
// Created by dmitry on 19.03.2024.
//

#ifndef MODULE_1_QUEUE_H
#define MODULE_1_QUEUE_H
#include "../stack/stack.h"

class queue {
    stack in;
    stack out;

public:
    void push(int num);
    int pop();
};


void queue::push(int num) {
    in.push(num);
}

int queue::pop() {
    if (in.size() == 0 && out.size() == 0)
        return -1;
    if (out.size() == 0){
        while (!in.empty()){
            out.push(in.pop());
        }
    }
    return out.pop();
}

#endif //MODULE_1_QUEUE_H
