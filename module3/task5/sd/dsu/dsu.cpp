//
// Created by dmitry on 05.06.24.
//

#include "dsu.h"


void DSU::union_set(int v, int u) {
    int v_set = find_set(v);
    int u_set = find_set(u);

    if (v_set == u_set) {
        return;
    }
    if (rank[v_set] > rank[u_set]) {
        parent[u_set] = v_set;
        rank[u_set] += rank[v_set];
    } else {
        parent[v_set] = u_set;
        rank[v_set] += u_set;
    }
}

int DSU::find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}
