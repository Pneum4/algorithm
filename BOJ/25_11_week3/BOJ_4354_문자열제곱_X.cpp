#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
abaabaaba
abaaba
   abaaba

1. pi값이 N/2보다는 커야된다
2. N-pi(N-1) 값이 N으로 나누어 떨어져야한다
  - 위 예시에서 aba가 반복 문자열인데
  - 위 aba랑 아래 aba랑 같고,
  - 아래 aba는 바로 위의 aba 와 매핑되어서 같다
  - 이걸 반복하는데 반복이 끝났을때 남는 문자열이 없으면 모든 문자열이 aba로
표현되는 것 참고로 Pi(N-1) != N 이다 (자기자신은 항상 prefix이면서 suffix)

abacaba -> N/2 보다 작아서 안됨
aba
    aba

abababa -> 반복 문자열 매칭이 끝나면 1개가 남음
ababa
  ababa
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  while (true) {
    string in;
    cin >> in;
    if (in == ".") break;

    int n = in.size();
    vector<int> pi(n, 0);

    int i = 1, j = 0;  // i는 원본, j는 토큰 인덱스
    while (i < n) {
      while (j > 0 && in[i] != in[j]) {
        j = pi[j - 1];
      }

      if (in[i] == in[j]) {
        pi[i] = ++j;
      }
      i++;
    }

    int len = n - pi[n - 1];
    if (n % len == 0)
      cout << n / len << '\n';
    else
      cout << 1 << '\n';
  }

  return 0;
}
