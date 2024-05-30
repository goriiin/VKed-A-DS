//
// Created by dmitry on 30.05.2024.
//

#include "setGraph.h"

void SetGraph::AddEdge(int from, int to) {
    next[from].push_back(to);
    prev[to].push_back(from);
}

int SetGraph::VerticesCount() const {
    return count;
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    return next.at(vertex);
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    return prev.at(vertex);
}
