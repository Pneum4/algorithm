#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
위상정렬
*/

vector<vector<bool>> orderMatrix;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    int N, M;
    cin >> N;
    orderMatrix.assign(N + 1, vector<bool>(N + 1, false));
    vector<int> ins(N), indegree(N + 1, 0);
    for (int i = 0; i < N; i++) {
      int in;
      cin >> ins[i];
    }

    for (int i = 0; i < N - 1; i++) {
      for (int j = i + 1; j < N; j++) {
        orderMatrix[ins[i]][ins[j]] = true;
        indegree[ins[j]]++;
      }
    }

    cin >> M;
    for (int i = 0; i < M; i++) {
      int s, e;
      cin >> s >> e;
      if (orderMatrix[s][e]) {
        orderMatrix[s][e] = false;
        orderMatrix[e][s] = true;
        indegree[s]++;
        indegree[e]--;
      } else {
        orderMatrix[s][e] = true;
        orderMatrix[e][s] = false;
        indegree[s]--;
        indegree[e]++;
      }
    }

    queue<int> q;
    for (int i = 1; i <= N; i++) {
      if (indegree[i] == 0) q.push(i);
    }

    vector<int> answer;

    bool finished = false;
    for (int i = 0; i < N; i++) {
      if (q.empty()) {
        cout << "IMPOSSIBLE" << endl;
        finished = true;
      }

      if (q.size() > 1) {
        cout << "?" << endl;
        finished = true;
      }

      if (finished) break;

      int cur = q.front();
      q.pop();

      answer.push_back(cur);
      for (int next = 1; next <= N; next++) {
        if (orderMatrix[cur][next]) {
          indegree[next]--;
          if (indegree[next] == 0) q.push(next);
        }
      }
    }
    if (!finished) {
      for (int i = 0; i < (int)answer.size(); i++) {
        cout << answer[i];
        if (i != (int)answer.size() - 1) cout << " ";
      }
      cout << endl;
    }
  }
  return 0;
}
