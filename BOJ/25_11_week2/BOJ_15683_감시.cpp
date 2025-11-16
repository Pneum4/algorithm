#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using pii = pair<int, int>;

int N, M, answer;
vector<vector<char>> map;
vector<pii> cctvPos;
int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
// u r d l
vector<vector<vector<int>>> cctvDir = {
    {},                                            // dummy
    {{0}, {1}, {2}, {3}},                          // 1번
    {{0, 2}, {1, 3}},                              // 2번
    {{0, 1}, {1, 2}, {2, 3}, {3, 0}},              // 3번
    {{0, 1, 2}, {1, 2, 3}, {2, 3, 0}, {3, 0, 1}},  // 4번
    {{0, 1, 2, 3}}                                 // 5번
};

/*
1. 자료구조
cctv 위치 큐
stackSearch(depth)
view(pos, dir, change)

2. 인사이트
메모리 절약을 위해 백트래킹을 이용
cctv로 바뀐 위치를 저장했다가 하위 탐색이 끝나면 다시 복구
-> 단순하게 직선으로 복구하면 원래 #이었던 곳도 복구가 되어서 틀린다

*/

void view(int row, int col, int dir,
          vector<pii>& change) {  // 1: view, 0: unview
  int nr = row, nc = col;

  while (true) {
    nr += dr[dir];
    nc += dc[dir];

    if (nr < 0 || nr >= N || nc < 0 || nc >= M) break;
    if (map[nr][nc] == '6') break;

    if (map[nr][nc] == '0') {
      map[nr][nc] = '#';
      change.push_back({nr, nc});
    }
  }
}

void stackSearch(int depth) {
  if (depth == cctvPos.size()) {
    int cnt = 0;

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (map[i][j] == '0') cnt++;
      }
    }

    answer = min(answer, cnt);

    return;
  }

  int cr = cctvPos[depth].first, cc = cctvPos[depth].second;
  int cur = map[cr][cc] - '0';
  int n = cctvDir[cur].size();
  for (auto& ele : cctvDir[cur]) {
    vector<pii> change;
    for (auto& nd : ele) {
      view(cr, cc, nd, change);
    }

    stackSearch(depth + 1);

    for (auto& ele : change) {
      map[ele.first][ele.second] = '0';
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  cin >> N >> M;
  map.assign(N, vector<char>(M));

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      char cur;
      cin >> cur;
      map[i][j] = cur;
      if (cur >= '1' && cur <= '5') {
        cctvPos.push_back({i, j});
      }
    }
  }

  answer = 100;
  stackSearch(0);

  cout << answer << '\n';

  return 0;
}
