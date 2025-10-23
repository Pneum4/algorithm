#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// dp[a][b][c] -> a번째 시간일때 b번 움직였을경우 현재위치가 1/2일때 최대 자두
// 개수 디버깅)
//   -> 시간이 1일때 무조건 1번 나무에 서있어야 한다 = 0번 움직였을 경우
//   현재위치 2일때 최대 자두개수는 모두 0

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("input.txt", "r", stdin);

  int T, W;
  cin >> T >> W;
  vector<vector<vector<int>>> dp(T + 1,
                                 vector<vector<int>>(W + 1, vector<int>(2, 0)));

  for (int i = 1; i <= T; i++) {
    int in;
    cin >> in;
    for (int j = 0; j <= W; j++) {
      if (j == 0) {
        dp[i][j][0] = dp[i - 1][j][0] + (in == 1 ? 1 : 0);
        dp[i][j][1] = 0;
        continue;
      }

      dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][0] + (in == 1 ? 1 : 0));
      dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j][1] + (in == 2 ? 1 : 0));
      if (j - 1 >= 0) {
        dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j - 1][1] + (in == 1 ? 1 : 0));
        dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j - 1][0] + (in == 2 ? 1 : 0));
      }
    }
  }

  int answer = 0;
  for (int j = 0; j <= W; j++) {
    answer = max({answer, dp[T][j][0], dp[T][j][1]});
  }

  cout << answer << '\n';

  return 0;
}
