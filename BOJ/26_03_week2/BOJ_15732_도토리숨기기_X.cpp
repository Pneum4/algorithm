#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

struct rule {
  int a, b, c;
};

vector<int> boxList;
vector<rule> ruleList;

int calc(int ruleIdx, int num) {
  const rule& cur = ruleList[ruleIdx];

  int r = min(cur.b, num);
  int l = cur.a;
  int g = cur.c;

  if (l > num) return 0;
  return (r - l) / g + 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, K, D;
  cin >> N >> K >> D;
  boxList.assign(N + 1, 0);
  for (int i = 0; i < K; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    ruleList.push_back({a, b, c});
  }

  // 햇갈리면 (같다, 같다, 같다, rl 순서)
  int l = 1, r = N;
  int answer;
  while (l <= r) {
    int m = (l + r) / 2;

    ll sum = 0;
    for (int i = 0; i < (int)ruleList.size(); i++) {
      sum += calc(i, m);
      if (sum >= D) break;
    }

    if (sum >= D) {
      answer = m;
      r = m - 1;
    } else {
      l = m + 1;
    }
  }

  cout << answer << endl;

  return 0;
}
