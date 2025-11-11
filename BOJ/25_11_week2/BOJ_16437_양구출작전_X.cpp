#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using pii = pair<int, int>;
using ll = long long;

int N;
vector<vector<int>> g;
vector<ll> val;

ll dfs(int cur) {
  ll sum = 0;
  for (int next : g[cur]) sum += dfs(next);  // visited 없이도 1번만 탐색함

  sum += val[cur];       // 양은 +, 늑대는 -값으로 저장
  if (sum < 0) sum = 0;  // 늑대가 더 많으면 0으로 컷

  return sum;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  cin >> N;
  g.assign(N + 1, vector<int>());
  val.assign(N + 1, 0);

  for (int i = 2; i <= N; i++) {
    char t;
    ll a;
    int p;
    cin >> t >> a >> p;
    g[p].push_back(i);
    val[i] = (t == 'S' ? a : -a);
  }

  cout << dfs(1) << '\n';
}
