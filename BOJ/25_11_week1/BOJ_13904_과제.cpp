#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;

/*
백준 1781와 동일한 문제 (이 문제는 N조건이 조금 느슨함)
- 데드라인이 3이면 현재까지 풀 수 있는 최대 문제수도 3개
- 최대 문제수를 유지하면서 모든 문제를 순회
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  // freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  vector<pii> taskList(N);
  for (int i = 0; i < N; i++) {
    cin >> taskList[i].first >> taskList[i].second;
  }

  sort(taskList.begin(), taskList.end());

  priority_queue<int, vector<int>, greater<int>> pq;

  for (int i = 0; i < N; i++) {
    pq.push(taskList[i].second);
    if ((int)pq.size() > taskList[i].first) pq.pop();
  }

  long long answer = 0;
  while (!pq.empty()) {
    answer += pq.top();
    pq.pop();
  }

  cout << answer << '\n';

  return 0;
}
