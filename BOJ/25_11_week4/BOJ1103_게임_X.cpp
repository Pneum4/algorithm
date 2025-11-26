#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
처음에는 dp없이 백트래킹만 하면 될 줄 알았다
그러나 dp없이 풀이는 되는데 시간 복잡도에서 터진다 (시간 4^2500 이라는데 맞나?)
1. 인사이트
  - dfs에서 왠만하면 dp를 사용하자. 귀찮더라도 디버깅보다 덜걸린다.
*/

vector<vector<char>> map;
vector<vector<bool>> visited;
vector<vector<int>> dp;
int N, M, hasLoop;
const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};

int stackSearch(int r, int c) {
  if (hasLoop) return 0;

  if (map[r][c] == 'H') {
    return 0;
  }

  if (dp[r][c] != -1) return dp[r][c];

  int cur = map[r][c] - '0';
  int result = 0;
  for (int d = 0; d < 4; d++) {
    int nr = r + dr[d] * cur;
    int nc = c + dc[d] * cur;

    if (nr < 0 || nr >= N || nc < 0 || nc >= M) {
      result = max(result, 1);
      continue;
    }

    if (visited[nr][nc]) {
      hasLoop = true;
      return 0;
    }

    visited[nr][nc] = true;
    result = max(result, stackSearch(nr, nc) + 1);
    visited[nr][nc] = false;
  }

  return dp[r][c] = result;
}

int main() {
  // FILE *fp;
  // freopen_s(&fp, "input.txt", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M;

  map.assign(N, vector<char>(M));
  visited.assign(N, vector<bool>(M, false));
  dp.assign(N, vector<int>(M, -1));
  for (auto& row : map) {
    for (auto& ele : row) {
      cin >> ele;
    }
  }

  hasLoop = false;
  visited[0][0] = true;
  stackSearch(0, 0);

  if (hasLoop)
    cout << -1 << endl;
  else
    cout << dp[0][0] << endl;

  return 0;
}