//
// Created by dmitry on 29.05.2024.
//

#include "matrixGraph.h"

void MatrixGraph::AddEdge(int from, int to) {
    graph[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return (int)graph.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> res;
    for (int i = 0; i < VerticesCount(); ++i){
        if (graph[vertex][i])
            res.push_back(i);
    }
    return res;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;
    for (int i = 0; i < VerticesCount(); ++i){
        if (graph[i][vertex])
            res.push_back(i);
    }

    return res;
}
