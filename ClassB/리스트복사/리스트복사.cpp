#include <string.h>

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
using pii = pair<int, int>;

const int MAX_ORI = 10;
const int MAX_SIZE = 200'000;
const int MAX_COPY = 5'000;
const int MAX_UPDATE = 100'000;

int oriList[MAX_ORI + 1][MAX_SIZE + 4];
pii changeLog[MAX_ORI + MAX_COPY + MAX_UPDATE + 4];
// logIdx -> (-1, oriIdx) : 원본배열
// logIdx -> (-1, -1) : deep copy
// logIdx -> (idx, value) : update한 값
int pre[MAX_COPY + MAX_UPDATE + 4];   // logIdx -> prev logIdx
int lastLog[MAX_ORI + MAX_COPY + 4];  // arrIdx -> logIdx
// swallow copy는 last change를 따라가야됨
unordered_map<string, int> nameToArrIdx;  // name -> arrIdx

int oriIdx, logIdx, arrIdx;
void init() {
  oriIdx = 0;
  logIdx = 0;
  arrIdx = 0;
  nameToArrIdx.clear();
}

void makeList(char mName[], int mLength, int mListValue[]) {
  memcpy(oriList[oriIdx], mListValue, mLength * sizeof(int));
  changeLog[logIdx] = {-1, oriIdx};
  pre[logIdx] = -1;
  lastLog[arrIdx] = logIdx;
  nameToArrIdx[string(mName)] = arrIdx;

  oriIdx++;
  logIdx++;
  arrIdx++;
}

void copyList(char mDest[], char mSrc[], bool mCopy) {
  string src = string(mSrc);
  string dest = string(mDest);
  if (!mCopy) {
    nameToArrIdx[dest] = nameToArrIdx[src];
    return;
  }

  changeLog[logIdx] = {-1, -1};
  pre[logIdx] = lastLog[nameToArrIdx[src]];
  lastLog[arrIdx] = logIdx;
  nameToArrIdx[dest] = arrIdx;

  logIdx++;
  arrIdx++;
}

void updateElement(char mName[], int mIndex, int mValue) {
  string name = string(mName);
  changeLog[logIdx] = {mIndex, mValue};
  pre[logIdx] = lastLog[nameToArrIdx[name]];
  lastLog[nameToArrIdx[name]] = logIdx;

  logIdx++;
}

int element(char mName[], int mIndex) {
  string name = string(mName);
  int curArrIdx = nameToArrIdx[name];
  int curLogIdx = lastLog[curArrIdx];

  while (true) {
    pii& cur = changeLog[curLogIdx];
    if (cur.first == mIndex) {
      return cur.second;
    } else if (cur.first == -1 && cur.second != -1) {
      return oriList[cur.second][mIndex];
    }

    curLogIdx = pre[curLogIdx];
  }

  return 0;
}