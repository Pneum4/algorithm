#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> numList;
int N, M;

bool canDivide(int maxVal) {
  int cnt = 1;
  int sum = 0;
  for (int i = 0; i < N; i++) {
    if (numList[i] > maxVal) return false;
    if (sum + numList[i] > maxVal) {
      cnt++;
      sum = numList[i];
    } else {
      sum += numList[i];
    }
  }
  return cnt <= M;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  if (!(cin >> N >> M)) return 0;

  numList.assign(N, 0);
  int l = 0, r = 0;
  for (int i = 0; i < N; i++) {
    cin >> numList[i];
    l = max(l, numList[i]);
    r += numList[i];
  }

  int answer = r;
  while (l <= r) {
    int m = (l + r) / 2;
    if (canDivide(m)) {
      answer = m;
      r = m - 1;
    } else {
      l = m + 1;
    }
  }

  cout << answer << "\n";

  int sum = 0;
  int count = 0;
  for (int i = 0; i < N; i++) {
    sum += numList[i];
    if (sum > answer) {
      cout << count << " ";
      sum = numList[i];
      count = 1;
      M--;
    } else {
      count++;
    }

    if (N - i == M) {
      cout << count << " ";
      for (int j = 0; j < M - 1; j++) {
        cout << 1 << " ";
      }
      M = 0;
      break;
    }
  }
  if (M > 0) cout << count;
  cout << endl;

  return 0;
}