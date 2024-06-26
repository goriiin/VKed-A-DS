//
// Created by dmitry on 06.06.24.
//

#ifndef TASK_5_EXPERIMENT_H
#define TASK_5_EXPERIMENT_H

#include <iostream>
#include <vector>
#include "../tsp/stat.h"
#include "../tsp/tsp.h"
#include "../kruskal/kruskal.h"
#include "../tsp/aproximation.h"

void run_experiment(int n_vertices, int num_trials = 10) {
    std::vector<double> approximations;

    for (int i = 0; i < num_trials; ++i) {
        Graph graph(n_vertices);
        double mst_weight = kruskal(graph);
        double optimal_distance = tsp(graph);
        std::cout << "i=" << i << " mst: " << mst_weight << " optimal: " << optimal_distance << "\n";
        approximations.push_back(calculate_approximation(optimal_distance, mst_weight));
    }

    auto stats = calculate_statistics(approximations);
    std::cout << "Mean: " << stats.first << ", StdDev: " << stats.second << std::endl;
    std::cout << "==========================================================\n";

}

#endif //TASK_5_EXPERIMENT_H
