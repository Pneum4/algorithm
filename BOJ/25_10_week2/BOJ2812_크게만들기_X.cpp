#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 난이도 4️⃣점
// 중요도 4️⃣점
// 분노지수 1️⃣점

// 1. 완탐 불가능하니깐 당연하게 그리디를 생각했다
//   -> 그리디로 앞자리부터 가능한 모든 경우에서 가장 큰것만 고른다
//   -> 이전에 고른 idx 다음부터 ~ 뒤에서 남은개수만큼 뺀 곳까지 중에서 최솟값만
//   픽했으나 ..
//   -> O(n^2) 이라 2500억으로 터진다

// 2. 모르겠어서 힌트를 봤다 (스택)
//   -> 스택?? O(N)으로 해결하려면 순차로 전부 넣었을때 답이 나와야된다 ..

// 3. 스택에 대한 고민
//   -> 스택에 순차적으로 넣었을때 필요 없는 정보는 뭘까?
//   -> 스택 top보다 큰 값이 들어오면 기존 정보는 필요없겠다
//   -> 근데 스택 top보다 작은 값을 무시해버리면 나중에 넣는 숫자들의 비교대상이
//   없어진다
//   -> 스택 top보다 작은 값은 넣긴하는데, 큰 값이 오면 기존 작은 값들은
//   밀어버리자!

// 4. 시뮬레이션
//   -> 4177252841
//     41
//     772
//     7752
//     775841 (o)
//     77841 (x)
//   -> 시뮬로 조건을 하나 찾았다. 제거가 끝나면 스택 쌓기를 중지해야한다.
//   -> 제거가 끝났는데도 스택에서 1개라도 밀어버리면 숫자가 부족하다

// 5. 디버그
//   -> 4 2 4321 일때 delCnt=0 이고 4321이 나오는 문제 발생
//   -> 스택에서 원하는 만큼만 남겨야한다.

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("input.txt", "r", stdin);

  int N, K;
  cin >> N >> K;
  string in;
  cin >> in;

  deque<char> stk;
  int delCnt = 0;
  int i;
  for (i = 0; i < N; i++) {
    char curCh = in[i];

    while (!stk.empty() && stk.back() < curCh && delCnt < K) {
      stk.pop_back();
      delCnt++;
    }

    stk.push_back(curCh);
  }

  while (delCnt < K) {
    stk.pop_back();
    delCnt++;
  }

  string answer(stk.begin(), stk.end());
  cout << answer << '\n';

  return 0;
}
