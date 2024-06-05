//
// Created by dmitry on 05.06.24.
//

#ifndef TASK_5_TSP_H
#define TASK_5_TSP_H

#include "../graph/graph.h"
#include "../box_muller/box_muller.h"
#include <limits>
#include <stack>


double tsp(const Graph& graph) {
    int V = graph.vertices_count();
    std::vector<bool> visited(V, false);
    double minCost = std::numeric_limits<double>::max();

    struct State {
        int currPos;
        int count;
        double cost;
        int i;
    };

    std::stack<State> stack;
    stack.push({0, 1, 0.0, 0});

    while (!stack.empty()) {
        auto& state = stack.top();
        visited[state.currPos] = true;

        while (state.i < V) {
            if (!visited[state.i]) {
                // Используем graph.get_weight() вместо adjMatrix
                double newCost = state.cost + graph.get_weight(state.currPos, state.i);
                stack.push({state.i, state.count + 1, newCost, 0});
                visited[state.i] = true;
                state.currPos = state.i;
                state.count++;
                state.cost = newCost;
                state.i = 0;
                continue;
            }
            state.i++;
        }

        if (state.count == V) {
            minCost = std::min(minCost, state.cost + graph.get_weight(state.currPos, 0));
        }

        visited[state.currPos] = false;
        stack.pop();
    }

    return minCost;
}


#endif //TASK_5_TSP_H
