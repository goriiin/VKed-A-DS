#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

void run(std::istream &in, std::ostream &out);

int main() {
    run(std::cin, std::cout);
    return 0;
}

struct ListGraph {
    explicit ListGraph(int size) : graph(size) {}

    void add_edge(int from, int to) {
        graph[from].push_back(to);
    }

    int vertices_count() const {
        return (int) graph.size();
    }

    std::vector<int> get_next_vertices(int vertex) const {
        return {graph[vertex].begin(), graph[vertex].end()};
    }

    std::vector<int> get_prev_vertices(int vertex) const {
        std::vector<int> res;
        for (int from = 0; from < graph.size(); ++from) {
            for (int to: graph[from]) {
                if (to == vertex) {
                    res.push_back(from);
                }
            }
        }
        return res;
    }

private:
    std::vector<std::vector<int>> graph;
};


bool is_hamiltonian(ListGraph& graph, std::vector<int> path){
    if (graph.vertices_count() != path.size())
        return false;
    for (int i = 0; i < graph.vertices_count(); ++i){
        if (std::find(path.begin(), path.end(), i) == path.end()){
            return false;
        }
    }

    for (int i = 0; i < path.size() - 1; ++i) {
        int u = path[i];
        int v = path[i + 1];
        bool foundEdge = false;
        for (int j : graph.get_next_vertices(u)) {
            if (j == v) {
                foundEdge = true;
                break;
            }
        }
        if (!foundEdge) {
            return false;
        }
    }


    return true;
}

void run(std::istream &in, std::ostream &out) {
    int N = 0;
    in >> N;
    ListGraph graph(N);
    int M = 0;
    in >> M;
    int K = 0;
    in >> K;
    for (int i = 0; i < M; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph.add_edge(a, b);
        graph.add_edge(b, a);
    }


    std::vector<int> path;
    for (int i = 0; i < K; ++i) {
        int a;
        in >> a;
        path.push_back(a);
    }
    out << is_hamiltonian(graph, path);
}
