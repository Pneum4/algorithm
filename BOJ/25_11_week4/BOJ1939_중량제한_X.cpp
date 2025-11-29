#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;

/*
세가지 풀이 가능
1. BFS이진탐색 -> 36ms
2. Dijkstra -> 36ms
3. Union-Find -> 28ms

첫번째 풀이 BFS + 이진탐색
가능한 모든 무게를 이진탐색하고, 이동 가능한 가장 큰 무게를 리턴
*/
vector<vector<pii>> graph;
vector<int> visited;

bool bfs(int start, int end, int limit) {
  queue<int> q;
  q.push(start);
  visited[start] = limit;
  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (pii next : graph[cur]) {
      int np = next.first;   // pos
      int nc = next.second;  // cost
      if (visited[np] == limit) continue;
      if (nc < limit) continue;

      if (np == end) return true;

      visited[np] = limit;
      q.push(np);
    }
  }

  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int N, M;
  cin >> N >> M;
  graph.assign(N + 1, vector<pii>());
  visited.assign(N + 1, 0);
  for (int i = 0; i < M; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].push_back({b, c});
    graph[b].push_back({a, c});
  }
  int S, E;
  cin >> S >> E;

  int l = 1, r = 1e9 + 1;
  int answer = 0;
  while (l < r) {
    int mid = (l + r) / 2;
    if (bfs(S, E, mid)) {
      l = mid + 1;
      answer = mid;
    } else {
      r = mid;
    }
  }
  cout << answer << '\n';

  return 0;
}

/*
두번째 풀이 다익스트라
a->b 갱신할때 dist[a]와 a->b cost의 최솟값을 보고,
그 최소값이 dist[b] 보다 크면 갱신해주고 큐에 넣는다.
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;
const int INF = 2e9;

vector<vector<pii>> graph;
vector<int> dist;  // 현재까지 가능한 무게의 최댓값
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int N, M;
  cin >> N >> M;
  graph.assign(N + 1, vector<pii>());
  dist.assign(N + 1, -1);

  for (int i = 0; i < M; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].push_back({b, c});
    graph[b].push_back({a, c});
  }
  int S, E;
  cin >> S >> E;

  priority_queue<pii> pq;
  pq.push({INF, S});
  dist[S] = INF;

  while (!pq.empty()) {
    pii cur = pq.top();
    pq.pop();
    int cc = cur.first;
    int cp = cur.second;

    if (dist[cp] > cc) continue;

    for (pii next : graph[cp]) {
      int np = next.first;
      int nc = min(next.second, cc);

      if (nc > dist[np]) {
        dist[np] = nc;
        pq.push({nc, np});
      }
    }
  }

  cout << dist[E] << '\n';

  return 0;
}

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
세번째 풀이 유니온 파인드
사이클이 생기던말던 큰거부터 넣다가
S E 연결되면 마지막으로 넣었던 값이 답
*/
vector<int> parent;

struct Node {
  int s, e, c;

  bool operator<(const Node& b) const { return c < b.c; }
};

int find(int x) {
  if (x == parent[x])
    return x;
  else
    return parent[x] = find(parent[x]);
}

void unionTwo(int a, int b) {
  int pa = find(a);
  int pb = find(b);
  if (pa < pb)
    parent[pb] = pa;
  else
    parent[pa] = pb;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int N, M;
  cin >> N >> M;
  parent.assign(N + 1, 0);
  priority_queue<Node> pq;

  for (int i = 0; i < M; i++) {
    int s, e, c;
    cin >> s >> e >> c;
    pq.push({s, e, c});
  }

  int S, E;
  cin >> S >> E;

  for (int i = 1; i <= N; i++) {
    parent[i] = i;
  }

  int answer;
  while (!pq.empty()) {
    Node cur = pq.top();
    pq.pop();
    unionTwo(cur.s, cur.e);
    if (find(S) == find(E)) {
      answer = cur.c;
      break;
    }
  }

  cout << answer << '\n';

  return 0;
}
