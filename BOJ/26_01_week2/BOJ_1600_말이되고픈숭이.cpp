#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int INF = 2e9;

/*
1. dfs < bfs인 이유
  - 성공하면 바로 리턴 가능
2. visited 처리
  - horse 수까지 3차원 필요
*/


struct qEle
{
  int r, c, horse, dist;
};

int dhr[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dhc[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int K, C, R;
  cin >> K >> C >> R;

  if (R == 1 && C == 1) {
    cout << 0 << "\n";
    return 0;
  }

  vector<vector<bool>> map(R, vector<bool>(C, 0));
  vector<vector<vector<bool>>> visited(R,
    vector<vector<bool>>(C,
      vector<bool>(K+1, false)));

  for(int i=0; i<R; i++) {
    for(int j=0; j<C; j++) {
      int in; cin>>in;
      if(in == 1) map[i][j] = true;
    }
  }

  deque<qEle> q;
  q.push_back({0, 0, 0, 0});
  bool isFinish = false;
  int answer = INF;
  visited[0][0][0] = true;

  while (!q.empty())
  {
    qEle cur = q.front();
    q.pop_front();

    for (int d = 0; d < 4; d++)
    {
      int nr = cur.r + dr[d];
      int nc = cur.c + dc[d];

      if (nr < 0 || nr >= R || nc < 0 || nc >= C)
        continue;
      if (map[nr][nc] || visited[nr][nc][cur.horse])
        continue;

      if (nr == (R - 1) && nc == (C - 1))
      {
        isFinish = true;
        answer = cur.dist + 1;
        break;
      }
      
      visited[nr][nc][cur.horse] = true;
      q.push_back({nr, nc, cur.horse, cur.dist + 1});
    }

    if (isFinish)
      break;

    if (cur.horse == K)
      continue;

    for (int d = 0; d < 8; d++)
    {
      int nr = cur.r + dhr[d];
      int nc = cur.c + dhc[d];

      if (nr < 0 || nr >= R || nc < 0 || nc >= C)
        continue;
      if(map[nr][nc] || visited[nr][nc][cur.horse+1])
        continue;

      if (nr == (R - 1) && nc == (C - 1))
      {
        isFinish = true;
        answer = cur.dist + 1;
        break;
      }

      visited[nr][nc][cur.horse+1] = true;
      q.push_back({nr, nc, cur.horse + 1, cur.dist + 1});
    }

    if(isFinish) break;
  }

  if(answer == INF)
    cout<<-1<<endl;
  else 
    cout<<answer<<endl;

  return 0;
}
