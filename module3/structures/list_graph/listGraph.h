//
// Created by dmitry on 29.05.2024.
//

#ifndef MODULE3_LISTGRAPH_H
#define MODULE3_LISTGRAPH_H

#include "../IGraph.h"

struct list_graph : public IGraph {
    explicit list_graph(int size) : graph(size) {}

    explicit list_graph(const IGraph &other_graph) {
        for (int i = 0; i < other_graph.VerticesCount(); ++i) {
            graph[i] = other_graph.GetNextVertices(i);
        }
    }

    ~list_graph() override = default;

    void AddEdge(int from, int to) override;

    [[nodiscard]] int VerticesCount() const override;

    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;

    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> graph;
};


#endif //MODULE3_LISTGRAPH_H
