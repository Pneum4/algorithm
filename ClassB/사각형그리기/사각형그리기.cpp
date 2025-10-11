#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <iostream>
using namespace std;
extern void init(int L, int N);
extern int draw(int mID, int mRow, int mCol, int mHeight, int mWidth);
extern int getRectCount(int mID);
extern int countGroup();

#define CMD_INIT 1
#define CMD_DRAW 2
#define CMD_RECT 3
#define CMD_CNT 4

static bool run()
{
    int query_num;
    scanf("%d", &query_num);

    int ans;
    bool ok = false;

    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);
        if (query == CMD_INIT)
        {
            int L, N;
            scanf("%d %d", &L, &N);
            init(L, N);
            ok = true;
        }
        else if (query == CMD_DRAW)
        {
            int mID, mRow, mCol, mHeight, mWidth;
            scanf("%d %d %d %d %d", &mID, &mRow, &mCol, &mHeight, &mWidth);
            int ret = draw(mID, mRow, mCol, mHeight, mWidth);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
        else if (query == CMD_RECT)
        {
            int mID;
            scanf("%d", &mID);
            int ret = getRectCount(mID);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
        else if (query == CMD_CNT)
        {
            int ret = countGroup();
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
    }
    
    return ok;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);
    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}

////////////////////////////////////////////////////////////////
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

struct Square {
  int id, r, c, h, w;
  Square() {}
  Square(int _id, int _r, int _c, int _h, int _w)
    :id(_id), r(_r), c(_c), h(_h), w(_w) { }
};

unordered_map<int, int> idToIdx;
Square squareList[15000+4];
vector<int> bucket[50+1][50+1];
int parent[15000+4];
int squareCount[15000+4];

int idxCnt, groupCnt;
void init(int L, int N){
  idToIdx.clear();
  for(int i=0; i<50+1; i++) {
    for(int j=0; j<50+1; j++) {
      bucket[i][j].clear();
    }
  }
  for(int i=0; i<15000+4; i++) {
    parent[i] = i;
    squareCount[i] = 1;
  }

  idxCnt = 0;
  groupCnt = 0;
  return;
}

int find(int x) {
  if(parent[x] == x) return x;
  else return parent[x] = find(parent[x]);
}

void unionTwo(int a, int b) {
  int pa = find(a);
  int pb = find(b);
  if(pa == pb) return;
  if(pa<pb) {
    parent[pb] = pa;
    squareCount[pa] += squareCount[pb];
  } else {
    parent[pa] = pb;
    squareCount[pb] += squareCount[pa];
  }
  groupCnt--;
}

bool isOverlap(int a, int b) {
  Square& sa = squareList[a];
  Square& sb = squareList[b];
  if(sa.r+sa.h-1 < sb.r || sb.r+sb.h-1 < sa.r) return false;
  if(sa.c+sa.w-1 < sb.c || sb.c+sb.w-1 < sa.c) return false;

  return true;
}

int draw(int mID, int mRow, int mCol, int mHeight, int mWidth){
  idToIdx[mID] = idxCnt;
  squareList[idxCnt] = {mID, mRow, mCol, mHeight, mWidth};
  groupCnt++;
  for(int r=mRow/100; r<=(mRow+mHeight-1)/100; r++) {
    for(int c=mCol/100; c<=(mCol+mWidth-1)/100; c++) {
      for(int i=0; i<bucket[r][c].size(); i++) {
        if(isOverlap(bucket[r][c][i], idxCnt)) {
          unionTwo(bucket[r][c][i], idxCnt);
        }
      }
      bucket[r][c].push_back(idxCnt);
    }
  }

  idxCnt++;
  
  return squareCount[find(idxCnt-1)];
}

int getRectCount(int mID){
  if(idToIdx.find(mID) == idToIdx.end())
    return 0;
  int curIdx = idToIdx[mID];
  return squareCount[find(curIdx)];
}

int countGroup(){
  return groupCnt;
}
