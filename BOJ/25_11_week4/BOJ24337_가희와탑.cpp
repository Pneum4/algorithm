#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
경우의 수를 한정시킬 기준이 안보여서 그리디 진행
1. 디버깅
  - a=1인 경우 highest가 가장 먼저 출력되는 예외case고려해야됨
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int N, a, b;
  cin >> N >> a >> b;

  if (a + b > N + 1) {
    cout << -1 << endl;
    return 0;
  }

  vector<int> first(a - 1), second(b - 1);
  int highest = max(a, b);
  for (int i = 0; i < a - 1; i++) {
    first[i] = i + 1;
  }
  for (int i = 0; i < b - 1; i++) {
    second[i] = i + 1;
  }

  int remain = N - a - b + 1;

  if (a == 1) {
    cout << highest << " ";
    for (int i = 0; i < remain; i++) cout << 1 << " ";
    for (int i = 0; i < a - 1; i++) cout << first[i] << " ";
    for (int i = b - 2; i >= 0; i--) cout << second[i] << " ";
  } else {
    for (int i = 0; i < remain; i++) cout << 1 << " ";
    for (int i = 0; i < a - 1; i++) cout << first[i] << " ";
    cout << highest << " ";
    for (int i = b - 2; i >= 0; i--) cout << second[i] << " ";
  }
}
/*
1 2 3

1 2 1 3 1
3 2

1 1 2 3 1
1 1 3 2 1
*/
