#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int M, N;
int board[501][501];
int dp[501][501];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int dfs(int x, int y) {
  if (x == M - 1 && y == N - 1) return 1;  // 목적지 도착 = 1개의 경로

  if (dp[x][y] != -1) return dp[x][y];  // 이미 계산됨

  dp[x][y] = 0;

  for (int i = 0; i < 4; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];

    if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;

    if (board[nx][ny] < board[x][y]) {
      dp[x][y] += dfs(nx, ny);
    }
  }

  return dp[x][y];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> M >> N;
  for (int i = 0; i < M; i++)
    for (int j = 0; j < N; j++) cin >> board[i][j];

  memset(dp, -1, sizeof(dp));

  cout << dfs(0, 0) << "\n";
  return 0;
}
