//
// Created by dmitry on 05.06.24.
//

#include "graph.h"
#include "../box_muller/box_muller.h"

void Graph::add_edge(int from, int to) {
    vertices[from].push_back(to);
    vertices[to].push_back(from);
}

int Graph::vertices_count() const {
    return (int) vertices.size();
}

std::vector<int> Graph::get_next_vertices(int vertex) const {
    return vertices[vertex];
}

std::vector<std::pair<double, double>> Graph::get_points() const {
    return points;
}

std::vector<std::pair<double, double>> Graph::create_points(int count_points) {
    std::vector<std::pair<double, double>> points;
    points.reserve(count_points);
    for (int i = 0; i < count_points; ++i) {
        points.emplace_back(points::gets());
    }
    return points;
}

std::vector<Edge> Graph::get_edges() const {
    std::vector<Edge> edges;
    for (int i = 0; i < vertices_count(); ++i) {
        for (int j = 1; j < vertices_count(); ++j) {
            edges.push_back({i, j, get_weight(i, j)});
        }
    }

    return edges;
}

double Graph::_get_weight(const std::pair<double, double> &a, const std::pair<double, double> &b) {
    return std::sqrt(std::pow((a.first - b.first), 2) + std::pow((a.second - b.second), 2));
}

double Graph::get_weight(int from, int to) const {
    return ((from != to) ? _get_weight(points[from], points[to]) : 0);
}
