#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;
const int INF = 2e9;

vector<vector<pii>> graph;
vector<int> dist;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    int n, d, c;
    cin >> n >> d >> c;
    graph.assign(n + 1, vector<pii>());
    dist.assign(n + 1, INF);

    for (int i = 0; i < d; i++) {
      int a, b, s;
      cin >> a >> b >> s;
      graph[b].push_back({a, s});
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, c});
    dist[c] = 0;

    while (!pq.empty()) {
      int cp = pq.top().second;
      int cd = pq.top().first;
      pq.pop();

      if (cd > dist[cp]) continue;

      for (pii& next : graph[cp]) {
        int np = next.first;
        int nd = cd + next.second;

        if (nd >= dist[np]) continue;

        dist[np] = nd;
        pq.push({nd, np});
      }
    }

    int maxVal = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
      int cur = dist[i];
      if (cur < INF) {
        cnt++;
        if (cur > maxVal) maxVal = cur;
      }
    }

    cout << cnt << " " << maxVal << '\n';
  }

  return 0;
}