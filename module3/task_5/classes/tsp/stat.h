//
// Created by dmitry on 06.06.24.
//

#ifndef TASK_5_STAT_H
#define TASK_5_STAT_H

#include <cmath>

std::pair<double, double> calculate_statistics(const std::vector<double> &data) {
    if (data.empty()) {
        return {0, 0};
    }

    double sum = 0;
    for (double value: data) {
        sum += value;
    }
    double mean = sum / ((double) data.size());

    double squared_sum = 0;
    for (double value: data) {
        squared_sum += std::pow(value - mean, 2);
    }
    double std_dev = std::sqrt(squared_sum / ((double) data.size()));

    return {mean, std_dev};
}

#endif //TASK_5_STAT_H
