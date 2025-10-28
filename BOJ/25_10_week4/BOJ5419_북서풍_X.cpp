#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using pii = pair<int, int>;

/*
- 힌트 : x, y 중 하나를 좌표 정렬한다
- y좌표로 정렬했으면, y좌표의 범위는 -1e9~1e9 에서 0~75000이 된다
- 정렬 했으면 점들의 계산 순서가 중요한데 (x좌표 내림차순, y좌표 오름차순) 으로
계산해야한다
- 우선순위가 가장 낮은 좌표(가장 오른쪽 아래 좌표) 부터 계산해야 우선순위가 높은
좌표가 누적합을 이용할 수 있다
- 세그 트리로 누적합을 계산하는데 세그 1~2노드 합의 의미는 지금까지 계산한 y=1,
y=2 일때 좌표 총 개수이다
- 각 좌표를 순회하면서 누적합을 이용해서 북서풍으로 이동 가능한 좌표 개수를
반환받고, 자기 자신을 세그트리에 update한다
*/

int N;
vector<int> segTree;
vector<pii> pos;

int getCount(int node, int left, int right, int start, int end) {
  if (right < start || end < left) return 0;

  if (start <= left && right <= end) {
    return segTree[node];
  }

  int mid = (left + right) / 2;
  return getCount(2 * node, left, mid, start, end) +
         getCount(2 * node + 1, mid + 1, right, start, end);
}

void update(int node, int left, int right, int target) {
  if (right < target || target < left) return;

  if (left == right && left == target) {
    segTree[node]++;
    return;
  }

  int mid = (left + right) / 2;
  update(2 * node, left, mid, target);
  update(2 * node + 1, mid + 1, right, target);

  segTree[node] = segTree[node * 2] + segTree[node * 2 + 1];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;
  while (T--) {
    cin >> N;

    segTree.assign(N * 4, 0);
    pos.assign(N, {0, 0});

    for (int i = 0; i < N; i++) {
      cin >> pos[i].first >> pos[i].second;
    }

    sort(pos.begin(), pos.end(),
         [](const pii& a, const pii& b) { return a.second < b.second; });

    int id = 0, pre = 2e9;
    for (int i = 0; i < N; i++) {
      int cur = pos[i].second;
      if (cur == pre)
        pos[i].second = id;
      else {
        pos[i].second = ++id;
        pre = cur;
      }
    }

    sort(pos.begin(), pos.end(), [](const pii& a, const pii& b) {
      if (a.first != b.first)
        return a.first > b.first;
      else
        return a.second < b.second;
    });

    int answer = 0;
    for (int i = 0; i < N; i++) {
      answer += getCount(1, 1, N, 1, pos[i].second);
      update(1, 1, N, pos[i].second);
    }
    cout << answer << '\n';
  }

  return 0;
}
