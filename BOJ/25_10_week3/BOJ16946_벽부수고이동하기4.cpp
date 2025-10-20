#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using pii = pair<int, int>;

// bfs/dfs 그룹핑 문제
// 디버깅 )
//   -> 마지막에 주변 그룹 id로 주변 그룹의 총 사이즈 합을 구하는데
//   -> id의 중복을 막는 로직이 필요함

int N, M;
vector<string> board;  // 맵정보 저장
vector<vector<int>>
    group;  // 이동할 수 있는 곳을 모아서 그룹으로 만들고, 그룹 id저장
vector<int> idToSize;  // 그룹이 만들어졌으면 id:size 저장
static int dr[4] = {1, 0, -1, 0};
static int dc[4] = {0, 1, 0, -1};

int bfs(int r, int c, int id) {
  queue<pii> q;
  group[r][c] = id;
  q.push({r, c});

  int size = 1;
  while (!q.empty()) {
    pii cur = q.front();
    q.pop();

    for (int d = 0; d < 4; d++) {
      int nr = cur.first + dr[d];
      int nc = cur.second + dc[d];

      if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
      if (board[nr][nc] == '0' && group[nr][nc] == -1) {
        size++;
        group[nr][nc] = id;
        q.push({nr, nc});
      }
    }
  }

  return size;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N >> M;

  board.resize(N);
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
  }
  group.assign(N, vector<int>(M, -1));

  int id = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (board[i][j] == '0' && group[i][j] == -1) {
        int curSize = bfs(i, j, id++);
        idToSize.push_back(curSize);
      }
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (board[i][j] == '0') {
        cout << 0;
      } else {
        set<int> buffer;
        for (int d = 0; d < 4; d++) {
          int nr = i + dr[d];
          int nc = j + dc[d];

          if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;

          int curId = group[nr][nc];
          if (curId != -1) {
            buffer.insert(curId);
          }
        }

        int sum = 1;
        for (int ele : buffer) sum += idToSize[ele];
        cout << sum % 10;
      }
    }
    cout << '\n';
  }

  return 0;
}
