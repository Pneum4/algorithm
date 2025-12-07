#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pic = pair<int, char>;
using pii = pair<int, int>;

/*
디버그 :
  - 마지막 꼬리의 위치를 실시간 추적하려면 큐가 하나 필요하다
*/

int N, K, L;
vector<vector<char>> map;
vector<pic> changeDir;
queue<pii> snake;
int cr, cc, cd, timer, changeIdx;
int dr[4] = {-1, 0, 1, 0};  // u r d l
int dc[4] = {0, 1, 0, -1};

bool move() {
  ++timer;

  int nr = cr + dr[cd];
  int nc = cc + dc[cd];

  if (nr < 0 || nr >= N || nc < 0 || nc >= N) return false;
  if (map[nr][nc] == 'S') return false;

  if (map[nr][nc] != 'A') {
    pii last = snake.front();
    snake.pop();
    map[last.first][last.second] = '0';
  }

  map[nr][nc] = 'S';
  snake.push({nr, nc});
  cr = nr;
  cc = nc;

  pic curChange = changeDir[changeIdx];
  if (curChange.first == timer) {
    if (curChange.second == 'L') {
      cd = (cd + 3) % 4;
    } else {
      cd = (cd + 1) % 4;
    }
    changeIdx++;
  }

  return true;
}

void showMap() {
  for (auto& row : map) {
    for (auto& ele : row) {
      cout << ele << " ";
    }
    cout << '\n';
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  cin >> N >> K;
  map.assign(N, vector<char>(N, '0'));
  for (int i = 0; i < K; i++) {
    int r, c;
    cin >> r >> c;
    map[r - 1][c - 1] = 'A';
  }
  cin >> L;
  changeDir.assign(L, {});
  for (int i = 0; i < L; i++) {
    int s;
    char d;
    cin >> s >> d;
    changeDir[i] = {s, d};
  }
  sort(changeDir.begin(), changeDir.end());
  changeIdx = 0;

  cr = 0;
  cc = 0;
  cd = 1;
  timer = 0;
  map[cr][cc] = 'S';
  snake.push({0, 0});
  while (move()) {
    // showMap();
  }

  cout << timer << '\n';

  return 0;
}
