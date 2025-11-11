#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int INF = 2e9;

vector<vector<int>> map, leftRight, rightLeft;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int N, M;
  cin >> N >> M;
  map.assign(N + 1, vector<int>(M + 1, 0));
  leftRight.assign(N + 1, vector<int>(M + 1, -INF));
  rightLeft.assign(N + 1, vector<int>(M + 1, -INF));

  for (int r = 1; r <= N; r++) {
    for (int c = 1; c <= M; c++) {
      cin >> map[r][c];
    }
  }

  leftRight[1][1] = rightLeft[1][1] = map[1][1];
  for (int r = 1; r <= N; r++) {
    leftRight[r][1] = map[r][1];
    if (r > 1) leftRight[r][1] += leftRight[r - 1][1];
    for (int c = 2; c <= M; c++) {
      leftRight[r][c] =
          max(leftRight[r - 1][c], leftRight[r][c - 1]) + map[r][c];
    }

    if (r != 1) {
      rightLeft[r][M] = map[r][M];
      if (r > 1) rightLeft[r][M] += rightLeft[r - 1][M];
      for (int c = M - 1; c >= 1; c--) {
        rightLeft[r][c] =
            max(rightLeft[r - 1][c], rightLeft[r][c + 1]) + map[r][c];
      }
    }

    for (int c = 1; c <= M; c++) {
      leftRight[r][c] = max(leftRight[r][c], rightLeft[r][c]);
      rightLeft[r][c] = max(leftRight[r][c], rightLeft[r][c]);
    }
  }

  cout << leftRight[N][M] << '\n';

  return 0;
}
