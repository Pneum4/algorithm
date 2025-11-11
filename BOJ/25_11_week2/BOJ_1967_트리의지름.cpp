#include <iostream>
#include <vector>
using namespace std;

struct Node {
  int v;
  int d;
};

vector<vector<Node>> graph;
vector<bool> visited;
int maxDist;
int maxNode;

inline void dfs(const int v, const int dist) {
  visited[v] = true;

  if (maxDist < dist) {
    maxDist = dist;
    maxNode = v;
  }

  for (const auto [nextV, nextD] : graph[v]) {
    if (!visited[nextV]) {
      dfs(nextV, dist + nextD);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  graph.assign(n + 1, vector<Node>());
  visited.assign(n + 1, false);

  for (int i = 0; i < n - 1; ++i) {
    int s, e, d;
    cin >> s >> e >> d;

    graph[s].push_back({e, d});
    graph[e].push_back({s, d});
  }

  dfs(1, 0);

  fill(visited.begin(), visited.end(), false);
  dfs(maxNode, 0);

  cout << maxDist << '\n';

  return 0;
}