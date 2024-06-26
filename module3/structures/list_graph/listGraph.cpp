//
// Created by dmitry on 29.05.2024.
//

#include <cassert>
#include "listGraph.h"

void ListGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < graph.size());
    assert(0 <= to && to < graph.size());
    graph[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return (int) graph.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < graph.size());

    return {graph[vertex].begin(), graph[vertex].end()};
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (int from = 0; from < graph.size(); ++from) {
        for (int to: graph[from]) {
            if (to == vertex) {
                res.push_back(from);
            }
        }
    }
    return res;
}
