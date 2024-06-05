//
// Created by dmitry on 06.06.24.
//

#include "box_muller.h"

std::pair<double, double> points::gets() {
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
