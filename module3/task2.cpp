#include <iostream>
#include <vector>
#include <queue>

void run(std::istream &in, std::ostream &out);

int main() {
    run(std::cin, std::cout);
}


struct Graph {
private:
    struct _vertex {
        size_t dist{};
        size_t k{};
    };
public:
    Graph(int size) : graph(size){}
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

    size_t count_path(int from, int to) {
        std::vector<_vertex> visited(vertices_count(), {0, 0});
        std::queue<int> q;
        q.push(from);
        visited[from].k = 1;

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            auto next = get_next_vertices(curr);
            for (auto i: next) {
                if (visited[i].k == 0) {
                    q.push(i);
                    visited[i].dist = visited[curr].dist + 1;
                    visited[i].k = visited[curr].k;
                } else if (visited[i].dist == visited[curr].dist + 1) {
                    visited[i].k += visited[curr].k;
                }
            }
        }

        return visited[to].k;
    }


private:
    std::vector<std::vector<int>> graph;
};

void run(std::istream &in, std::ostream &out) {
    int size = 0;
    std::cin >> size;
    Graph graph(size);

    std::cin >> size;
    for (int i = 0; i < size; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph.add_edge(a, b);
        graph.add_edge(b, a);
    }
    int from, to;
    std::cin >> from >> to;
    std::cout << graph.count_path(from, to);
}