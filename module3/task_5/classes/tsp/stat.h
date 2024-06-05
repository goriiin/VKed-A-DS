//
// Created by dmitry on 06.06.24.
//

#ifndef TASK_5_STAT_H
#define TASK_5_STAT_H

#include <cmath>

std::pair<double, double> calculate_statistics(const std::vector<double>& data) {
    if (data.empty()) {
        return {0, 0};
    }

    double sum = 0;
    for (double value : data) {
        sum += value;
    }
    double mean = sum / data.size();

    double squared_sum = 0;
    for (double value : data) {
        squared_sum += std::pow(value - mean, 2);
    }
    double stddev = std::sqrt(squared_sum / data.size());

    return {mean, stddev};
}

#endif //TASK_5_STAT_H
