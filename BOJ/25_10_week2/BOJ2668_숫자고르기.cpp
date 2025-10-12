#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> arr, answer;
vector<int> visited;

// (경우의 수)
// 1. 완전탐색 -> 2^100 = 불가능
// 2. union-find로 사이클 찾기 -> parent 배열을 100번 초기화해야되어서 비효율
// 3. DFS -> visited 배열을 초기화하지 않는 방법을 이용하면 최적의 해를 구할 수
// 있다

// (인사이트)
// visited 배열을 여러번 초기화해야하는 경우
// visited를 int로 만들어서 해당 case에만 방문처리를 할 수 있다

void stackSearch(int cur, int start) {
  int next = arr[cur];
  if (visited[next] == start) {
    if (next == start) answer.push_back(start);
    return;
  }

  visited[next] = start;
  stackSearch(next, start);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("input.txt", "r", stdin);

  int N;
  cin >> N;

  arr.assign(N + 1, 0);
  for (int i = 1; i <= N; i++) {
    cin >> arr[i];
  }
  visited.assign(N + 1, 0);

  for (int i = 1; i <= N; i++) {
    visited[i] = i;
    stackSearch(i, i);
  }

  sort(answer.begin(), answer.end());

  cout << answer.size() << '\n';
  for (auto &ele : answer) cout << ele << '\n';

  return 0;
}
