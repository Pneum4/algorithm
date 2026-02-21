#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INF = 2e9;

vector<vector<int>> graph;
vector<int> visited;
vector<vector<int>> dist;

void bfs(int s) {
  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int next : graph[cur]) {
      if (visited[next] == s) continue;

      visited[next] = s;
      dist[s][next] = min(dist[s][next], dist[s][cur] + 1);
      q.push(next);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M, Q;
  cin >> N >> M >> Q;
  graph.assign(N + 1, vector<int>());
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
  }
  visited.assign(N + 1, 0);
  dist.assign(N + 1, vector<int>(N + 1, INF));

  for (int i = 1; i <= N; i++) {
    visited[i] = i;
    dist[i][i] = 0;
    bfs(i);
  }

  for (int i = 0; i < Q; i++) {
    int a, b;
    cin >> a >> b;
    int answer = INF;
    for (int j = 1; j <= N; j++) {
      if (dist[j][a] == INF || dist[j][b] == INF) continue;
      answer = min(answer, max(dist[j][a], dist[j][b]));
    }
    if (answer == INF)
      cout << -1 << '\n';
    else
      cout << answer << '\n';
  }
  return 0;
}