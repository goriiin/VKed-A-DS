//
// Created by dmitry on 26.03.2024.
//

#ifndef MODULE_1_FUNCTOR_H
#define MODULE_1_FUNCTOR_H

template <typename T>
struct BaseFunctor {
    bool operator () (const T& l, const T& r){
        return l < r;
    }
};

#endif //MODULE_1_FUNCTOR_H
