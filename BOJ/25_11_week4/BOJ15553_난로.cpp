#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using pii = pair<int, int>;

/*
그리디
*/

int main() {
  // FILE *fp;
  // freopen_s(&fp, "input.txt", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, K;
  cin >> N >> K;
  vector<int> arrive(N);
  vector<int> gap(N);
  for (int i = 0; i < N; i++) {
    cin >> arrive[i];
    if (i > 0) gap[i - 1] = arrive[i] - arrive[i - 1];
  }

  std::sort(gap.begin(), gap.end() - 1);

  int answer = N;
  int iter = N - K, idx = 0;
  while (iter--) {
    answer += gap[idx++] - 1;
  }

  cout << answer << endl;

  return 0;
}