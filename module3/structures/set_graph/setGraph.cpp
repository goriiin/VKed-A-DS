//
// Created by dmitry on 30.05.2024.
//

#include "setGraph.h"

void set_graph::AddEdge(int from, int to) {
    next[from].push_back(to);
    prev[to].push_back(from);
}

int set_graph::VerticesCount() const {
    return count;
}

std::vector<int> set_graph::GetNextVertices(int vertex) const {
    return next.at(vertex);
}

std::vector<int> set_graph::GetPrevVertices(int vertex) const {
    return prev.at(vertex);
}
