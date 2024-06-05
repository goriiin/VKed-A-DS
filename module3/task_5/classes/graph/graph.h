//
// Created by dmitry on 05.06.24.
//

#ifndef TASK_5_GRAPH_H
#define TASK_5_GRAPH_H

#include <algorithm>
#include "../edge/edge.h"


struct Graph {
    explicit Graph(int size) : vertices(size) {
        points = create_points(size);
    }

    void add_edge(int from, int to);

    [[nodiscard]] int vertices_count() const;

    [[nodiscard]] std::vector<int> get_next_vertices(int vertex) const;

    [[nodiscard]] std::vector<std::pair<double, double>> get_points() const;

    [[nodiscard]] std::vector<Edge> get_edges() const;

    [[nodiscard]] double get_weight(int from, int to) const;

private:
    [[nodiscard]] static double _get_weight(const std::pair<double, double> &a, const std::pair<double, double> &b);

    static std::vector<std::pair<double, double>> create_points(int count_points);

    std::vector<std::vector<int>> vertices;
    std::vector<std::pair<double, double>> points;
};


#endif //TASK_5_GRAPH_H
