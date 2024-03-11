//
// Created by dmitry on 11.03.2024.
//

#ifndef MODULE_1_VECTOR_H
#define MODULE_1_VECTOR_H

using ui = unsigned int;

template <typename T>
class vector {
    T* data;
    int cap = 0;
    int len = 0;
public:
    vector() {}
    explicit vector(int num){
        data = new int(num);
        cap = num;
    }
    vector(const vector& vec);
    vector operator = (const vector& vec);
    ~vector(){}
    vector(vector&& vec) = delete;
    vector operator = (vector&& vec) = delete;

    bool empty();
    ui size();
    void resize(ui new_cap);
    T get(ui index);
    T operator [] (int ind);
    void reserve(int new_cap);
    void push_back(T num);
    void pop_back();
};


#endif //MODULE_1_VECTOR_H
