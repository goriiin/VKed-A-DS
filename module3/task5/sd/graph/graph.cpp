//
// Created by dmitry on 05.06.24.
//

#include "graph.h"

int Graph::VerticesCount() const {
    return (int) vertices.size();
}

std::vector<int> Graph::GetNextVertices(int vertex) const {
    return vertices[vertex];
}

void Graph::AddEdge(int from, int to) {
    vertices[from].push_back(to);
    vertices[to].push_back(from);
}

double Graph::get_weight(int from, int to) const {
    return point::get_weight(points, from, to);
}
