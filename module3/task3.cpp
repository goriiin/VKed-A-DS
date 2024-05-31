#include <iostream>
#include <set>
#include <vector>
#include <cassert>
#include <climits>

// test 1
//6
//0 1 2
//0 2 5
//1 2 1
//1 3 3
//2 4 4
//3 4 1
//0 4

//вывод 6

//test2
//3
//3
//0 1 5
//1 2 3
//2 2 1
//0 2

//вывод 8

//test3
//4
//4
//0 1 1
//1 2 2
//2 3 3
//0 3 10
//0 3

//вывод 6



void run(std::istream &in, std::ostream &out);

int main() {
    run(std::cin, std::cout);
}

struct MatrixGraph {
    explicit MatrixGraph(unsigned int n) : graph(n, std::vector<std::pair<unsigned int, unsigned int>>()) {}

    void add_edge(unsigned int from, unsigned int to, unsigned int weight) {
        assert(0 <= from && from < graph.size());
        assert(0 <= to && to < graph.size());

        if (from == to)
            return;

        graph[from].emplace_back(to, weight);
        graph[to].emplace_back(from, weight);
    }

    unsigned int vertices_count() const {
        return graph.size();
    }

    std::vector<std::pair<unsigned int, unsigned int>> get_next_vertices(unsigned int vertex) const {
        return graph[vertex];
    }

    void relax(std::vector<unsigned int> &dist,
               std::set<std::pair<unsigned int, unsigned int>> &q,
               unsigned int from, unsigned int to, unsigned int weight) {

        if (dist[to] > dist[from] + weight) {
            auto it = q.find({dist[to], to});
            if (it != q.end()) {
                q.erase(it);
            }

            dist[to] = dist[from] + weight;
            q.insert({dist[to], to});
        }
    }

    int Dijkstra(unsigned int from, unsigned int to) {
        std::set<std::pair<unsigned int, unsigned int>> q;
        std::vector<unsigned int> dist(vertices_count(), INT_MAX);

        dist[from] = 0;
        q.insert({0, from});


        while (!q.empty()) {
            auto curr = q.begin()->second;
            q.erase(q.begin());

            auto next = get_next_vertices(curr);
            for (auto v: next) {
                if (dist[v.first] == INT_MAX) {
                    dist[v.first] = dist[curr] + v.second;
                    q.insert({v.second, v.first});

                } else
                    relax(dist, q, curr, v.first, v.second);
            }
        }
        return (dist[to] == INT_MAX) ? -1 : dist[to];
    }

private:
    // вершина - вес
    std::vector<std::vector<std::pair<unsigned int, unsigned int>>> graph;
};

void run(std::istream &in, std::ostream &out) {
    int size = 0;
    in >> size;
    MatrixGraph graph(size);

    in >> size;
    for (int i = 0; i < size; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        graph.add_edge(a, b, c);
    }
    int from, to;
    in >> from >> to;
    out << graph.Dijkstra(from, to);
}