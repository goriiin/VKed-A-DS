//
// Created by dmitry on 06.06.24.
//

#ifndef TASK_5_APROXIMATION_H
#define TASK_5_APROXIMATION_H

#include <vector>

double calculate_approximation(const Graph& graph, double mst_weight) {
    std::vector<int> optimal_path;
    double optimal_distance = tsp(graph);
    return 2 * mst_weight / optimal_distance;
}
#endif //TASK_5_APROXIMATION_H
