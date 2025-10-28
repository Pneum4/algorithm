#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using pii = pair<int, int>;

/*
좌표에 매몰되면 안된다
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  // freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  vector<pii> lineList(N);
  for (int i = 0; i < N; i++) {
    cin >> lineList[i].first >> lineList[i].second;
  }

  sort(lineList.begin(), lineList.end());

  int last = -2e9, answer = 0;
  for (int i = 0; i < N; i++) {
    int s = lineList[i].first;
    int e = lineList[i].second;

    if (last >= e)
      continue;
    else {
      if (s <= last) {
        answer += (e - last);
      } else {
        answer += (e - s);
      }
      last = e;
    }
  }

  cout << answer << '\n';

  return 0;
}
