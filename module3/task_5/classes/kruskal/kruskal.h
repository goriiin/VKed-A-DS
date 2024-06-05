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
        if (dsu.find_set(edge.to)!= dsu.find_set(edge.from)){
            dsu.union_set(edge.from, edge.to);
            total+=edge.weight;
        }
    }
    return total;
}


#endif //TASK_5_KRUSKAL_H
