#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
1. 피보나치?
  -> dp구나
2. log n 피보나치가 필요한가?
  -> 피보나치 최댓값이 10억이면 되는거라 필요없어보인다
3. dfs인가?
  -> 최소 수열 1개만 찾는거라 낭비같다
4. 그리디?
  -> 큰거부터 빼보면 무조건 가능할 것 같다 (느낌)
*/

vector<int> dp;

void calcFibo() {
  dp.push_back(1);
  dp.push_back(1);
  int curIdx = 1;
  while (true) {
    int cur = dp[curIdx - 1] + dp[curIdx];
    if (cur > 1e9) {
      dp.push_back(cur);
      return;
    }
    dp.push_back(cur);
    curIdx++;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("input.txt", "r", stdin);

  calcFibo();

  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;

    int remain = N;
    vector<int> answer;
    while (remain > 0) {
      for (int i = 1; i < (int)dp.size(); i++) {
        if (dp[i] > remain) {
          answer.push_back(dp[i - 1]);
          remain -= dp[i - 1];
          break;
        }
      }
    }
    reverse(answer.begin(), answer.end());
    for (auto& ele : answer) cout << ele << " ";
    cout << '\n';
  }
  return 0;
}
