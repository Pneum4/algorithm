#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_REMOVE 3
#define CMD_NUMBER_OF_CROSS 4
#define CMD_PARTICIPANT 5

extern void init();
extern void add(int mX, int mY);
extern void remove(int mX, int mY);
extern int numberOfCross(int mID);
extern int participant(int mX, int mY);

/////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
using pib = pair<int, bool>;
/////////////////////////////////////////////////////////////////////////
static bool run() {
  int numQuery;

  int mX, mY, mID;

  int userAns, ans;

  bool isCorrect = false;

  scanf("%d", &numQuery);

  for (int i = 0; i < numQuery; ++i) {
    int cmd;
    scanf("%d", &cmd);

    switch (cmd) {
      case CMD_INIT:
        init();
        isCorrect = true;
        break;
      case CMD_ADD:
        scanf("%d %d", &mX, &mY);
        add(mX, mY);
        break;
      case CMD_REMOVE:
        scanf("%d %d", &mX, &mY);
        remove(mX, mY);
        break;
      case CMD_NUMBER_OF_CROSS:
        scanf("%d", &mID);
        userAns = numberOfCross(mID);
        scanf("%d", &ans);
        if (userAns != ans) {
          isCorrect = false;
        }
        break;
      case CMD_PARTICIPANT:
        scanf("%d %d", &mX, &mY);
        userAns = participant(mX, mY);
        scanf("%d", &ans);
        if (userAns != ans) {
          isCorrect = false;
        }
        break;
      default:
        isCorrect = false;
        break;
    }
    // if (isCorrect)
    //   cout << "#" << i + 1 << '\n';
    // else
    //   cout << "##" << i + 1 << '\n';
  }
  return isCorrect;
}

int main() {
  setbuf(stdout, NULL);
  freopen("sample_input.txt", "r", stdin);

  int T, MARK;
  scanf("%d %d", &T, &MARK);

  for (int tc = 1; tc <= T; tc++) {
    int score = run() ? MARK : 0;
    printf("#%d %d\n", tc, score);
  }

  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
using pib = pair<int, bool>;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1. 세로줄 개수가 99개 -> 99개 자료구조 만들기
// 2. 정렬된 상태에서 upper_bound를 쓰고 싶다 + 찾았을때 왼쪽인지 오른쪽인지
// 알아야된다 -> 99개 map을 사용
// 3. numberOfCross() 시간복잡도 500번 * 5000 * log 400000/100 = 2500000 * 12 =
// 27500000 (가능)
// 4. participant()는 반대로 타고 올라가면 될듯?
const int MAX_X = 100;

map<int, bool> yPos[MAX_X + 1];

void init() {
  for (int i = 0; i < MAX_X + 1; i++) {
    yPos[i].clear();
  }
}

void add(int mX, int mY) {
  yPos[mX].insert({mY, true});
  yPos[mX + 1].insert({mY, false});
}

void remove(int mX, int mY) {
  yPos[mX].erase(mY);
  yPos[mX + 1].erase(mY);
}

int numberOfCross(int mID) {
  int cx = mID, cy = 0;
  int cnt = 0;
  while (true) {
    map<int, bool> &curMap = yPos[cx];
    auto iter = curMap.upper_bound(cy);

    if (iter == curMap.end()) break;

    cnt++;
    cy = iter->first;
    cx += (iter->second ? 1 : -1);
  }

  return cnt;
}

int participant(int mX, int mY) {
  int cx = mX, cy = mY;
  while (true) {
    map<int, bool> &curMap = yPos[cx];
    auto iter = curMap.lower_bound(cy);
    if (iter == curMap.begin()) break;

    cy = prev(iter)->first;
    cx += (prev(iter)->second ? 1 : -1);
  }

  return cx;
}