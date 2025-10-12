#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int N, L, R, sum, cnt;
vector<vector<int>> map;
vector<vector<int>> visited;
int dr[4] = {1, 0, -1, 0};
int dc[4] = {0, 1, 0, -1};

// 1. 방문은 dfs로 하면 될 것 같다
// 2. 일단 구역을 나누어서 구역마다 평균이 필요한데
// -> visited를 int로 만들어서 id를 저장해 구역을 나누어보자 (visitToken방식)
// 3. visited에서 id가 같은 지역을 전부 방문하면서 평균값으로 바꿔줘야한다
// -> visited를 또 만들면 낭비니까, 방문한 지역은 -id를 저장해서 방문을
// 표시해보자
// 추가) gpt는 bfs로 하면 더 최적화라는데 gpt:696ms / 내코드:116ms ???

void dfs(int r, int c, int id) {
  for (int d = 0; d < 4; d++) {
    int nr = r + dr[d];
    int nc = c + dc[d];

    if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
    int diff = abs(map[nr][nc] - map[r][c]);
    if (visited[nr][nc] != 0 || diff < L || diff > R) continue;

    visited[nr][nc] = id;
    cnt += 1;
    sum += map[nr][nc];
    dfs(nr, nc, id);
  }
}

void move(int r, int c, int id, int avg) {
  for (int d = 0; d < 4; d++) {
    int nr = r + dr[d];
    int nc = c + dc[d];

    if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;

    if (visited[nr][nc] == id) {
      visited[nr][nc] = -visited[nr][nc];
      map[nr][nc] = avg;
      move(nr, nc, id, avg);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("input.txt", "r", stdin);

  cin >> N >> L >> R;

  map.assign(N, vector<int>(N, 0));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> map[i][j];
    }
  }
  visited.assign(N, vector<int>(N, 0));

  int answer = 0;
  while (true) {
    // visited 0으로 초기화
    for (auto &row : visited) fill(row.begin(), row.end(), 0);

    int id = 1, changeCnt = 0;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (visited[i][j] == 0) {
          // visited에 방문할때마다 id를 남겨서 평균구해야하는 구역을 구분
          sum = map[i][j];
          cnt = 1;
          visited[i][j] = id;
          dfs(i, j, id);

          if (cnt > 1) changeCnt++;

          // 같은 id로 되어있는 구역만 인구수를 평균으로 바꿈
          int avg = sum / cnt;
          map[i][j] = avg;
          visited[i][j] = -visited[i][j];
          move(i, j, id++, avg);
        }
      }
    }
    if (changeCnt == 0) break;
    answer++;
  }

  cout << answer << '\n';

  return 0;
}
