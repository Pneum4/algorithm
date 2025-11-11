#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int N, M;
  cin >> N >> M;
  int K;
  cin >> K;
  vector<vector<bool>> leftRight(M + 1, vector<bool>(N + 1, false)),
      downUp(M + 1, vector<bool>(N + 1, false));

  for (int i = 0; i < K; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    if (x1 == x2)
      downUp[min(y1, y2)][x1] = true;
    else
      leftRight[y1][min(x1, x2)] = true;
  }

  vector<vector<ll>> dp(M + 1, vector<ll>(N + 1, 0));
  dp[0][0] = 1;

  for (int i = 0; i <= M; i++) {
    for (int j = 0; j <= N; j++) {
      if (i > 0 && !downUp[i - 1][j]) dp[i][j] += dp[i - 1][j];
      if (j > 0 && !leftRight[i][j - 1]) dp[i][j] += dp[i][j - 1];
    }
  }

  cout << dp[M][N] << '\n';
  return 0;
}
