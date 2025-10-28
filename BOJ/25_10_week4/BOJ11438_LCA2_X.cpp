#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int maxNode = 100'000;

/*
난이도 5 많이 어렵다
LCA 원리는 13144 참고
initDp -> 바로 윗 부모만 dp 배열에 넣어줌
calcDp -> 바로 윗 부모 정보만 있는데, k값을 1개씩 증가시키면서 다른 2^k 부모도
채운다 findLCA ->
  - a b 중에서 depth가 높은 것을 낮은 것에 맞춰주고
  - 2^maxK 부터 시작해서 1씩 k값을 낮추면서 공통 부모를 찾아 올라간다
  - 같은 부모를 가졌다 = 거기나 그 아래 어딘가에서 공통 부모가 있다
  - 다른 부모를 가졌다 = 그 위에 어딘가에 공통 부모가 있다
  - 2^k 에서 같은 부모를 가졌으면 k--
  - 2^k 에서 다른 부모를 가졌으면 거기로 이동 후, 이동한 곳에서 2^k-1부터 다시
탐색
  - 이렇게 탐색하면 이진 탐색이 가능
*/

int maxHeight, N, M;
vector<vector<int>> graph;
vector<vector<int>> dp;
vector<int> depth;

void initDp(int par, int cur, int dep) {
  dp[cur][0] = par;
  depth[cur] = dep;  // 0base

  for (int next : graph[cur]) {
    if (next == par) continue;
    initDp(cur, next, dep + 1);
  }
}

void calcDp() {
  for (int k = 1; k <= maxHeight; k++) {
    for (int i = 2; i <= N; i++) {
      if (dp[i][k - 1] != 0) {
        dp[i][k] = dp[dp[i][k - 1]][k - 1];
      }
    }
  }
}

int findLCA(int a, int b) {
  if (depth[a] < depth[b]) swap(a, b);
  // depth[a] >= depth[b]

  int diff = depth[a] - depth[b];
  int i = 0;
  while (diff >= (1 << i)) {
    if ((diff & (1 << i)) != 0) a = dp[a][i];
    i++;
  }

  if (a == b) return a;

  for (int i = maxHeight; i >= 0; i--) {
    if (dp[a][i] != dp[b][i]) {
      a = dp[a][i];
      b = dp[b][i];
    }
  }

  return dp[a][0];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  // freopen("input.txt", "r", stdin);

  cin >> N;

  maxHeight = ceil(log2(N));
  graph.assign(N + 1, vector<int>());
  depth.assign(N + 1, 0);
  dp.assign(N + 1, vector<int>(maxHeight + 1, 0));

  for (int i = 0; i < N - 1; i++) {
    int s, e;
    cin >> s >> e;
    graph[s].push_back(e);
    graph[e].push_back(s);
  }

  initDp(0, 1, 0);
  calcDp();

  cin >> M;
  while (M--) {
    int a, b;
    cin >> a >> b;
    cout << findLCA(a, b) << '\n';
  }

  return 0;
}