#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 전형적인 stackSearch 문제
// 앞에서부터 차례대로 1개로 묶을지 2개로 묶을지 선택해나간다

int N, answer, _N;
string in;

void stackSearch(int cur, int sum) {
  if (cur > N) {
    answer = max(answer, sum);
    return;
  }

  char op1 = 0, op2 = 0;
  int n1 = -1, n2 = -1;
  if (cur * 2 - 3 < _N) op1 = in[cur * 2 - 3];
  if (cur * 2 - 2 < _N) n1 = in[cur * 2 - 2] - '0';
  if (cur * 2 - 1 < _N) op2 = in[cur * 2 - 1];
  if (cur * 2 < _N) n2 = in[cur * 2] - '0';
  int ns = sum;
  if (op1 == '+') {
    ns += n1;
  } else if (op1 == '*') {
    ns *= n1;
  } else if (op1 == '-') {
    ns -= n1;
  }
  stackSearch(cur + 1, ns);

  if (op2 == 0 || n2 == -1) return;
  int ts = n1;
  if (op2 == '+') {
    ts += n2;
  } else if (op2 == '*') {
    ts *= n2;
  } else if (op2 == '-') {
    ts -= n2;
  }

  ns = sum;
  if (op1 == '+') {
    ns += ts;
  } else if (op1 == '*') {
    ns *= ts;
  } else if (op1 == '-') {
    ns -= ts;
  }
  stackSearch(cur + 2, ns);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> _N;
  N = (_N + 1 + 1) / 2;
  cin >> in;
  answer = -2e9;

  stackSearch(2, in[0] - '0');

  cout << answer << '\n';

  return 0;
}
