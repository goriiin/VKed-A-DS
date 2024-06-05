//
// Created by dmitry on 05.06.24.
//

#ifndef TASK_5_KRUSKAL_H
#define TASK_5_KRUSKAL_H

#include <algorithm>
#include "../graph/graph.h"
#include "../dsu/dsu.h"


double kruskal(Graph& graph){
    DSU dsu(graph.vertices_count());

    auto edges = graph.get_edges();

    std::sort(edges.begin(), edges.end(), [](const Edge &l, const Edge &r) {
        return l.weight < r.weight;
    });
    double total = 0;
    for (const auto &edge: edges) {
        int v = dsu.find_set(edge.from);
        int u = dsu.find_set(edge.to);

        if (v == u) {
            continue;
        }

        dsu.union_set(v, u);
        total += edge.weight;
    }
    return total;
}


#endif //TASK_5_KRUSKAL_H
