#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  vector<vector<int>> manPreferOrder(N + 1, vector<int>(N + 1));
  vector<vector<int>> manToOrder(N + 1, vector<int>(N + 1));

  for (int i = 1; i <= N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> manPreferOrder[i][j];
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 0; j < N; j++) {
      int w;
      cin >> w;
      manToOrder[i][w] = j;
    }
  }

  vector<int> manSelect(N + 1, 0), womanSelect(N + 1, 0);
  vector<int> manSelectIdx(N + 1, 0);

  queue<int> q;
  for (int i = 1; i <= N; i++) {
    q.push(i);
  }

  while (!q.empty()) {
    int curMan = q.front();
    q.pop();

    int curWoman = manPreferOrder[curMan][manSelectIdx[curMan]];
    if (womanSelect[curWoman] == 0) {
      manSelect[curMan] = curWoman;
      womanSelect[curWoman] = curMan;
    } else {
      int preMan = womanSelect[curWoman];
      if (manToOrder[curWoman][preMan] > manToOrder[curWoman][curMan]) {
        // 지금이 선호하는 남자면
        q.push(preMan);
        manSelectIdx[preMan]++;
        manSelect[curMan] = curWoman;
        womanSelect[curWoman] = curMan;
      } else {
        q.push(curMan);
        manSelectIdx[curMan]++;
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    cout << manSelect[i] << "\n";
  }

  return 0;
}
