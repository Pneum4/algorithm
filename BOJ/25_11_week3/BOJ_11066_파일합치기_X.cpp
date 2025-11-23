#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int INF = 2e9;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int T;
  cin >> T;

  while (T--) {
    int K;
    cin >> K;

    vector<int> arr(K + 1);
    vector<int> sum(K + 1, 0);

    for (int i = 1; i <= K; i++) {
      cin >> arr[i];
      sum[i] = sum[i - 1] + arr[i];
    }

    vector<vector<int>> dp(K + 1, vector<int>(K + 1, 0));

    // len = 구간 길이
    for (int len = 2; len <= K; len++) {
      for (int i = 1; i + len - 1 <= K; i++) {
        int j = i + len - 1;
        dp[i][j] = INF;

        for (int k = i; k < j; k++) {
          dp[i][j] =
              min(dp[i][j], dp[i][k] + dp[k + 1][j] + (sum[j] - sum[i - 1]));
        }
      }
    }

    cout << dp[1][K] << "\n";
  }

  return 0;
}
