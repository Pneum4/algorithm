#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using pii = pair<int, int>;

vector<pii> rawWoodList, woodList;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    int s, e;
    cin >> s >> e;
    rawWoodList.push_back({s, e});
  }

  sort(rawWoodList.begin(), rawWoodList.end());

  int curS = rawWoodList[0].first;
  int curE = rawWoodList[0].second;
  for (int i = 1; i < N; i++) {
    if (curE >= rawWoodList[i].first) {
      curE = max(curE, rawWoodList[i].second);
    } else {
      woodList.push_back({curS, curE});
      curS = rawWoodList[i].first;
      curE = rawWoodList[i].second;
    }
  }
  woodList.push_back({curS, curE});

  int maxJump = woodList[0].second * 2 - woodList[0].first;
  int answer = woodList[0].second;

  for (int i = 1; i < woodList.size(); i++) {
    if (woodList[i].first > maxJump) {
      break;
    }
    answer = max(answer, woodList[i].second);
    maxJump = max(maxJump, woodList[i].second * 2 - woodList[i].first);
  }

  cout << answer << endl;

  return 0;
}
