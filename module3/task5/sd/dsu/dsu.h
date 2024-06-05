//
// Created by dmitry on 05.06.24.
//

#ifndef TASK5_DSU_H
#define TASK5_DSU_H

#include <iostream>
#include <vector>

class DSU {
public:
    explicit DSU(int size) {
        rank.resize(size, 1);
        parent.resize(size, 1);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find_set(int v);

    void union_set(int v, int u);

private:
    std::vector<int> parent;
    std::vector<int> rank;
};


#endif //TASK5_DSU_H
