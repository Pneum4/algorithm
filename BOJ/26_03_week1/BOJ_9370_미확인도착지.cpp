#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;
const int INF = 2e9;

struct qEle {
  int pos, dist;
  bool isContain;

  bool operator<(const qEle& b) const { return dist > b.dist; }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    int n, m, t;
    cin >> n >> m >> t;
    int s, g, h;
    cin >> s >> g >> h;

    vector<vector<pii>> graph(n + 1);
    vector<int> dist(n + 1, INF), destList;
    vector<bool> contain(n + 1, false);

    for (int i = 0; i < m; i++) {
      int a, b, w;
      cin >> a >> b >> w;
      graph[a].push_back({b, w});
      graph[b].push_back({a, w});
    }

    for (int i = 0; i < t; i++) {
      int d;
      cin >> d;
      destList.push_back(d);
    }
    sort(destList.begin(), destList.end());

    dist[s] = 0;
    priority_queue<qEle> pq;
    pq.push({s, 0, false});

    while (!pq.empty()) {
      qEle cur = pq.top();
      pq.pop();

      if (cur.dist > dist[cur.pos]) {
        continue;
      }

      if (cur.dist == dist[cur.pos] && contain[cur.pos] && !cur.isContain)
        continue;

      for (pii next : graph[cur.pos]) {
        int nextDist = dist[cur.pos] + next.second;
        bool canPassGH = (cur.isContain || (cur.pos == g && next.first == h) ||
                          (cur.pos == h && next.first == g));

        if (nextDist < dist[next.first]) {
          dist[next.first] = nextDist;
          contain[next.first] = canPassGH;
          pq.push({next.first, nextDist, canPassGH});
        } else if (nextDist == dist[next.first] && !contain[next.first] &&
                   canPassGH) {
          contain[next.first] = true;
          pq.push({next.first, nextDist, true});
        }
      }
    }

    for (int i = 0; i < (int)destList.size(); i++) {
      if (contain[destList[i]]) {
        cout << destList[i] << (i == destList.size() - 1 ? "" : " ");
      }
    }
    cout << '\n';
  }

  return 0;
}
