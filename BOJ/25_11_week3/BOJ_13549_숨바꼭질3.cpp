#include <deque>
#include <iostream>
#include <vector>
using namespace std;

const int MAX = 100001;

/*
dp와 queue를 이용
dp 10만 -> 공간 복잡도 통과
최대 3*10만 -> 시간 복잡도 통과
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K;
  cin >> N >> K;

  vector<int> dist(MAX, -1);
  deque<int> dq;

  dist[N] = 0;
  dq.push_back(N);

  while (!dq.empty()) {
    int cur = dq.front();
    dq.pop_front();

    if (cur * 2 < MAX && dist[cur * 2] == -1) {
      dist[cur * 2] = dist[cur];  // 순간이동 (0초)
      dq.push_front(cur * 2);
    }

    if (cur - 1 >= 0 && dist[cur - 1] == -1) {
      dist[cur - 1] = dist[cur] + 1;
      dq.push_back(cur - 1);
    }

    if (cur + 1 < MAX && dist[cur + 1] == -1) {
      dist[cur + 1] = dist[cur] + 1;
      dq.push_back(cur + 1);
    }
  }

  cout << dist[K] << '\n';
  return 0;
}
