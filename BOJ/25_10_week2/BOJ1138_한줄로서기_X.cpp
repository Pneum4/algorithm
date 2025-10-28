#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 일단 완탐도 9!이라서 가능할 것 같음
// 근데 그리디가 가능할 것 같은 느낌이 든다

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  cin >> N;
  vector<int> answer(N, 0);
  for (int i = 1; i <= N; i++) {
    int cnt;
    cin >> cnt;
    cnt++;

    for (int j = 0; j < N; j++) {
      if (answer[j] == 0) {
        cnt--;
        if (cnt == 0) {
          answer[j] = i;
          break;
        }
      }
    }
  }

  for (int ele : answer) cout << ele << ' ';
  cout << '\n';

  return 0;
}
