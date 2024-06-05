#include <iostream>
#include <vector>
#include "kruskal.h"
#include "sd/edge/edge.h"

int main() {
    std::vector<Edge> edges = {
            {2, 3, 3},
            {1, 6, 4},
            {5, 7, 5},
            {6, 8, 5},
            {7, 8, 5},
            {2, 4, 1},
            {3, 4, 1},
            {1, 3, 2},
            {0, 3, 6},
            {4, 7, 6},
            {3, 6, 7},
            {0, 1, 9},
            {3, 5, 9},
            {5, 6, 1},
            {5, 8, 1},
            {0, 2, 2}
    };

    kruskal(edges, edges.size(),[](const Edge& e){
       std::cout << "( " << e.from << ", " << e.to << " )" << std::endl;
    });
    return 0;
}
