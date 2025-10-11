#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include<iostream>
using namespace std;
extern void init(int L, int N);
extern int addBaseCamp(int mID, int mRow, int mCol, int mQuantity);
extern int findBaseCampForDropping(int K);

#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_DROP 3

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
        else if (query == CMD_ADD)
        {
            int mID, mRow, mCol, mQuantity;
            scanf("%d %d %d %d", &mID, &mRow, &mCol, &mQuantity);

            int ret = addBaseCamp(mID, mRow, mCol, mQuantity);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
        else if (query == CMD_DROP)
        {
            int K;
            scanf("%d", &K);
            int ret = findBaseCampForDropping(K);
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

///////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<vector>
#include<unordered_map>
#include<cmath>
#include<unordered_set>

using namespace std;

struct Base {
  int id, r, c, q;
  Base() {}
  Base(int _id, int _r, int _c, int _q): id(_id), r(_r), c(_c), q(_q) {}
};

Base baseList[20000+4];
int parent[20000+4];
int groupCnt[20000+4];
vector<int> bucket[30+1][30+1];
unordered_map<int, int> idToIdx;
unordered_set<int> parentSet;

int idxCnt, L, N;

void init(int _L, int _N)
{
  for(int i=0; i<20000+4; i++) {
    parent[i] = i;
    groupCnt[i] = 0;
  }
  for(int i=0; i<30+1; i++) {
    for(int j=0; j<30+1; j++) {
      bucket[i][j].clear();
    }
  }
  parentSet.clear();
  idToIdx.clear();
  idxCnt = 0;
  L = _L;
  N = _N;
}

int find(int x) {
  if(x == parent[x]) return x;
  else return parent[x] = find(parent[x]);
}

void unionTwo(int a, int b) {
  int pa = find(a);
  int pb = find(b);
  if(pa == pb) return;
  bool isAFirst  = true;
  if(baseList[pa].q < baseList[pb].q) {
    isAFirst = true;
  } else if(baseList[pa].q > baseList[pb].q) {
    isAFirst = false;
  } else if(baseList[pa].r < baseList[pb].r) {
    isAFirst = true;
  } else if(baseList[pa].r > baseList[pb].r) {
    isAFirst = false;
  } else if(baseList[pa].c < baseList[pb].c) {
    isAFirst = true;
  } else if(baseList[pa].c > baseList[pb].c) {
    isAFirst = false;
  }

  if(isAFirst) {
    parent[pb] = pa;
    groupCnt[pa] += groupCnt[pb];
    parentSet.erase(pb);
  } else {
    parent[pa] = pb;
    groupCnt[pb] += groupCnt[pa];
    parentSet.erase(pa);
  }
}

int calcDist(int ia, int ib) {
  Base& a = baseList[ia];
  Base& b = baseList[ib];

  return abs(a.r - b.r) + abs(a.c - b.c);
}

int addBaseCamp(int mID, int mRow, int mCol, int mQuantity) // 3x3 check
{
  idToIdx[mID] = idxCnt;
  baseList[idxCnt] = {mID, mRow, mCol, mQuantity};
  groupCnt[idxCnt] = mQuantity;
  int br = mRow/500;
  int bc = mCol/500;
  parentSet.insert(idxCnt);

  for(int i=-1; i<=1; i++) {
    for(int j=-1; j<=1; j++) {
      int nr = br + i;
      int nc = bc + j;
      if(nr<0 || nr>N/L || nc<0 || nc>N/L)
        continue;

      for(int i=0; i<bucket[nr][nc].size(); i++) {
        if(calcDist(bucket[nr][nc][i], idxCnt) <= L) {
          unionTwo(bucket[nr][nc][i], idxCnt);
        }
      }
    }
  }
  bucket[br][bc].push_back(idxCnt);

  idxCnt++;
  
  return groupCnt[find(idxCnt-1)];
}

int findBaseCampForDropping(int K)
{
  int answer = -1;
  for(auto ele: parentSet) {
    if(groupCnt[ele] < K) continue;

    if(answer == -1) {
      answer = ele;
      continue;
    }
    
    if(baseList[ele].q < baseList[answer].q) {
      answer = ele;
    } else if(baseList[ele].q == baseList[answer].q && baseList[ele].r < baseList[answer].r) {
      answer = ele;
    } else if(baseList[ele].q == baseList[answer].q && baseList[ele].r == baseList[answer].r && baseList[ele].c < baseList[answer].c ) {
      answer = ele;
    }
  }
  if(answer == -1)
    return -1;

  return baseList[answer].id;
}