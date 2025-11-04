#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;

/*
그리디 문제
1. 내 풀이
- 우선 데드라인이 급박한거부터 탐색한다
- 시간이 N이면 풀 수 있는 문제 개수도 N개 이다
- 시간이 1증가해서 N+1이 되면, 새로 문제를 푸는데
- 기존에 유지하던 N개 문제와 더불어 가장 컵라면 큰거 N+1개만 남긴다
- 기존에 유지하던 문제라도 나중에 들어온 문제가 컵라면이 더 크면 순위가 밀린다

2. GPT 최적화 풀이
- 데드라인이 3이면 현재까지 풀 수 있는 최대 문제수도 3개
- 최대 문제수를 유지하면서 모든 문제를 순회
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  // freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  vector<pii> eleList(N);
  for (int i = 0; i < N; i++) {
    cin >> eleList[i].first >> eleList[i].second;
  }

  sort(eleList.begin(), eleList.end());

  // GPT 최적화 풀이
  priority_queue<int, vector<int>, greater<int>> pq;

  int cur = 1;
  for (int i = 0; i < N; i++) {
    pq.push(eleList[i].second);
    if ((int)pq.size() > eleList[i].first) pq.pop();
  }

  // 내 풀이
  // priority_queue<pii, vector<pii>, greater<pii>> pq;
  // int cur = 1;
  // for (int i = 0; i < N;) {
  //   if (eleList[i].first > cur) {
  //     cur++;
  //     continue;
  //   }
  //   while (i < N && eleList[i].first <= cur) {
  //     pq.push({eleList[i].second, eleList[i].first});
  //     i++;
  //   }
  //   while (pq.size() > cur) pq.pop();
  //   cur++;
  // }

  long long answer = 0;
  while (!pq.empty()) {
    answer += pq.top();
    pq.pop();
  }

  cout << answer << '\n';

  return 0;
}