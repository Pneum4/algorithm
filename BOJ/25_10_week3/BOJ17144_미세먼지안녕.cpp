
#include <iostream>
#include <vector>
using namespace std;

// 주의)
// 공기 순환할때 앞에서 밀어야할까? 뒤에서 당겨야할까?

int R, C, T;
int board[50][50];
int temp[50][50];
pair<int, int> airCleanerTop, airCleanerBottom;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void spread() {
  for (int i = 0; i < R; ++i)
    for (int j = 0; j < C; ++j) temp[i][j] = 0;

  for (int x = 0; x < R; ++x) {
    for (int y = 0; y < C; ++y) {
      if (board[x][y] >= 5) {
        int spread_amount = board[x][y] / 5;
        int count = 0;
        for (int dir = 0; dir < 4; ++dir) {
          int nx = x + dx[dir];
          int ny = y + dy[dir];
          if (nx >= 0 && nx < R && ny >= 0 && ny < C && board[nx][ny] != -1) {
            temp[nx][ny] += spread_amount;
            count++;
          }
        }
        board[x][y] -= spread_amount * count;
      }
    }
  }

  for (int x = 0; x < R; ++x)
    for (int y = 0; y < C; ++y) board[x][y] += temp[x][y];
}

void clean() {
  int x = airCleanerTop.first;
  int y = airCleanerTop.second;

  for (int i = x - 1; i > 0; i--) board[i][0] = board[i - 1][0];
  for (int i = 0; i < C - 1; i++) board[0][i] = board[0][i + 1];
  for (int i = 0; i < x; i++) board[i][C - 1] = board[i + 1][C - 1];
  for (int i = C - 1; i > 1; i--) board[x][i] = board[x][i - 1];
  board[x][1] = 0;

  x = airCleanerBottom.first;
  y = airCleanerBottom.second;

  for (int i = x + 1; i < R - 1; i++) board[i][0] = board[i + 1][0];
  for (int i = 0; i < C - 1; i++) board[R - 1][i] = board[R - 1][i + 1];
  for (int i = R - 1; i > x; i--) board[i][C - 1] = board[i - 1][C - 1];
  for (int i = C - 1; i > 1; i--) board[x][i] = board[x][i - 1];
  board[x][1] = 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> R >> C >> T;
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      cin >> board[i][j];
      if (board[i][j] == -1) {
        if (airCleanerTop.first == 0)
          airCleanerTop = {i, j};
        else
          airCleanerBottom = {i, j};
      }
    }
  }

  while (T--) {
    spread();
    clean();
  }

  int total = 0;
  for (int i = 0; i < R; ++i)
    for (int j = 0; j < C; ++j)
      if (board[i][j] > 0) total += board[i][j];

  cout << total << '\n';
  return 0;
}
