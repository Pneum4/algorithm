#define MAX_N 350
#define MAX_ID 200
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using pii = pair<int, int>;

const int INF = 2e9;
int dr[4] = {0, 1, 0, -1};  // r d l u
int dc[4] = {1, 0, -1, 0};
int N, L;
vector<vector<int>> map, visited;
vector<vector<pii>> graph;
vector<vector<int>> dist;

void init(int _N, int mRange, int mMap[MAX_N][MAX_N]) {
  N = _N;
  L = mRange;
  map.assign(N, vector<int>(N, 0));
  graph.assign(MAX_ID + 2, vector<pii>());
  visited.assign(N, vector<int>(N, 0));
  dist.assign(MAX_ID + 2, vector<int>(MAX_ID + 2, INF));

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      map[i][j] = mMap[i][j];
    }
  }

  return;
}

void add(int mID, int mRow, int mCol) {
  int id = mID + 2;
  map[mRow][mCol] = id;

  queue<pii> q;
  q.push({mRow, mCol});
  visited[mRow][mCol] = id;

  int count = 0;
  while (!q.empty()) {
    int size = q.size();
    if (count++ == L) break;
    for (int i = 0; i < size; ++i) {
      pii cur = q.front();
      q.pop();

      for (int d = 0; d < 4; ++d) {
        int nr = cur.first + dr[d];
        int nc = cur.second + dc[d];

        if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
        if (visited[nr][nc] == id || map[nr][nc] == 1) continue;

        if (map[nr][nc] >= 2) {
          int endId = map[nr][nc];
          graph[id].push_back({endId, count});
          graph[endId].push_back({id, count});
        }

        visited[nr][nc] = id;
        q.push({nr, nc});
      }
    }
  }

  for (int i = 2; i < MAX_ID + 2; ++i) {
    dist[i][i] = INF;
  }
}

int distance(int mFrom, int mTo) {
  int startId = mFrom + 2, endId = mTo + 2;

  if (dist[startId][startId] != INF) {
    return dist[startId][endId] == INF ? -1 : dist[startId][endId];
  }

  for (int i = 2; i < MAX_ID + 2; ++i) {
    dist[startId][i] = INF;
  }

  dist[startId][startId] = 0;

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push({0, mFrom + 2});

  while (!pq.empty()) {
    pii cur = pq.top();
    pq.pop();

    if (cur.first > dist[startId][cur.second]) continue;

    for (auto ele : graph[cur.second]) {
      int nd = ele.second + cur.first;
      if (nd < dist[startId][ele.first]) {
        dist[startId][ele.first] = nd;
        pq.push({nd, ele.first});
      }
    }
  }

  if (dist[startId][endId] == INF)
    return -1;
  else
    return dist[startId][endId];
}
