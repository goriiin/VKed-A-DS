//
// Created by dmitry on 05.06.24.
//

#ifndef TASK5_GRAPH_H
#define TASK5_GRAPH_H


#include <vector>
#include "../edge/edge.h"
#include "../../box_muller.h"


class Graph {
    explicit Graph(int size) : vertices(size) {
        points = point::get_points(size);
    }

    void AddEdge(int from, int to);

    [[nodiscard]] int VerticesCount() const;

    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const;

    [[nodiscard]] double get_weight(int from, int to) const;

private:
    std::vector<std::vector<int>> vertices;
    std::vector<std::pair<double, double>> points;
};


#endif //TASK5_GRAPH_H
