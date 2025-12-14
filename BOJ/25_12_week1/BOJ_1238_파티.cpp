#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
시작점이 여러개이고, 한 지점까지의 최단거리르 구하려면
edge를 뒤집고, 그 지점에서 다익스트라를 구하면 된다.
*/

struct node {
  int v;
  int d;

  bool operator<(const node& b) const { return this->d < b.d; }
};

inline void dijkstra(int s, vector<vector<node>>& _graph, vector<int>& _dist) {
  _dist[s] = 0;

  priority_queue<node> pq;
  pq.push(node{s, 0});

  while (!pq.empty()) {
    node curNode = pq.top();
    pq.pop();

    if (_dist[curNode.v] < curNode.d) continue;

    for (const node& next : _graph[curNode.v]) {
      int newDist = _dist[curNode.v] + next.d;
      if (_dist[next.v] > newDist) {
        _dist[next.v] = newDist;
        pq.push(node{next.v, newDist});
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int vertex, edge, start;
  cin >> vertex >> edge >> start;

  vector<int> dist;     // inf
  vector<int> revDist;  // inf
  vector<vector<node>> graph;
  vector<vector<node>> revGraph;

  dist.assign(vertex + 1, INT_MAX);
  revDist.assign(vertex + 1, INT_MAX);
  graph.assign(vertex + 1, vector<node>());
  revGraph.assign(vertex + 1, vector<node>());

  for (int i = 0; i < edge; ++i) {
    int s, e, d;
    cin >> s >> e >> d;

    graph[s].push_back(node{e, d});
    revGraph[e].push_back(node{s, d});
  }

  dijkstra(start, graph, dist);

  dijkstra(start, revGraph, revDist);

  int max = 0;
  for (int i = 1; i <= vertex; ++i) {
    if (max < (dist[i] + revDist[i])) max = dist[i] + revDist[i];
  }
  cout << max << endl;

  return 0;
}