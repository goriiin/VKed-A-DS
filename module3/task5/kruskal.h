//
// Created by dmitry on 05.06.24.
//

#ifndef TASK5_KRUSKAL_H
#define TASK5_KRUSKAL_H

#include <vector>
#include <algorithm>
#include "sd/graph/graph.h"
#include "sd/dsu/dsu.h"

void kruskal(Graph& graph, void (*callback)(const Edge&)){
    DSU dsu(graph.vertices_count());

    auto edges = graph.get_edges();

    std::sort(edges.begin(), edges.end(), [](const Edge& l, const Edge& r){
        return l.weight < r.weight;
    });

    for (const auto& edge: edges) {
        int v = dsu.find_set(edge.from);
        int u = dsu.find_set(edge.to);

        if (v == u){
            continue;
        }

        dsu.union_set(v, u);
        callback(edge);
    }
}


#endif //TASK5_KRUSKAL_H
