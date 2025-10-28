#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;

/*
- 데드라인에 가장 가까운 곳에 새로운 강의 넣는다
- 만약 못넣으면 강의수 +1
- 한 번 증가한 강의수는 줄어들지 않는다
*/

struct qEle {
  int s, e;

  bool operator<(const qEle& b) const { return e > b.e; }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  // freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  vector<pii> timeList(N);
  for (int i = 0; i < N; i++) {
    cin >> timeList[i].first >> timeList[i].second;
  }

  sort(timeList.begin(), timeList.end());

  priority_queue<qEle> pq;
  for (int i = 0; i < N; i++) {
    int s = timeList[i].first;
    int e = timeList[i].second;

    if (pq.empty()) {
      pq.push({s, e});
    } else if (pq.top().e <= s) {
      pq.pop();
      pq.push({s, e});
    } else {
      pq.push({s, e});
    }
  }

  cout << pq.size() << '\n';

  return 0;
}
