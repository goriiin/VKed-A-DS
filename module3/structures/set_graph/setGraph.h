//
// Created by dmitry on 30.05.2024.
//

#ifndef MODULE3_SETGRAPH_H
#define MODULE3_SETGRAPH_H


#include "../IGraph.h"
#include <unordered_map>

struct SetGraph : public IGraph {

    explicit SetGraph(int n) : count(n) {}

    explicit SetGraph(const IGraph &other_graph) : count(other_graph.VerticesCount()) {
        for (int i = 0; i < other_graph.VerticesCount(); ++i) {
            next[i] = other_graph.GetNextVertices(i);
            prev[i] = other_graph.GetPrevVertices(i);
        }
    }

    ~SetGraph() override = default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;

    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;

private:
    int count;
    std::unordered_map<int, std::vector<int>> next;
    std::unordered_map<int, std::vector<int>> prev;
};


#endif //MODULE3_SETGRAPH_H
