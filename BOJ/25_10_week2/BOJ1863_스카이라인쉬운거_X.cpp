#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 높이가 증가할때는 스택에 넣고
// 높이가 감소할때는 스택에서 빼는데
// 빼다가 높이가 같아지면 일단 넘어가고 나중에 처리한다
// 높이가 0인거는 빼는데 count로 치지는 않는다
// 조건분기처리 주의

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  deque<int> buffer;
  int answer = 0;
  for (int i = 0; i < N; i++) {
    int pos, cur;
    cin >> pos >> cur;
    while (!buffer.empty() && buffer.back() > cur) {
      if (buffer.back() > 0) answer++;
      buffer.pop_back();
    }
    if (!buffer.empty() && buffer.back() == cur) continue;

    buffer.push_back(cur);
  }

  while (!buffer.empty()) {
    if (buffer.back() > 0) answer++;
    buffer.pop_back();
  }

  cout << answer << '\n';

  return 0;
}
