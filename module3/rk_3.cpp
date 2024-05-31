#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;


void bfs(long long  a, long long  b, long long  M, long long  x, long long  y) {
    vector<long long > dist(M, LLONG_MAX);
    dist[x] = 0;
    deque<int> dq;
    dq.push_back(x);

    while (!dq.empty()) {
        long long  z = dq.front();
        dq.pop_front();

        long long  next1 = (z + 1) % M;
        if (dist[z] + a < dist[next1]) {
            dist[next1] = dist[z] + a;
            dq.push_back(next1);
        }

        long long  next2 = (z * z + 1) % M;
        if (dist[z] + b < dist[next2]) {
            dist[next2] = dist[z] + b;
            dq.push_back(next2);
        }
    }

    if (dist[y] == LLONG_MAX) {
        cout << -1 << endl;
    } else {
        cout << dist[y] << endl;
    }
}

int main() {
    long long a, b, M, x, y;
    cin >> a >> b >> M >> x >> y;
    bfs(a, b, M, x, y);
    return 0;
}
