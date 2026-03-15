#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  priority_queue<int> maxHeap;
  priority_queue<int, vector<int>, greater<int>> minHeap;

  int N;
  cin >> N;

  while (N--) {
    int in;
    cin >> in;

    if (maxHeap.size() == minHeap.size()) {
      maxHeap.push(in);
    } else {
      minHeap.push(in);
    }

    if (!maxHeap.empty() && !minHeap.empty() && maxHeap.top() > minHeap.top()) {
      int maxTop = maxHeap.top();
      int minTop = minHeap.top();

      maxHeap.push(minTop);
      minHeap.push(maxTop);

      maxHeap.pop();
      minHeap.pop();
    }

    cout << maxHeap.top() << '\n';
  }

  return 0;
}

/*
3 2 1 (small) - maxHeap
4 5 6 (big) - minHeap
*/