#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

const int BUCKET_SIZE = 25;
const int MAX_N = 10'000;
const int MAX_PRINT = 5'000;

struct printEle {
  int id, row, col, dir;
} printList[MAX_PRINT + 4];

vector<vector<int>> squareList[40 + 4];
int squareSize[40 + 4];
vector<int> bucket[MAX_N / BUCKET_SIZE + 1][MAX_N / BUCKET_SIZE + 1];

unordered_map<int, int> idToIdx;

int idxCnt, printCnt;
void init(int N) {
  for (int i = 0; i < MAX_N / BUCKET_SIZE + 1; i++) {
    for (int j = 0; j < MAX_N / BUCKET_SIZE + 1; j++) {
      bucket[i][j].clear();
    }
  }

  idToIdx.clear();

  idxCnt = 0;
  printCnt = 0;
}

void addPrint(int mID, int mSize, int mCnt, int mPixel[][3]) {  // 40
  idToIdx[mID] = idxCnt;
  squareList[idxCnt] = vector<vector<int>>(mSize);
  for (int i = 0; i < mSize; i++) {
    squareList[idxCnt][i] = vector<int>(mSize);
  }

  squareSize[idxCnt] = mSize;

  for (int i = 0; i < mCnt; i++) {
    int r = mPixel[i][0];
    int c = mPixel[i][1];
    int w = mPixel[i][2];
    squareList[idxCnt][r][c] = w;
  }
  vector<vector<int>>& cur = squareList[idxCnt];

  // 누적합
  for (int i = 0; i < mSize; i++) {
    for (int j = 0; j < mSize; j++) {
      cur[i][j] = cur[i][j] + (i > 0 ? cur[i - 1][j] : 0) +
                  (j > 0 ? cur[i][j - 1] : 0) -
                  (j > 0 && i > 0 ? cur[i - 1][j - 1] : 0);
    }
  }

  idxCnt++;
}

void pressPrint(int mID, int mRow, int mCol, int mDir) {  // 5000
  printEle& cur = printList[printCnt];
  cur.id = mID;
  cur.row = mRow;
  cur.col = mCol;
  cur.dir = mDir;

  int curIdx = idToIdx[mID];

  int sr = mRow;
  int sc = mCol;
  int er = mRow + squareSize[curIdx] - 1;
  int ec = mCol + squareSize[curIdx] - 1;

  for (int r = sr / BUCKET_SIZE; r <= er / BUCKET_SIZE; r++) {
    for (int c = sc / BUCKET_SIZE; c <= ec / BUCKET_SIZE; c++) {
      bucket[r][c].push_back(printCnt);
    }
  }

  printCnt++;
}

int calcDepth(int printIdx, int sr, int sc) {
  printEle& cur = printList[printIdx];
  int curIdx = idToIdx[cur.id];

  int psr = cur.row, psc = cur.col, per = cur.row + squareSize[curIdx],
      pec = cur.col + squareSize[curIdx];
  int gsr = sr, gsc = sc, ger = sr + 25, gec = sc + 25;
  int a = gsr - psr, b = gsc - psc, c = ger - psr, d = gec - psc;
  int size = squareSize[curIdx];
  a = (a < 0) ? 0 : (a > size ? size : a);
  b = (b < 0) ? 0 : (b > size ? size : b);
  c = (c < 0) ? 0 : (c > size ? size : c);
  d = (d < 0) ? 0 : (d > size ? size : d);
  if (a == size || b == size || c == 0 || d == 0) return 0;

  int ar, ac, br, bc;
  if (cur.dir == 0) {
    ar = a;  // ar이 0이되는 경우 존재
    ac = b;  // ac가 0이되는 경우 존재
    br = c;  // 0이 될수 없음
    bc = d;  // 0이 될수 없음
  } else if (cur.dir == 1) {
    ar = b;
    ac = squareSize[curIdx] - c;
    br = d;
    bc = squareSize[curIdx] - a;
  } else if (cur.dir == 2) {
    ar = squareSize[curIdx] - c;
    ac = squareSize[curIdx] - d;
    br = squareSize[curIdx] - a;
    bc = squareSize[curIdx] - b;
  } else if (cur.dir == 3) {
    ar = squareSize[curIdx] - d;
    ac = a;
    br = squareSize[curIdx] - b;
    bc = c;
  }
  vector<vector<int>>& curSquare = squareList[curIdx];
  int result = curSquare[br - 1][bc - 1] -
               ((ac > 0) ? curSquare[br - 1][ac - 1] : 0) -
               ((ar > 0) ? curSquare[ar - 1][bc - 1] : 0) +
               ((ar > 0 && ac > 0) ? curSquare[ar - 1][ac - 1] : 0);
  return result;
}

// 400 71 8 7324

int getDepth(int mRow, int mCol) {  // 1000

  int sr = mRow;
  int sc = mCol;
  unordered_set<int> visited;

  int sum = 0;
  for (int i = 0; i <= 1; i++) {
    for (int j = 0; j <= 1; j++) {
      for (int curIdx : bucket[sr / BUCKET_SIZE + i][sc / BUCKET_SIZE + j]) {
        if (visited.find(curIdx) != visited.end()) continue;
        visited.insert(curIdx);
        sum += calcDepth(curIdx, sr, sc);
      }
    }
  }

  return sum;
}