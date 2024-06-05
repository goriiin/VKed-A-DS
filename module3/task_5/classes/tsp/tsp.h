//
// Created by dmitry on 05.06.24.
//

#ifndef TASK_5_TSP_H
#define TASK_5_TSP_H

#include "../graph/graph.h"
#include "../box_muller/box_muller.h"
#include <limits>
#include <stack>

double tsp(const Graph &graph) {
    int V = graph.vertices_count();
    std::vector<bool> visited(V, false);
    double min_cost = std::numeric_limits<double>::max();

    struct State {
        int curr_pos;
        int count;
        double cost;
        int i;
    };

    std::stack<State> stack;
    stack.push({0, 1, 0.0, 0});

    while (!stack.empty()) {
        auto &state = stack.top();
        visited[state.curr_pos] = true;

        while (state.i < V) {
            if (!visited[state.i]) {
                double new_cost = state.cost + graph.get_weight(state.curr_pos, state.i);
                stack.push({state.i, state.count + 1, new_cost, 0});
                visited[state.i] = true;
                state.curr_pos = state.i;
                state.count++;
                state.cost = new_cost;
                state.i = 0;
                continue;
            }
            state.i++;
        }

        if (state.count == V) {
            min_cost = std::min(min_cost, state.cost + graph.get_weight(state.curr_pos, 0));
        }

        visited[state.curr_pos] = false;
        stack.pop();
    }

    return min_cost;
}


#endif //TASK_5_TSP_H
