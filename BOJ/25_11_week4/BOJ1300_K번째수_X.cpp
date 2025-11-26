#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

/*
1. 해결할 문제
  - 공간도 줄이고 시간도 줄여야한다

2. log n 알고리즘이 필요하다 (n=1e10)
  - 정렬, 이분탐색 ?
  - 정렬이 불가능 하니깐 이분탐색 해보자

3. 구해야 되는 값
  - value는 value보다 작거나 같은 값이 k개 이상인 가장 작은 값이다
  - 또한 1개 row는 전부 i의 배수이기 때문에
    row의 N개 원소에서 특정 값보다 작은 원소의 개수는 O(1)에 계산이 가능
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  int K;
  cin >> K;
  int l = 1, r = (int)min((ll)1e9, (ll)N * N) + 1;
  int answer = 0;
  while (l < r) {
    int m = (l + r) / 2;
    int cnt = 0;
    for (int i = 1; i <= N; i++) {
      cnt += min(m / i, N);
    }

    if (K <= cnt) {
      answer = m;
      r = m;
    } else {
      l = m + 1;
    }
  }

  cout << r << endl;

  return 0;
}
/*
  1 2 3
1 1 2 3
2 2 4 6
3 3 6 9

1 2 2 3 3 4 6 6 9
*/