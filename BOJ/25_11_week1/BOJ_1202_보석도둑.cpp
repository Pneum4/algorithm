#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;

/*
가방에 넣을 수 있는 보석 중에서 가장 비싼거를 넣으면 된다
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int N, K;
  cin >> N >> K;
  vector<pii> itemList(N);
  vector<int> bagList(K);

  for (int i = 0; i < N; i++) {
    cin >> itemList[i].first >> itemList[i].second;
  }

  for (int i = 0; i < K; i++) {
    cin >> bagList[i];
  }

  sort(bagList.begin(), bagList.end());
  sort(itemList.begin(), itemList.end());

  priority_queue<int> pq;
  int j = 0;
  long long answer = 0;
  for (int i = 0; i < K; i++) {
    int curBag = bagList[i];
    while (j < N && itemList[j].first <= curBag) {
      pq.push(itemList[j].second);
      j++;
    }
    if (!pq.empty()) {
      answer += pq.top();
      pq.pop();
    }
  }
  cout << answer << '\n';

  return 0;
}
