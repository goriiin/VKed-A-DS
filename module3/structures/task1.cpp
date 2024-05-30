#include <iostream>
#include "IGraph.h"
#include <queue>
#include <stack>

#include "list_graph/listGraph.h"
#include "matrix_graph/matrixGraph.h"
#include "set_graph/setGraph.h"
#include "arc_graph/arcGraph.h"

void _dfs_internal(const IGraph &graph, std::vector<bool> &visited, int v, void (*callback)(int v)) {
    visited[v] = true;
    callback(v);

    std::vector<int> children = graph.GetNextVertices(v);
    for (int child: children) {
        if (!visited[child]) {
            _dfs_internal(graph, visited, child, callback);
        }
    }
}

void dfs(const IGraph &graph, void (*callback)(int v)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::stack<int> st;

    for (int v = 0; v < graph.VerticesCount(); ++v) {
        if (!visited[v]) {
            visited[v] = true;
            callback(v);
            st.push(v);
            while (!st.empty()) {
                auto curr = st.top();
                bool flag = false; // флаг нахождения соседа,
                // в которого мы пока не заходили

                for (auto &to: graph.GetNextVertices(curr)) {
                    if (!visited[to]) {
                        st.push(to);
                        flag = true;
                        visited[to] = true;
                        callback(to);
                        break;
                    }
                }
                if (!flag) {
                    st.pop();
                }
            }

        }
    }
}

void bfs(const IGraph &graph, void (*callback)(int v)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> q;

    for (int v = 0; v < graph.VerticesCount(); ++v) {
        if (!visited[v]) {
            visited[v] = true;
            q.push(v);
            while (!q.empty()) {
                int cur_v = q.front();
                q.pop();

                callback(cur_v);

                std::vector<int> children = graph.GetNextVertices(cur_v);
                for (int child: children) {
                    if (!visited[child]) {
                        visited[child] = true;
                        q.push(child);
                    }
                }
            }
        }
    }
}

int main() {
    std::cout << "Begin" << std::endl;
    ListGraph graph(7);
    graph.AddEdge(0, 1);
    graph.AddEdge(1, 0);

    graph.AddEdge(1, 2);
    graph.AddEdge(2, 1);

    graph.AddEdge(2, 3);
    graph.AddEdge(3, 2);

    graph.AddEdge(2, 4);
    graph.AddEdge(4, 2);

    graph.AddEdge(3, 4);
    graph.AddEdge(4, 3);

    graph.AddEdge(1, 5);
    graph.AddEdge(5, 1);

    // MatrixGraph mg(Graph);
//
//    dfs(Graph, [](int v) { std::cout << "[dfs] v=" << v << std::endl; });
//
//    std::cout << "-------------" << std::endl;
//    bfs(Graph, [](int v) { std::cout << "[bfs] v=" << v << std::endl; });



//    MatrixGraph graph1(Graph);
//    dfs(graph1, [](int v) { std::cout << "[dfs] v=" << v << std::endl; });
//
//    std::cout << "-------------" << std::endl;
//    bfs(graph1, [](int v) { std::cout << "[bfs] v=" << v << std::endl; });


    SetGraph graph2(graph);
    dfs(graph2, [](int v) { std::cout << "[dfs] v=" << v << std::endl; });

    std::cout << "-------------" << std::endl;
    bfs(graph2, [](int v) { std::cout << "[bfs] v=" << v << std::endl; });


//    ArcGraph graph3(Graph);
//    dfs(graph3, [](int v) { std::cout << "[dfs] v=" << v << std::endl; });
//
//    std::cout << "-------------" << std::endl;
//    bfs(graph3, [](int v) { std::cout << "[bfs] v=" << v << std::endl; });
    return 0;
}

