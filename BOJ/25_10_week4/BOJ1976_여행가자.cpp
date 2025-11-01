#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
유니온 파인드 풀이 : O(N^2 * a(N)) : a(N)은 거의 상수
플로이드 워셜 풀이 : O(N^3)

플로이드 워셜로 풀긴했는데
유니온 파인드가 더 최적임
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  // freopen("input.txt", "r", stdin);

  int N, M;
  cin >> N >> M;

  vector<vector<bool>> linkedMap(N, vector<bool>(N, false));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int in;
      cin >> in;
      linkedMap[i][j] = (in ? true : false);
    }
  }

  for (int i = 0; i < N; i++) {
    for (int r = 0; r < N; r++) {
      for (int c = 0; c < N; c++) {
        if (i == r || i == c) continue;
        linkedMap[r][c] =
            linkedMap[r][c] || (linkedMap[i][c] && linkedMap[r][i]);
      }
    }
  }

  int pre, cur;
  for (int i = 0; i < M; i++) {
    if (i == 0) {
      cin >> pre;
      continue;
    }
    cin >> cur;

    if (!linkedMap[pre - 1][cur - 1]) {
      cout << "NO" << '\n';
      return 0;
    }
    pre = cur;
  }

  cout << "YES" << '\n';

  return 0;
}
