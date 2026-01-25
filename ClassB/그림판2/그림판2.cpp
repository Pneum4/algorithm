#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

char map[512 + 4][512 + 4];
vector<vector<int>> sumMap;
int N, L;

vector<vector<int>> visited;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
int id;

int decode(int r, int c, int idx, int size, string& code) {  // 0 2
  if (code[idx] == '0' || code[idx] == '1') {
    char color = code[idx];
    for (int i = r; i < r + size; i++) {
      for (int j = c; j < c + size; j++) {
        map[i][j] = color;
      }
    }
    return idx + 1;
  } else if (code[idx] == '(') {
    int nextIdx = idx + 1;
    int half = size / 2;

    nextIdx = decode(r, c, nextIdx, half, code);
    nextIdx = decode(r, c + half, nextIdx, half, code);
    nextIdx = decode(r + half, c, nextIdx, half, code);
    nextIdx = decode(r + half, c + half, nextIdx, half, code);

    return nextIdx + 1;
  }
  return idx;
}

void init(int _N, int _L, char mCode[]) {
  N = _N;
  L = _L;
  id = 1;
  visited.assign(N, vector<int>(N, 0));
  memset(map, '0', sizeof(map));
  string code = mCode;
  decode(0, 0, 0, N, code);

  return;
}

void makeSumMap() {
  sumMap.assign(N, vector<int>(N, 0));

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      sumMap[i][j] += map[i][j] - '0';
      if (i > 0) {
        sumMap[i][j] += sumMap[i - 1][j];
      }
      if (j > 0) {
        sumMap[i][j] += sumMap[i][j - 1];
      }
      if (i > 0 && j > 0) {
        sumMap[i][j] -= sumMap[i - 1][j - 1];
      }
    }
  }
}

string result;

void encoding(int r, int c, int len) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      int cr = r + len * i / 2;
      int lr = cr + len / 2 - 1;
      int cc = c + len * j / 2;
      int lc = cc + len / 2 - 1;

      int sum = sumMap[lr][lc];
      if (cr > 0) sum -= sumMap[cr - 1][lc];
      if (cc > 0) sum -= sumMap[lr][cc - 1];
      if (cr > 0 && cc > 0) sum += sumMap[cr - 1][cc - 1];

      if (sum == 0) {
        result.push_back('0');
      } else if (sum == len * len / 4) {
        result.push_back('1');
      } else {
        result.push_back('(');
        encoding(cr, cc, len / 2);
        result.push_back(')');
      }
    }
  }
}

int encode(char mCode[]) {
  makeSumMap();
  result.clear();

  if (sumMap[N - 1][N - 1] == N * N) {
    result.push_back('1');
  } else if (sumMap[N - 1][N - 1] == 0) {
    result.push_back('0');
  } else {
    result.push_back('(');
    encoding(0, 0, N);
    result.push_back(')');
  }

  strcpy(mCode, result.c_str());
  return result.size();
}

void makeDot(int mR, int mC, int mSize, int mColor) {
  for (int i = -(mSize - 1); i <= 0; i++) {
    if (mR + i < 0 || mR + i >= N) continue;
    for (int j = -(i + mSize - 1); j <= i + mSize - 1; j++) {
      if (mC + j < 0 || mC + j >= N) continue;
      map[mR + i][mC + j] = mColor + '0';
    }
  }

  for (int i = 1; i <= mSize - 1; i++) {
    if (mR + i < 0 || mR + i >= N) continue;
    for (int j = -(mSize - i - 1); j <= mSize - i - 1; j++) {
      if (mC + j < 0 || mC + j >= N) continue;
      map[mR + i][mC + j] = mColor + '0';
    }
  }
}

void paint(int mR, int mC, int mColor) {
  int targetColor = map[mR][mC] - '0';
  if (targetColor == mColor) return;

  queue<pair<int, int>> q;

  visited[mR][mC] = id;
  map[mR][mC] = mColor + '0';
  q.push({mR, mC});

  while (!q.empty()) {
    pair<int, int> cur = q.front();
    q.pop();

    for (int d = 0; d < 4; d++) {
      int nr = cur.first + dr[d];
      int nc = cur.second + dc[d];

      if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;

      if (visited[nr][nc] == id || (map[nr][nc] - '0') != targetColor) continue;

      visited[nr][nc] = id;
      map[nr][nc] = mColor + '0';
      q.push({nr, nc});
    }
  }

  id++;
}

int getColor(int mR, int mC) { return map[mR][mC] - '0'; }