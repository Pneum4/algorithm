#include <deque>

using namespace std;

#define MAX_CARD 50000

struct Table {
  int joker;
  int begin, end;
  int cards[MAX_CARD * 2 + 5];
  deque<int> idxList[20][20];
  // idxList[joker][score] := 조커의 점수가 joker일 때, 점수가 score인 인덱스
  // 리스트 예를 들어, 현재 joker = 9점이고, findNumber의 타겟 점수가 19
  // 점이라면, 우리는 idxList[9][19] => 원하는 인덱스 리스트를 바로 알 수 있다.

  void updateIdx(
      int idx,
      int mdir)  // [idx ~ (idx + 3)] 의 네 장의 점수를 mdir 방향에 추가한다.
  {
    int sum = 0;        // 조커 이외의 총점
    int joker_cnt = 0;  // 조커 개수
    for (int i = 0; i < 4; i++) {
      if (cards[idx + i] == -1)
        joker_cnt++;
      else
        sum += cards[idx + i];
    }

    for (int i = 0; i < 20; i++)  // 조커의 점수를 i 로 가정해보자
    {
      int num = (sum + (joker_cnt * i)) % 20;
      if (mdir == 0)  // 왼쪽
        idxList[i][num].push_front(idx);
      else  // 오른쪽
        idxList[i][num].push_back(idx);
    }
  }

  void init(int mJoker, int mNumbers[5])  // 초기 5장과 조커로 초기화하기
  {
    joker = mJoker % 20;     // 조커 점수를 20으로 나눈 나머지로 초기화하기
    begin = end = MAX_CARD;  // 카드들의 처음, 끝 위치 초기화하기
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 20; j++) {
        idxList[i][j].clear();
      }
    }
    for (int i = 0; i < 5; i++) {
      cards[end + i] = mNumbers[i];
    }
    end += 5;
    for (int i = 0; i < 2; i++) {
      updateIdx(MAX_CARD + i, 1);
    }
  }

  void push_front(int mNumbers[5])  // 새로운 5 장을 왼쪽에 놓기
  {
    begin -= 5;
    for (int i = 0; i < 5; i++) {
      cards[begin + i] = mNumbers[i];
    }
    int target = begin;
    for (int i = 4; i >= 0; i--) {
      updateIdx(target + i, 0);
    }
  }

  void push_back(int mNumbers[5])  // 새로운 5 장을 오른쪽에 놓기
  {
    for (int i = 0; i < 5; i++) {
      cards[end + i] = mNumbers[i];
    }
    int target = end - 3;
    end += 5;
    for (int i = 0; i < 5; i++) {
      updateIdx(target + i, 1);
    }
  }

  int find(int mNum, int mNth)  // mNum 점수 중에 mNth 번째 위치 찾기
  {
    auto &list = idxList[joker][mNum];
    if (mNth > list.size()) return -1;
    return list[mNth - 1];
  }

  void changeJoker(int mJoker)  // 조커 점수 바꾸기
  {
    joker = mJoker % 20;
  }
};

Table t;

void init(int mJoker, int mNumbers[5]) { t.init(mJoker, mNumbers); }

void putCards(int mDir, int mNumbers[5]) {
  if (mDir == 0) {
    t.push_front(mNumbers);
  } else {
    t.push_back(mNumbers);
  }
}

int findNumber(int mNum, int mNth, int ret[4]) {
  int idx = t.find(mNum, mNth);
  if (idx == -1) return 0;
  for (int i = 0; i < 4; i++) {
    ret[i] = t.cards[idx + i];
  }
  return 1;
}

void changeJoker(int mValue) { t.changeJoker(mValue); }