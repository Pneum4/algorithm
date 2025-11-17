#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int answer, N;
vector<vector<int>> map, dp;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

/*
1. 분석
  - dfs와 dp를 이용한 문제
  - dp 값이 없는 곳에 처음 도착했을때, 탐색을 진행하고 dp를 갱신해준다

2. 최적화
  - visitied 배열은 필요가 없다
*/

int stackSearch(int row, int col) {
  if (dp[row][col] != -1) return dp[row][col];

  int cnt = 0;
  for (int d = 0; d < 4; d++) {
    int nr = row + dr[d];
    int nc = col + dc[d];

    if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
    if (map[nr][nc] <= map[row][col]) continue;

    cnt = max(cnt, stackSearch(nr, nc));
  }

  dp[row][col] = cnt + 1;
  answer = max(answer, cnt + 1);

  return cnt + 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  cin >> N;
  map.assign(N, vector<int>(N, 0));
  dp.assign(N, vector<int>(N, -1));
  answer = 0;

  for (auto& row : map)
    for (auto& ele : row) cin >> ele;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (dp[i][j] != -1) continue;
      stackSearch(i, j);
    }
  }

  cout << answer << '\n';

  return 0;
}
