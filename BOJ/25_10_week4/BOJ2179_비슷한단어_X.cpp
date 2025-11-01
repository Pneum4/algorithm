#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using psi = pair<string, int>;
using pis = pair<int, string>;

/*
1. 디버그
- 정렬 하고 나서도 원래 위치 정보를 알 수 있어야한다
- prefix 길이가 같은 경우 원래 위치 정보와 비교해서 추가해야되는데..
- 조건을 못만들어서 못풀었다

2. 해결방법
- 비교해야되는 조건이 복잡한경우
- 그냥 모든 가능성을 정답배열에 넣고
- 정답배열 중에서 찾아본다

*/

int findMaxPrefix(string& a, string& b) {
  int N = min(a.size(), b.size());
  int result = 0;
  for (int i = 0; i < N; i++) {
    if (a[i] != b[i]) break;
    result++;
  }
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  // freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  vector<psi> strArr(N);
  for (int i = 0; i < N; i++) {
    string in;
    cin >> in;
    strArr[i] = {in, i};
  }

  sort(strArr.begin(), strArr.end());

  vector<pis> answerList;

  int maxLen = 0;
  for (int i = 0; i + 1 < N; i++) {
    psi cur1 = strArr[i], cur2 = strArr[i + 1];

    int curLen = findMaxPrefix(cur1.first, cur2.first);

    if (cur1.second > cur2.second) swap(cur1, cur2);

    if (maxLen < curLen) {
      answerList.clear();
      maxLen = curLen;
      answerList.push_back({cur1.second, cur1.first});
      answerList.push_back({cur2.second, cur2.first});
    } else if (maxLen == curLen) {
      answerList.push_back({cur1.second, cur1.first});
      answerList.push_back({cur2.second, cur2.first});
    }
  }

  sort(answerList.begin(), answerList.end());

  pis answer1 = answerList[0], answer2;
  for (int i = 1; i < (int)answerList.size(); i++) {
    if (findMaxPrefix(answerList[i].second, answer1.second) == maxLen) {
      answer2 = answerList[i];
      break;
    }
  }
  cout << answer1.second << '\n';
  cout << answer2.second << '\n';

  return 0;
}
