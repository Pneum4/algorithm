#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;

const int INF = 2e9;

vector<vector<pii>> graph;
vector<int> dist;
vector<int> pre;

auto comp = [](pii& a, pii& b) { return a.first > b.first; };

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M;
  cin >> N >> M;
  graph.assign(N + 1, vector<pii>());
  dist.assign(N + 1, INF);
  pre.assign(N + 1, 0);

  for (int i = 0; i < M; i++) {
    int s, e, w;
    cin >> s >> e >> w;
    graph[s].push_back({e, w});
  }

  int S, E;
  cin >> S >> E;

  priority_queue<pii, vector<pii>, decltype(comp)> pq(comp);

  dist[S] = 0;
  pq.push({0, S});

  while (!pq.empty()) {
    int cd = pq.top().first;
    int cp = pq.top().second;
    pq.pop();

    if (cd > dist[cp]) continue;

    for (pii& next : graph[cp]) {
      int np = next.first;
      int nd = next.second + cd;

      if (dist[np] <= nd) continue;

      dist[np] = nd;
      pre[np] = cp;
      pq.push({nd, np});
    }
  }

  cout << dist[E] << endl;

  vector<int> answer;

  for (int i = E; i != S; i = pre[i]) {
    answer.push_back(i);
  }
  answer.push_back(S);

  reverse(answer.begin(), answer.end());

  cout << answer.size() << endl;

  for (int& cur : answer) {
    cout << cur << " ";
  }

  return 0;
}
