
#include "classes/experiment/experiment.h"



int main() {
    int start_vert = 2, end_vert = 10, num_trials=10;

    for (int n = start_vert; n <= end_vert; ++n) {
        std::cout << "n= " << n;
        run_experiment(n, num_trials);
    }

    return 0;
}
