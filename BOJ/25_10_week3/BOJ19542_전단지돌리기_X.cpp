#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
1. 트리 탐색 문제
  -> dfs(pre, cur) 로 모든 노드를 탐색이 가능하다
2. 어려운점
  -> dfs는 중복 탐색을 하지 않는다는 것과
  -> 깊이 정보를 탐색해야된다는 것을 떠오르기 어렵다
*/

int N, S, D, answer;
vector<vector<int>> graph;

int dfs(int pre, int cur) {
  int depth = 0;
  for (auto next : graph[cur]) {
    if (next == pre) continue;
    depth = max(depth, dfs(cur, next) + 1);
  }
  if (depth >= D && cur != S) answer++;

  return depth;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("input.txt", "r", stdin);

  cin >> N >> S >> D;
  graph.assign(N + 1, vector<int>());
  for (int i = 0; i < N - 1; i++) {
    int s, e;
    cin >> s >> e;
    graph[s].push_back(e);
    graph[e].push_back(s);
  }

  answer = 0;
  dfs(-1, S);

  cout << answer * 2 << '\n';
  return 0;
}