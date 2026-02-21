#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
using pii = pair<int, int>;
const int INF = 2e9;

/*
dijkstra + dp
*/

int cost[10][10];
int dist[4][3];
int dr[8] = {-1, 0, 1, 0, -1, 1, 1, -1};
int dc[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int posToNum[4][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {-1, 0, -1}};
int dp[2][10][10];

struct pqEle {
  int r, c, d;

  bool operator<(const pqEle& b) const { return d > b.d; }
};

void dijkstra(int r, int c) {
  fill(&dist[0][0], &dist[0][0] + 4 * 3, INF);
  dist[r][c] = 0;
  priority_queue<pqEle> pq;
  pq.push({r, c, 0});

  while (!pq.empty()) {
    pqEle cur = pq.top();
    pq.pop();

    if (cur.d > dist[cur.r][cur.c]) {
      continue;
    }

    for (int d = 0; d < 4; d++) {
      int nr = cur.r + dr[d];
      int nc = cur.c + dc[d];

      if (nr < 0 || nr >= 4 || nc < 0 || nc >= 3) {
        continue;
      }

      int nd = cur.d + 2;
      if (nd < dist[nr][nc]) {
        dist[nr][nc] = nd;
        pq.push({nr, nc, nd});
      }
    }
    for (int d = 4; d < 8; d++) {
      int nr = cur.r + dr[d];
      int nc = cur.c + dc[d];

      if (nr < 0 || nr >= 4 || nc < 0 || nc >= 3) {
        continue;
      }

      int nd = cur.d + 3;
      if (nd < dist[nr][nc]) {
        dist[nr][nc] = nd;
        pq.push({nr, nc, nd});
      }
    }
  }

  dist[r][c] = 1;
}

void assignCost(int num) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == 3 && j == 0) continue;
      if (i == 3 && j == 2) continue;
      cost[num][posToNum[i][j]] = dist[i][j];
    }
  }
}

int solution(string numbers) {
  memset(cost, 0, sizeof(cost));

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == 3 && j == 0) continue;
      if (i == 3 && j == 2) continue;
      dijkstra(i, j);
      assignCost(posToNum[i][j]);
    }
  }

  int size = numbers.size();
  fill(&dp[0][0][0], &dp[0][0][0] + 2 * 10 * 10, INF);
  dp[0][4][6] = 0;

  for (int i = 0; i < size; i++) {
    int curNum = numbers[i] - '0';
    int curIdx = (i + 1) % 2, preIdx = i % 2;

    fill(&dp[curIdx][0][0], &dp[curIdx][0][0] + 10 * 10, INF);

    for (int l = 0; l < 10; l++) {
      for (int r = 0; r < 10; r++) {
        if (dp[preIdx][l][r] == INF) {
          continue;
        }
        if (curNum != r) {
          dp[curIdx][curNum][r] =
              min(dp[curIdx][curNum][r], dp[preIdx][l][r] + cost[l][curNum]);
        }
        if (curNum != l) {
          dp[curIdx][l][curNum] =
              min(dp[curIdx][l][curNum], dp[preIdx][l][r] + cost[r][curNum]);
        }
      }
    }
  }

  int answer = INF;
  int last = size % 2;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      answer = min(answer, dp[last][i][j]);
    }
  }

  return answer;
}