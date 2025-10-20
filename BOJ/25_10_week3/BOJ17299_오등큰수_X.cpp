#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

// 문제)
//   -> 오른쪽에서 가장 큰 빈도수 숫자 반환 x
//   -> 오른쪽에서 현재보다 큰 빈도수 숫자중 가장 왼쪽것 반환 o
// 분석)
//   -> 빈도수가 작은 숫자라도 스택에 일단 넣어야됨

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<int> count(1'000'000 + 4, 0);
  vector<int> seq(N, 0), answer(N, 0);

  for (int i = 0; i < N; i++) {
    int in;
    cin >> in;
    seq[i] = in;
    count[in]++;
  }

  deque<int> stk;
  for (int i = N - 1; i >= 0; i--) {
    int cur = count[seq[i]];

    while (!stk.empty() && count[stk.back()] <= cur) {
      stk.pop_back();
    }

    if (stk.empty())
      answer[i] = -1;
    else
      answer[i] = stk.back();

    stk.push_back(seq[i]);
  }

  for (auto& ele : answer) cout << ele << " ";
}