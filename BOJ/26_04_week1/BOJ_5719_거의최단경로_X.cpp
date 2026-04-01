#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;
const int INF = 2e9;

vector<vector<pii>> graph, revGraph;
vector<int> dist;
vector<vector<bool>> visited;
int N, M, S, E;

void dijkstra() {
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push({0, S});
  dist[S] = 0;

  while (!pq.empty()) {
    int cp = pq.top().second;
    int cd = pq.top().first;
    pq.pop();

    if (cd > dist[cp]) continue;

    for (pii& next : graph[cp]) {
      int np = next.first;
      int nd = cd + next.second;

      if (visited[cp][np]) continue;
      if (nd >= dist[np]) continue;

      dist[np] = nd;
      pq.push({nd, np});
    }
  }
}

void btDelete() {
  queue<int> q;
  q.push(E);

  while (!q.empty()) {
    int cp = q.front();
    q.pop();

    if (cp == S) continue;

    for (pii& prev : revGraph[cp]) {
      int pp = prev.first;
      int cc = prev.second;

      if (dist[pp] + cc == dist[cp]) {
        if (visited[pp][cp]) continue;

        visited[pp][cp] = true;
        q.push(pp);
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  while (true) {
    cin >> N >> M;
    if (N == 0 && M == 0) break;

    cin >> S >> E;

    graph.assign(N, vector<pii>());
    revGraph.assign(N, vector<pii>());
    dist.assign(N, INF);
    visited.assign(N, vector<bool>(N, false));

    for (int i = 0; i < M; i++) {
      int a, b, c;
      cin >> a >> b >> c;
      graph[a].push_back({b, c});
      revGraph[b].push_back({a, c});
    }

    dijkstra();
    btDelete();

    dist.assign(N, INF);

    dijkstra();

    if (dist[E] == INF)
      cout << -1 << '\n';
    else
      cout << dist[E] << endl;
  }
  return 0;
}