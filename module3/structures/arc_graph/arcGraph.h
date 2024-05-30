//
// Created by dmitry on 30.05.2024.
//

#ifndef MODULE3_ARCGRAPH_H
#define MODULE3_ARCGRAPH_H


#include <iostream>
#include "../IGraph.h"

struct arc_graph : public IGraph{
    explicit arc_graph(int n) : count(n) {}
    explicit arc_graph(const IGraph &other_graph) : count(other_graph.VerticesCount())  {
        for (int i = 0; i < other_graph.VerticesCount(); ++i) {
            for (auto j : other_graph.GetNextVertices(i)) {
                edges.emplace_back(i, j);
            }
        }
    }
    ~arc_graph() override = default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;

    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> edges;
    int count = 0;
};


#endif //MODULE3_ARCGRAPH_H
