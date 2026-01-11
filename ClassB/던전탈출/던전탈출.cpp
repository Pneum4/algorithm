#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <queue>
#include <functional>
#define MAP_SIZE_MAX 350
using namespace std;
using pii = pair<int, int>;
const int INF = 2e9;
const int maxGate = 200;

/*
  전기차대여소랑 똑같은 다익스트라 중복계산 최적화문제
  차이점은 지점 remove가 추가된 것
  - 2차원 vector graph 사용하면 remove 연산이 오래걸린다
  - 2차원 정적할당 graph 사용하면 remove 연산이 빠르다
*/

vector<vector<int>> map, visited;
vector<vector<int>> graph;
vector<vector<int>> dist;
vector<bool> needCalc;
vector<pii> gateIdToPos;
int _N, maxDist;

void init(int N, int mMaxStamina, int mMap[MAP_SIZE_MAX][MAP_SIZE_MAX])
{
  _N = N;

  // map
  map.assign(N, vector<int>(N, 0));
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      map[i][j] = mMap[i][j] == 1 ? -1 : 0;
    }
  }

  // visited
  visited.assign(N, vector<int>(N, 0));

  // graph
  graph.assign(maxGate + 1, vector<int>(maxGate + 1, INF));

  // dist
  dist.assign(maxGate + 1, vector<int>(maxGate + 1, INF));

  // needInit
  needCalc.assign(maxGate + 1, true);

  // maxDist
  maxDist = mMaxStamina;

  // gateIdToPos
  gateIdToPos.assign(maxGate + 1, {-1, -1});

  return;
}

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

void bfs(int id, int r, int c)
{
  deque<pii> q;
  q.push_back({r, c});
  visited[r][c] = id;
  int cnt = 0;
  while (!q.empty() && ++cnt <= maxDist)
  {
    int qSize = q.size();

    for (int i = 0; i < qSize; i++)
    {
      pii cur = q.front();
      q.pop_front();

      for (int d = 0; d < 4; d++)
      {
        int nr = cur.first + dr[d];
        int nc = cur.second + dc[d];

        if (nr < 0 || nr >= _N || nc < 0 || nc >= _N)
          continue;
        if (visited[nr][nc] == id || map[nr][nc] == -1)
          continue;

        if (map[nr][nc] > 0)
        {
          int e = map[nr][nc];
          graph[id][e] = min(graph[id][e], cnt);
          graph[e][id] = min(graph[e][id], cnt);
        }

        visited[nr][nc] = id;
        q.push_back({nr, nc});
      }
    }
  }

  return;
}

void addGate(int mGateID, int mRow, int mCol)
{
  for (int i = 1; i < maxGate + 1; i++)
  {
    needCalc[i] = true;
  }

  gateIdToPos[mGateID].first = mRow;
  gateIdToPos[mGateID].second = mCol;
  map[mRow][mCol] = mGateID;

  bfs(mGateID, mRow, mCol);

  return;
}

void removeGate(int mGateID)
{
  for (int i = 1; i < maxGate + 1; i++)
  {
    needCalc[i] = true;
  }

  pii curP = gateIdToPos[mGateID];
  map[curP.first][curP.second] = 0;
  gateIdToPos[mGateID].first = -1;
  gateIdToPos[mGateID].second = -1;

  for (int i = 1; i < maxGate; i++)
  {
    graph[mGateID][i] = INF;
    graph[i][mGateID] = INF;
  }

  return;
}

void dijkstra(int id)
{
  for (int i = 1; i < maxGate + 1; i++)
  {
    dist[id][i] = INF;
  }
  dist[id][id] = 0;

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push({0, id});
  while (!pq.empty())
  {
    pii cur = pq.top();
    pq.pop();

    if (cur.first > dist[id][cur.second])
      continue;

    for (int next = 1; next <= maxGate; next++)
    {
      if (graph[cur.second][next] == INF)
        continue;

      if (dist[id][cur.second] + graph[cur.second][next] < dist[id][next])
      {
        dist[id][next] = dist[id][cur.second] + graph[cur.second][next];
        pq.push({dist[id][next], next});
      }
    }
  }

  return;
}

int getMinTime(int mStartGateID, int mEndGateID)
{
  if (needCalc[mStartGateID])
  {
    dijkstra(mStartGateID);
    needCalc[mStartGateID] = false;
  }
  return dist[mStartGateID][mEndGateID] == INF ? -1 : dist[mStartGateID][mEndGateID];
}