//
// Created by dmitry on 05.06.24.
//

#ifndef TASK5_BOX_MULLER_H
#define TASK5_BOX_MULLER_H

#include <cmath>
#include <random>
#include "sd/edge/edge.h"

using pdd = std::pair<double, double>;

pdd get_point() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(0.0, 1.0);

    double u = dis(gen);
    double v = dis(gen);

    double a = std::sqrt(-2.0 * std::log(v));
    double b = 2.0 * M_PI * u;

    double x = a * std::cos(b);
    double y = a * std::sin(b);

    return std::make_pair(x, y);
}

double get_weight(pdd a, pdd b) {
    return std::sqrt(std::pow((a.first - b.first), 2) + std::pow((a.second - b.second), 2));
}

std::vector<pdd> get_points(int count_points) {
    std::vector<pdd> points;
    points.reserve(count_points);
    for (int i = 0; i < count_points; ++i) {
        points.emplace_back(get_point());
    }
    return points;
}

double get_weight(std::vector<pdd> points, int from, int to) {
    return get_weight(points[from], points[to]);
}

#endif //TASK5_BOX_MULLER_H
