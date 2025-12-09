#include <algorithm>
#include <iostream>
#include <list>
#include <tuple>
#include <vector>
using namespace std;
using tiii = tuple<int, int, int>;

/*
1라운드마다
lastPos로 가능한 후보군만 찾아서
그중에서 requireCoin 개수가 가장 작은거를 제거
*/

int solution(int coin, vector<int> cards) {
  int N = cards.size();
  vector<int> pair(N);
  for (int i = 0; i < N; i++) {
    pair[i] = N - cards[i] + 1;
  }
  vector<tiii> lastPos(N + 1);  // lastPos, value, idx
  for (int i = 0; i < N + 1; i++) {
    get<0>(lastPos[i]) = -1;
    get<1>(lastPos[i]) = i;
  }
  for (int i = 0; i < N; i++) {
    get<2>(lastPos[cards[i]]) = i;
  }

  for (int i = 0; i < N; i++) {
    tiii& cur = lastPos[cards[i]];
    if (get<0>(cur) < i) {
      get<0>(cur) = i;
    }

    tiii& cur2 = lastPos[pair[i]];
    if (get<0>(cur2) < i) {
      get<0>(cur2) = i;
    }
  }

  sort(lastPos.begin(), lastPos.end());

  int answer = 0, remainCoin = coin;
  for (int i = N / 3 + 1; i < N; i += 2) {  // 5 7 9 11
    int minReqCoin = 10, minIdx = -1;
    for (int j = 1; j + 1 < lastPos.size(); j += 2) {
      tiii a = lastPos[j], b = lastPos[j + 1];
      if (get<0>(a) > i) break;

      int reqCoin = 0;
      if (get<2>(a) >= N / 3) reqCoin++;
      if (get<2>(b) >= N / 3) reqCoin++;

      if (reqCoin > remainCoin) continue;

      if (minReqCoin > reqCoin) {
        minReqCoin = reqCoin;
        minIdx = j;
      }
    }

    if (minIdx == -1) break;

    remainCoin -= minReqCoin;
    lastPos.erase(lastPos.begin() + minIdx);
    lastPos.erase(lastPos.begin() + minIdx);
    answer++;
  }
  return answer + 1;
}

int main() {
  int coin = 4;
  vector<int> cards = {3, 6, 7, 2, 1, 10, 5, 9, 8, 12, 11, 4};

  cout << solution(coin, cards) << '\n';

  return 0;
}

/*
-1,0,0
1,5,0
1,8,1
5,4,5
5,9,4
6,1,2
6,12,6
7,2,3
7,11,7
9,3,8
9,10,9
11,6,10
11,7,11

3 6 7 2 1 10 5 9 8 12 11 4
107 6 1112 3 8 4 5  1  2 9
*/