/*
MST 문제
1. 크루스칼 풀이
2. 프림 풀이
*/

// 1. 크루스칼 풀이 (20584KB 372ms)
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int, int> pii;

struct qEle {
  int s, e, c;

  qEle(int _s = -1, int _e = -1, int _c = -1) : s(_s), e(_e), c(_c) {}

  bool operator<(const qEle& b) const { return c > b.c; }
};
vector<int> parent;

int find(int a) {
  if (parent[a] == a)
    return a;
  else
    return parent[a] = find(parent[a]);
}

void unionFind(int a, int b) {
  int pa = find(a);
  int pb = find(b);
  if (pa < pb)
    parent[pb] = pa;
  else
    parent[pa] = pb;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int V, E;
  cin >> V >> E;
  priority_queue<qEle> pq;
  for (int i = 0; i < E; ++i) {
    int s, e, c;
    cin >> s >> e >> c;
    pq.push({s, e, c});
  }

  parent.resize(V + 1);
  for (int i = 1; i <= V; ++i) {
    parent[i] = i;
  }

  qEle last;
  int sum = 0, cnt = 0;
  while (cnt < V - 2) {
    qEle cur = pq.top();
    pq.pop();
    int s = cur.s;
    int e = cur.e;
    int c = cur.c;

    int ps = find(s);
    int pe = find(e);

    if (ps == pe) continue;

    unionFind(s, e);
    sum += c;
    cnt++;
  }
  cout << sum << '\n';

  return 0;
}

// 2. 프림 풀이 (43936KB 604ms)
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int, int> pii;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int V, E;
  cin >> V >> E;
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  vector<vector<pii>> graph(V + 1, vector<pii>());
  for (int i = 0; i < E; ++i) {
    int s, e, c;
    cin >> s >> e >> c;
    graph[s].push_back({e, c});
    graph[e].push_back({s, c});
  }

  vector<bool> visited(V + 1, false);
  pq.push({0, 1});

  int sum = 0, cnt = 0;
  int high = 0;
  while (!pq.empty() && cnt <= V - 1) {
    pii cur = pq.top();
    pq.pop();

    high = max(high, cur.first);
    if (visited[cur.second]) continue;

    visited[cur.second] = true;
    sum += cur.first;
    cnt++;

    for (auto ele : graph[cur.second]) {
      if (!visited[ele.first]) pq.push({ele.second, ele.first});
    }
  }

  cout << sum - high << endl;

  return 0;
}