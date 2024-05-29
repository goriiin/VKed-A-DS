//
// Created by dmitry on 29.05.2024.
//

#ifndef MODULE3_MATRIXGRAPH_H
#define MODULE3_MATRIXGRAPH_H

#include <vector>
#include "../IGraph.h"

struct matrix_graph : public IGraph{

    explicit matrix_graph(int n) : graph(n, std::vector<bool>(n, false)){}
    explicit matrix_graph(const IGraph &other_graph) {
        for (int i = 0; i < other_graph.VerticesCount(); ++i) {
            for (auto j : other_graph.GetNextVertices(i)){
                graph[i][j] = true;
            }
        }
    }
    ~matrix_graph() override = default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;

    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<bool>> graph;
};


#endif //MODULE3_MATRIXGRAPH_H
