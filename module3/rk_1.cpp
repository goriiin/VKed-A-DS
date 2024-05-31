

#include <iostream>
#include <vector>
#include <stack>

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

void dfs(const ListGraph &graph, int vertex, std::vector<bool> &visited) {
    std::stack<int> st;
    visited[vertex] = true;

    st.push(vertex);
    while (!st.empty()) {
        auto curr = st.top();
        bool flag = false; // флаг нахождения соседа,
        // в которого мы пока не заходили

        for (auto &to: graph.get_next_vertices(curr)) {
            if (!visited[to]) {
                st.push(to);
                flag = true;
                visited[to] = true;
                break;
            }
        }
        if (!flag) {
            st.pop();
        }
    }

}


int find_KSS(const ListGraph &graph) {
    std::vector<bool> visited(graph.vertices_count(), false);
    int k = 0;
    for (int v = 0; v < graph.vertices_count(); ++v) {
        if (!visited[v]) {
            ++k;
            dfs(graph, v, visited);
        }
    }
    return k;
}

void run(std::istream &in, std::ostream &out) {
    int s = 0;
    std::cin >> s;
    ListGraph graph(s);
    std::cin >> s;

    for (int i = 0; i < s; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.add_edge(from, to);
        graph.add_edge(to, from);
    }
    std::cout << find_KSS(graph);
}
