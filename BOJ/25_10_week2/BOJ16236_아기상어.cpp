#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

// 1. 다음 위치를 탐색하는데, 거리가 기준이다 -> bfs 사용
// 2. 주의 ) 물고기를 자기 크기만큼 먹어야 레벨업
//   -> 먹은 물고기 정보가 필요하고, 레벨업하면 0으로 초기화해야한다
// 3. 구현

// 4. 최적화 ) 전부 다 찾고 거리 기준 정렬하지 말고
//   -> bfs로 탐색하는데, 가장 가까운 상어가 아니라면 넘어가자
//   -> 같은 거리라면 위, 왼쪽 기준으로 업데이트가 가능한지 보자
//   -> bfs가 끝나면 가장 우선순위가 높은 상어 1개만 알 수 있다

// (거리, x좌표, y좌표)를 담는 튜플 타입 정의
using Fish = tuple<int, int, int>;

int N;                      // 공간의 크기
int board[21][21];          // 물고기/상어가 있는 공간
int sharkSize = 2;          // 초기 상어 크기 (2로 시작)
int eaten = 0;              // 현재 크기에서 먹은 물고기 수
int timeSum = 0;            // 총 이동 시간 (정답)
int sx, sy;                 // 상어의 현재 위치
int dx[4] = {-1, 0, 0, 1};  // 상, 좌, 우, 하
int dy[4] = {0, -1, 1, 0};

// 좌표 (x, y)가 격자 내에 있는지 검사
bool inRange(int x, int y) { return x >= 0 && x < N && y >= 0 && y < N; }

// BFS를 실행해서 이번 턴에 먹을 수 있는 물고기를 찾는 함수
bool bfs() {
  // BFS 거리 배열 (방문 체크도 겸함)
  vector<vector<int>> dist(N, vector<int>(N, -1));

  // BFS 큐 (상어 위치에서 시작)
  queue<pair<int, int>> q;
  dist[sx][sy] = 0;
  q.push({sx, sy});

  vector<Fish> candidates;  // 먹을 수 있는 물고기 후보 리스트

  // BFS 시작
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    // 4방향 탐색
    for (int d = 0; d < 4; ++d) {
      int nx = x + dx[d];
      int ny = y + dy[d];

      // 1️⃣ 범위를 벗어남 or 이미 방문함 or 상어보다 큰 물고기 → 이동 불가
      if (!inRange(nx, ny) || dist[nx][ny] != -1 || board[nx][ny] > sharkSize)
        continue;

      // 2️⃣ 이동 가능
      dist[nx][ny] = dist[x][y] + 1;

      // 3️⃣ 먹을 수 있는 물고기 (자기보다 작은 물고기)
      if (board[nx][ny] > 0 && board[nx][ny] < sharkSize)
        candidates.emplace_back(dist[nx][ny], nx, ny);

      // 4️⃣ 다음 탐색 큐에 추가
      q.push({nx, ny});
    }
  }

  // 먹을 수 있는 물고기가 하나도 없다면 → 종료
  if (candidates.empty()) return false;

  // 1. 거리(d) → 2. 위쪽(x) → 3. 왼쪽(y) 우선순위로 정렬
  sort(candidates.begin(), candidates.end());

  // 가장 우선순위가 높은 물고기 선택
  auto [d, tx, ty] = candidates[0];

  // 이동 거리 누적
  timeSum += d;

  // 먹은 개수 증가
  eaten++;

  // 상어가 있던 자리 비우기
  board[sx][sy] = 0;

  // 상어를 새로운 위치로 이동
  sx = tx;
  sy = ty;

  // 먹은 물고기 자리도 비우기
  board[sx][sy] = 0;

  // 상어가 자신의 크기만큼 물고기를 먹으면 크기 증가
  if (eaten == sharkSize) {
    sharkSize++;
    eaten = 0;
  }

  return true;  // 이번 턴에 물고기를 하나 먹었음
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;

  // 입력 처리
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> board[i][j];
      if (board[i][j] == 9) {
        // 9는 상어의 초기 위치
        sx = i;
        sy = j;
        board[i][j] = 0;  // 상어가 이동 가능해야 하므로 0으로 초기화
      }
    }
  }

  // 먹을 수 있는 물고기가 더 이상 없을 때까지 반복
  while (bfs());

  // 총 이동 시간 출력
  cout << timeSum << '\n';
  return 0;
}
