#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;
const int INF = 2e9;

vector<int> dist, revDist;
vector<vector<pii>> graph, revGraph;

void dijkstra(vector<vector<pii>>& curGraph, vector<int>& curDist, int start) {
  curDist[start] = 0;
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push({0, start});

  while (!pq.empty()) {
    pii cur = pq.top();
    pq.pop();

    if (cur.first > curDist[cur.second]) {
      continue;
    }

    for (pii next : curGraph[cur.second]) {
      if (cur.first + next.second < curDist[next.first]) {
        curDist[next.first] = cur.first + next.second;
        pq.push({curDist[next.first], next.first});
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M, X;
  cin >> N >> M >> X;
  graph.assign(N + 1, vector<pii>());
  revGraph.assign(N + 1, vector<pii>());
  dist.assign(N + 1, INF);
  revDist.assign(N + 1, INF);

  for (int i = 0; i < M; i++) {
    int s, e, c;
    cin >> s >> e >> c;
    graph[s].push_back({e, c});
    revGraph[e].push_back({s, c});
  }

  dijkstra(graph, dist, X);
  dijkstra(revGraph, revDist, X);

  int answer = 0;
  for (int i = 1; i <= N; i++) {
    answer = max(answer, dist[i] + revDist[i]);
  }

  cout << answer << endl;

  return 0;
}
