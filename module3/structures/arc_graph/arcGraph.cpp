//
// Created by dmitry on 30.05.2024.
//

#include "arcGraph.h"

void ArcGraph::AddEdge(int from, int to) {
    edges.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    return count;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    for (auto item : edges) {
        if (item.first == vertex)
            res.push_back(item.second);
    }

    return res;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (auto item : edges) {
        if (item.second == vertex)
            res.push_back(item.first);
    }

    return res;
}
