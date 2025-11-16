#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
using pii = pair<int, int>;
const int INF = 2e9;

vector<int> itemList;
vector<pii> answer;

/*
모노톤 스택
앞에서 부터 1번, 뒤에서부터 1번해서
2번 진행하면 된다.
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  itemList.assign(N, 0);
  answer.assign(N, {0, -INF});  // count, index

  for (auto& ele : itemList) {
    cin >> ele;
  }

  deque<pii> deq;  // height, index
  for (int i = 0; i < N; i++) {
    int cur = itemList[i];
    while (!deq.empty() && deq.back().first <= cur) {
      deq.pop_back();
    }

    answer[i].first += (int)deq.size();
    if (!deq.empty()) answer[i].second = deq.back().second;

    deq.push_back({cur, i + 1});
  }

  deq.clear();
  for (int i = N - 1; i >= 0; i--) {
    int cur = itemList[i];
    while (!deq.empty() && deq.back().first <= cur) {
      deq.pop_back();
    }

    answer[i].first += (int)deq.size();
    if (!deq.empty() &&
        abs(answer[i].second - (i + 1)) > abs(deq.back().second - (i + 1))) {
      answer[i].second = deq.back().second;
    }

    deq.push_back({cur, i + 1});
  }

  for (auto& ele : answer) {
    cout << ele.first;
    if (ele.second != -INF) cout << " " << ele.second;
    cout << '\n';
  }

  return 0;
}
