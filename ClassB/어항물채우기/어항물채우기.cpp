#define MAX_WIDTH 500
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

// 버킷 + 카운터 배열 문제
// 디버깅
// - 4버킷 -> 64버킷 으로 바꾸니까 통과함

struct Result {
  int ID;
  int height;
  int used;
};

unordered_map<int, int> idToSeq, seqToId;
set<int> shapeIdx[64];  // 0~19 * idx
vector<vector<int>> heightList(20, vector<int>(500, 0)),
    shapeList(20, vector<int>(500, 0));
int N, W, H;

int toKey(int a, int b, int c) { return (a << 4) + (b << 2) + c; }

void init(int _N, int mWidth, int mHeight, int mIDs[],
          int mLengths[][MAX_WIDTH], int mUpShapes[][MAX_WIDTH]) {
  N = _N;
  W = mWidth;
  H = mHeight;
  idToSeq.clear();
  seqToId.clear();
  for (int i = 0; i < 64; i++) {
    shapeIdx[i].clear();
  }

  map<int, int> tmpId;
  vector<vector<int>> tmpHeight(N, vector<int>(W, 0));
  vector<vector<int>> tmpShape(N, vector<int>(W, 0));

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < W; j++) {
      tmpHeight[i][j] = mLengths[i][j];
      tmpShape[i][j] = mUpShapes[i][j];
    }
  }

  for (int i = 0; i < N; i++) {
    tmpId.insert({mIDs[i], i});
  }

  auto iter = tmpId.begin();
  for (int i = 0; i < N; i++) {
    heightList[i] = tmpHeight[(*iter).second];
    shapeList[i] = tmpShape[(*iter).second];
    idToSeq.insert({(*iter).first, i});
    seqToId.insert({i, (*iter).first});
    iter++;
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < W - 2; j++) {
      int curShape =
          toKey(shapeList[i][j], shapeList[i][j + 1], shapeList[i][j + 2]);
      shapeIdx[curShape].insert(i * W + j);
    }
  }
}

int checkStructures(int mLengths[], int mUpShapes[], int mDownShapes[]) {
  int ds1 = mDownShapes[0], ds2 = mDownShapes[1], ds3 = mDownShapes[2];
  int h1 = mLengths[0], h2 = mLengths[1], h3 = mLengths[2];
  int us1 = mUpShapes[0], us2 = mUpShapes[1], us3 = mUpShapes[2];
  int cnt = 0;
  int dsKey = toKey(ds1, ds2, ds3);

  for (auto iter = shapeIdx[dsKey].begin(); iter != shapeIdx[dsKey].end();
       iter++) {
    int box = (*iter) / W;
    int idx = (*iter) % W;
    if (idx >= W - 2) continue;
    if (shapeList[box][idx] != ds1 || shapeList[box][idx + 1] != ds2 ||
        shapeList[box][idx + 2] != ds3)
      continue;
    if (heightList[box][idx] + h1 > H || heightList[box][idx + 1] + h2 > H ||
        heightList[box][idx + 2] + h3 > H)
      continue;
    if (heightList[box][idx] + h1 <= heightList[box][idx + 1] ||
        heightList[box][idx + 1] + h2 <= heightList[box][idx] ||
        heightList[box][idx + 1] + h2 <= heightList[box][idx + 2] ||
        heightList[box][idx + 2] + h3 <= heightList[box][idx + 1])
      continue;

    cnt++;
  }

  return cnt;
}

int addStructures(int mLengths[], int mUpShapes[], int mDownShapes[]) {
  int ds1 = mDownShapes[0], ds2 = mDownShapes[1], ds3 = mDownShapes[2];
  int h1 = mLengths[0], h2 = mLengths[1], h3 = mLengths[2];
  int us1 = mUpShapes[0], us2 = mUpShapes[1], us3 = mUpShapes[2];
  int cnt = 0, box = -1, idx = -1;
  bool find = false;
  int dsKey = toKey(ds1, ds2, ds3), usKey = toKey(us1, us2, us3);

  auto iter = shapeIdx[dsKey].begin();
  for (; iter != shapeIdx[dsKey].end(); iter++) {
    box = (*iter) / W;
    idx = (*iter) % W;

    if (idx >= W - 2) continue;
    if (shapeList[box][idx] != ds1 || shapeList[box][idx + 1] != ds2 ||
        shapeList[box][idx + 2] != ds3)
      continue;
    if (heightList[box][idx] + h1 > H || heightList[box][idx + 1] + h2 > H ||
        heightList[box][idx + 2] + h3 > H)
      continue;
    if (heightList[box][idx] + h1 <= heightList[box][idx + 1] ||
        heightList[box][idx + 1] + h2 <= heightList[box][idx] ||
        heightList[box][idx + 1] + h2 <= heightList[box][idx + 2] ||
        heightList[box][idx + 2] + h3 <= heightList[box][idx + 1])
      continue;

    find = true;
    break;
  }

  if (!find) return 0;

  heightList[box][idx] += h1;
  heightList[box][idx + 1] += h2;
  heightList[box][idx + 2] += h3;

  shapeList[box][idx] = us1;
  shapeList[box][idx + 1] = us2;
  shapeList[box][idx + 2] = us3;

  int fullIdx = box * W + idx;
  for (int i = idx - 2; i <= idx + 2; ++i) {
    if (i < 0 || i > W - 3) continue;
    int oldKey =
        toKey(shapeList[box][i], shapeList[box][i + 1], shapeList[box][i + 2]);
    shapeIdx[oldKey].erase(box * W + i);
  }

  for (int i = idx - 2; i <= idx + 2; ++i) {
    if (i < 0 || i > W - 3) continue;
    int newKey =
        toKey(shapeList[box][i], shapeList[box][i + 1], shapeList[box][i + 2]);
    shapeIdx[newKey].insert(box * W + i);
  }

  return seqToId[box] * 1000 + idx + 1;
}

Result pourIn(int mWater) {
  // id height used
  Result ret({0, 0, 0});

  for (int i = 0; i < N; i++) {
    vector<int> counter(H + 1, 0);
    for (int j = 0; j < W; j++) {
      counter[heightList[i][j]]++;
    }

    int remain = mWater;
    bool poured = false;
    int j = 1;

    for (; j < H; j++) {
      if (counter[j] == 0) continue;
      if (counter[j] > remain) break;

      poured = true;
      remain -= counter[j];
      counter[j + 1] += counter[j];
    }
    if (poured && j >= ret.height) {
      if (j == ret.height) {
        if (ret.used < mWater - remain) {
          ret.ID = seqToId[i];
          ret.height = j;
          ret.used = mWater - remain;
        }
      } else {
        ret.ID = seqToId[i];
        ret.height = j;
        ret.used = mWater - remain;
      }
    }
  }

  return ret;
}