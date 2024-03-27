//
// Created by dmitry on 27.03.2024.
//

#ifndef MODULE_1_PAIR_H
#define MODULE_1_PAIR_H

template <typename T1, typename T2>
struct pair {
    T1 first;
    T2 second;

    pair() = default;
    pair(T1 f, T2 s): first(f), second(s) {}
};


#endif //MODULE_1_PAIR_H
