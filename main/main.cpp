#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int INF = 2e9;
vector<int> exclude;
vector<char> include;
int answer, N, M;

int findDigits(int num) {
  if (num == 0) return 1;
  int cnt = 0;
  while (num > 0) {
    num /= 10;
    cnt++;
  }
  return cnt;
}

void perm(string* cur, int depth) {
  if (depth == 7) return;

  if (!cur->empty()) {
    int curNum = stoi(*cur);
    int result = abs(curNum - N) + findDigits(curNum);
    answer = min(answer, result);
  }

  for (char ele : include) {
    cur->push_back(ele);
    perm(cur, depth + 1);
    cur->pop_back();
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M;
  exclude.assign(M, 0);

  for (auto& ele : exclude) cin >> ele;
  for (int i = 0; i < 10; i++) {
    auto iter = find(exclude.begin(), exclude.end(), i);
    if (iter == exclude.end()) {
      include.push_back(i + '0');
    }
  }

  answer = abs(N - 100);
  if (!include.empty()) {
    string base = "";
    perm(&base, 0);
  }

  cout << answer << '\n';
  return 0;
}
