#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int INF = 2e9;

// 1. 최소 누름횟수? bfs인가?
//   -> 1회당 10만 번인데, 2회만 되어도 10만^2 이라 불가능하다
// 2. 그럼 겹치는 경우의수를 가지치기 하기위해 bfs+dp를 사용해 볼까?
//   -> 경우의 수가 2^10만개 인데, int 배열도 2^10만개가 필요할 것이라서 불가능
// 3. 그럼 최소를 찾는 방법은 그리디 밖에 없는데??
//   -> 모르겠다..
// 4. 000 -> 010 만들때 123번 스위치가 있다면
//   -> 1-3-2로 누르던 2-3-1로 누르던 상관없이 목표가 나오며, 순서상관없이
//   최소인 횟수가 3번으로 같다는 것을 발견
//   -> 그럼 같은 것은 중복해서 누르지 않고, 정답만 구할 수 있다면 그게
//   최소횟수인 정답이다
// 5. 정답을 반드시 구하는 방법은?
//   -> 맨왼쪽부터 눌러서 오른쪽까지 완성하는 방법이다
//   -> 1번째 전구는 2번째 전구로 반드시 목표 전구로 바꿀 수 있고 2번째 전구는
//   3번째 전구로 가능하다
// 6. 2~N번 전구는 1번째 전구가 확정되면 누르는 횟수가 고정이구나! 그런데 1번째
// 전구는?
//   -> 스위치를 누르거나, 누르지 않거나 2가지 경우가 둘다 가능
//   -> 경우의수가 2개라서 해보면 될 듯 하다 : O(10만 * 2)

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  string src, dest;
  cin >> src >> dest;

  // 2가지 경우를 봐야됨. 첫번째 스위치를 누른경우, 안누른경우
  // src:안누름, src2:누름
  string src2(src);
  for (int i = 0; i < 2; i++) {
    src2[i] = (src2[i] == '0' ? '1' : '0');
  }

  int answer = INF;
  for (int t = 0; t < 2; t++) {
    string cs;
    int cnt;
    if (t == 0) {
      cs = src;
      cnt = 0;
    } else if (t == 1) {  // src2의 경우 이미 1번 누른상태라서 cnt=1에서 시작
      cs = src2;
      cnt = 1;
    }

    // 2번째부터 마지막 스위치까지 필요한 경우 스위치 누르기
    for (int i = 1; i < N; i++) {
      if (cs[i - 1] != dest[i - 1]) {
        cnt++;
        for (int j = -1; j <= 1; j++) {
          cs[i + j] = (cs[i + j] == '0' ? '1' : '0');
        }
      }
    }

    // 1~N-1 까지 스위치는 반드시 같으므로 마지막 전구만 확인하면 됨
    if (cs[N - 1] == dest[N - 1]) {
      answer = min(answer, cnt);
    }
  }

  if (answer == INF)  // 경우의 수가 없는 경우
    cout << -1 << '\n';
  else
    cout << answer << '\n';

  return 0;
}
