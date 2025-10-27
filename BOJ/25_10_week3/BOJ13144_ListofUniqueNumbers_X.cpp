#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool visited[100'000 + 4];

/*
투포인터 할 때 s를 독립된 상태라고 생각하면 편하다
s~e 가 1231 일때
s로 시작하는 정답 배열만 더해준다
1 / 12 / 123 = 3개
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  // freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  vector<int> arr(N, 0);
  for (auto& ele : arr) cin >> ele;

  int s = 0, e = 0;
  long long answer = 0;
  while (s < N) {
    while (e < N) {
      if (visited[arr[e]]) break;
      visited[arr[e]] = true;
      e++;
    }
    answer += (e - s);
    visited[arr[s]] = false;
    s++;
  }

  cout << answer << '\n';

  return 0;
}