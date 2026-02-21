#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;
/*
Sweeping 기법이라고 하는데 첨봄
*/

bool compareLines(const pii& a, const pii& b) {
  if (a.second == b.second)
    return a.first < b.first;
  else
    return a.second < b.second;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  vector<pii> position(N);
  for (int i = 0; i < N; i++) {
    int s, e;
    cin >> s >> e;
    if (s > e) swap(s, e);
    position[i] = {s, e};
  }
  int D;
  cin >> D;

  sort(position.begin(), position.end(), compareLines);

  priority_queue<int, vector<int>, greater<int>> pq;
  int answer = 0;

  for (int i = 0; i < N; i++) {
    if (position[i].second - position[i].first > D) continue;

    int curFirst = position[i].second - D;
    pq.push(position[i].first);

    while (!pq.empty() && pq.top() < curFirst) {
      pq.pop();
    }

    answer = max(answer, (int)pq.size());
  }

  cout << answer << endl;

  return 0;
}
