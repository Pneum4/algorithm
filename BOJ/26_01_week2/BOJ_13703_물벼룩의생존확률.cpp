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

  int k, n; cin>>k>>n; //k:위치 n:횟수

  if (n == 0) {
    cout << (k == 0 ? 0 : 1) << "\n";
    return 0;
  }

  vector<vector<ll>> dp(64+1, vector<ll>(n+1, 0));

  for(int i=0; i<64+1; i++) {
    dp[i][0] = 0;
  }

  for(int i=0; i<n+1; i++) {
    dp[0][i] = (1ll<<i);
  }

  for(int c=1; c<n+1; c++) {
    for(int r=1; r<64; r++) {
      dp[r][c] = dp[r-1][c-1] + dp[r+1][c-1];
    }
  }

  ll result = (1ll<<n) - dp[k][n];

  cout<<result<<endl;

  return 0;
}
