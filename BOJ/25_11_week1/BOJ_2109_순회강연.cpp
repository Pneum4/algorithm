#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;

/*
BOJ 1781 컵라면 문제와 유사
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int N;
  cin >> N;

  vector<pii> scoreList(N);
  for (int i = 0; i < N; i++) {
    cin >> scoreList[i].second >> scoreList[i].first;
  }

  sort(scoreList.begin(), scoreList.end());

  priority_queue<int, vector<int>, greater<int>> pq;

  for (int i = 0; i < N; i++) {
    pq.push(scoreList[i].second);

    while (scoreList[i].first < pq.size()) {
      pq.pop();
    }
  }

  int answer = 0;
  while (!pq.empty()) {
    answer += pq.top();
    pq.pop();
  }

  cout << answer << '\n';

  return 0;
}
