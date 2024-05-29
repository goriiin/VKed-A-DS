//
// Created by dmitry on 29.05.2024.
//

#include "matrixGraph.h"

void matrix_graph::AddEdge(int from, int to) {
    graph[from][to] = true;
}

int matrix_graph::VerticesCount() const {
    return (int)graph.size();
}

std::vector<int> matrix_graph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    for (int i = 0; i < VerticesCount(); ++i){
        if (graph[vertex][i])
            res.push_back(i);
    }
    return res;
}

std::vector<int> matrix_graph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (int i = 0; i < VerticesCount(); ++i){
        if (graph[i][vertex])
            res.push_back(i);
    }

    return res;
}
