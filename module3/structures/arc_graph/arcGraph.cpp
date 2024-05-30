//
// Created by dmitry on 30.05.2024.
//

#include "arcGraph.h"

void arc_graph::AddEdge(int from, int to) {
    edges.emplace_back(from, to);
}

int arc_graph::VerticesCount() const {
    return count;
}

std::vector<int> arc_graph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    for (auto item : edges) {
        if (item.first == vertex)
            res.push_back(item.second);
    }

    return res;
}

std::vector<int> arc_graph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (auto item : edges) {
        if (item.second == vertex)
            res.push_back(item.first);
    }

    return res;
}
