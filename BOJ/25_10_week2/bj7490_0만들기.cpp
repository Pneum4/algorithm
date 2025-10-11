#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N;
vector<string> answer;

// 전형적인 깊이 탐색 문제
// 백트래킹은 귀찮으니 그냥 새 문자열 생성해서 다음으로 넘김
// 만약 메모리 터지는 문제면 문자열 공간 1개만 잡고 백트래킹 해야될듯?

int calculate(string curStr) {
  string tmp;
  vector<int> numList;
  vector<char> opList;
  for (int i = 0; i < (int)curStr.size(); i++) {
    if (curStr[i] == ' ')
      continue;
    else if (curStr[i] == '+' || curStr[i] == '-') {
      numList.push_back(stoi(tmp));
      opList.push_back(curStr[i]);
      tmp.clear();
    } else {
      tmp.push_back(curStr[i]);
    }
  }
  numList.push_back(stoi(tmp));

  int result = numList.front();
  for (int i = 1; i < (int)numList.size(); i++) {
    if (opList[i - 1] == '+')
      result += numList[i];
    else
      result -= numList[i];
  }

  return result;
}

void stackSearch(int curNum, string curStr) {
  if (curNum == N) {
    if (calculate(curStr) == 0) answer.push_back(curStr);
    return;
  }
  int nextNum = curNum + 1;
  stackSearch(nextNum, curStr + " " + to_string(nextNum));
  stackSearch(nextNum, curStr + "+" + to_string(nextNum));
  stackSearch(nextNum, curStr + "-" + to_string(nextNum));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("input.txt", "r", stdin);

  int T;
  cin >> T;
  while (T--) {
    cin >> N;
    answer.clear();
    stackSearch(1, "1");

    sort(answer.begin(), answer.end());

    for (string &ele : answer) cout << ele << '\n';

    cout << '\n';
  }

  return 0;
}
