#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  cin >> N;

  vector<vector<vector<int>>> dp(
      N + 1, vector<vector<int>>(10, vector<int>(1 << 10, 0)));

  for (int i = 1; i <= 9; ++i) {
    dp[1][i][1 << i] = 1;
  }

  for (int i = 2; i <= N; ++i) {             // new
    for (int j = 0; j <= 9; ++j) {           // new
      for (int k = 0; k < (1 << 10); ++k) {  // old
        int newBit = k | (1 << j);
        if (j > 0) {
          dp[i][j][newBit] = (dp[i][j][newBit] + dp[i - 1][j - 1][k]) % MOD;
        }
        if (j < 9) {
          dp[i][j][newBit] = (dp[i][j][newBit] + dp[i - 1][j + 1][k]) % MOD;
        }
      }
    }
  }

  int answer = 0;
  for (int i = 0; i <= 9; ++i) {
    answer = (answer + dp[N][i][(1 << 10) - 1]) % MOD;
  }

  cout << answer << '\n';

  return 0;
}