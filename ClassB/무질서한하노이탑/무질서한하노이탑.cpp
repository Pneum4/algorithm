#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using pii = pair<int, int>;

struct bufEle {
  int num, from, to, depth;
};

#define MAX_N 1000

deque<int> deq[3];
map<int, int> num2Pos;
vector<int> arr;
deque<bufEle> buffer;
bool isFinish;

void init(int N[3], int mDisk[3][MAX_N]) {
  for (int i = 0; i < 3; ++i) {
    deq[i].clear();
  }
  buffer.clear();
  num2Pos.clear();
  arr.clear();
  isFinish = false;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < N[i]; ++j) {
      arr.push_back(mDisk[i][j]);
      deq[i].push_front(mDisk[i][j]);
    }
  }

  int idx = 0;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < N[i]; ++j) {
      num2Pos[arr[idx++]] = i;
    }
  }

  sort(arr.begin(), arr.end());
}

void destroy() {}
void stackSearch(int depth, int to) {
  if (depth == -1) {
    isFinish = true;
    return;
  }
  int cur = arr[depth];
  int from = num2Pos[cur];

  if (deq[from].back() == cur && (deq[to].back() > cur || deq[to].empty())) {
    buffer.push_back({cur, from, to, depth});
    return;
  }
  if (from == to) {
    stackSearch(depth - 1, to);
  } else {
    buffer.push_back({cur, from, to, depth});
    stackSearch(depth - 1, 3 - to - from);
  }
}

void go(int k, int mTop[3]) {
  if (isFinish) {
    mTop[0] = mTop[1] = 0;
    mTop[2] = 1;
    return;
  }

  int from, to;
  for (int i = 0; i < k; ++i) {
    if (buffer.empty()) {
      stackSearch(arr.size() - 1, 2);
    }

    bufEle last = buffer.back();
    // 불가능할때
    if (deq[last.from].back() != last.num ||
        (!deq[last.to].empty() && deq[last.to].back() < last.num)) {
      stackSearch(last.depth - 1, 3 - last.to - last.from);
    }

    if (isFinish) break;

    from = buffer.back().from;
    to = buffer.back().to;
    buffer.pop_back();

    int fromNum = deq[from].back();
    deq[from].pop_back();
    deq[to].push_back(fromNum);
    num2Pos[fromNum] = to;

    if (deq[0].empty() && deq[1].empty()) {
      isFinish = true;
      break;
    }
  }

  mTop[0] = deq[0].empty() ? 0 : deq[0].back();
  mTop[1] = deq[1].empty() ? 0 : deq[1].back();
  mTop[2] = deq[2].empty() ? 0 : deq[2].back();
}
