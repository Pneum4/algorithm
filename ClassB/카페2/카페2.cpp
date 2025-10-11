#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <iostream>
using namespace std;
#define CMD_INIT            (100)
#define CMD_ORDER           (200)
#define CMD_SUPPLY          (300)
#define CMD_CANCEL          (400)
#define CMD_GET_STATUS      (500)
#define CMD_HURRY           (600)

struct RESULT
{
    int cnt;
    int IDs[5];
};

extern void init(int N);
extern int order(int mID, int M, int mBeverages[]);
extern int supply(int mBeverage);
extern int cancel(int mID);
extern int getStatus(int mID);
extern RESULT hurry();

#define MAX_NUM_BEVERAGES       (10)

static bool run()
{
    int Q, N, M;
    int mID, mBeverage;

    int mBeverages[MAX_NUM_BEVERAGES];

    int ret = -1, ans, cnt;

    RESULT res;

    scanf("%d", &Q);

    bool okay = false;

    for (int q = 0; q < Q; ++q)
    {
        int cmd;
        scanf("%d", &cmd);
        switch(cmd)
        {
        case CMD_INIT:
            scanf("%d", &N);
            init(N);
            okay = true;
            break;
        case CMD_ORDER:
            scanf("%d %d", &mID, &M);
            for (int i = 0; i < M; ++i)
                scanf("%d", &mBeverages[i]);
            ret = order(mID, M, mBeverages);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_SUPPLY:
            scanf("%d", &mBeverage);
            ret = supply(mBeverage);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_CANCEL:
            scanf("%d", &mID);
            ret = cancel(mID);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_GET_STATUS:
            scanf("%d", &mID);
            ret = getStatus(mID);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_HURRY:
            res = hurry();
            scanf("%d", &cnt);
            if (res.cnt != cnt)
                okay = false;
            for (int i = 0; i < cnt; ++i)
            {
                scanf("%d", &ans);
                if (res.IDs[i] != ans)
                    okay = false;
            }
            break;
        default:
            okay = false;
            break;
        }
    }

    return okay;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int TC, MARK;

    scanf("%d %d", &TC, &MARK);
    for (int tc = 1; tc <= TC; ++tc)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}

////////////////////////////////////////////////////////////////
#include<iostream>
#include<unordered_map>
#include<deque>
#include<set>
#include<string.h>

using namespace std;
using pii = pair<int, int>;

struct Order {
  int id;
  int bevCnt[11], fixedBevCnt[11];
};

Order orderList[20000 + 4];
deque<int> deq[11];
set<pii> sortedOrder;
unordered_map<int, int> idToIdx;

int idxCnt, orderCnt;

void init(int N)
{
  memset(orderList, 0, sizeof(orderList));
  for(int i=0; i<11; i++) {
    deq[i].clear();
  }
  sortedOrder.clear();
  idToIdx.clear();
  idxCnt = 0;
  orderCnt = 0;

  return;
}

int order(int mID, int M, int mBeverages[])
{
  Order& cur = orderList[idxCnt];
  cur.id = mID;
  for(int i=0; i<M; i++) {
    cur.fixedBevCnt[mBeverages[i]]++;
    cur.fixedBevCnt[0]++;
  }
  memcpy(cur.bevCnt, cur.fixedBevCnt, sizeof(cur.bevCnt));

  for(int i=1; i<=10; i++) {
    if(cur.fixedBevCnt[i] > 0)
      deq[i].push_back(idxCnt);
  }

  sortedOrder.insert({-cur.fixedBevCnt[0], idxCnt});

  idToIdx[mID] = idxCnt++;
  orderCnt++;
  
  return orderCnt;
}

int supply(int mBeverage)
{
  while(!deq[mBeverage].empty() && orderList[deq[mBeverage].front()].bevCnt[0] <= 0)
    deq[mBeverage].pop_front();
  
  if(deq[mBeverage].empty()) return -1;

  int curIdx = deq[mBeverage].front();

  sortedOrder.erase({ -orderList[curIdx].bevCnt[0], curIdx });
  orderList[curIdx].bevCnt[0]--;
  orderList[curIdx].bevCnt[mBeverage]--;

  if(orderList[curIdx].bevCnt[mBeverage] <= 0)
    deq[mBeverage].pop_front();
  
  if(orderList[curIdx].bevCnt[0] > 0)
    sortedOrder.insert({ -orderList[curIdx].bevCnt[0], curIdx });
  else
    orderCnt--;

  return orderList[curIdx].id;
}

int cancel(int mID)
{
  int curIdx = idToIdx[mID];
  Order& cur = orderList[curIdx];

  if(cur.bevCnt[0] <= 0)
    return cur.bevCnt[0];

  sortedOrder.erase({-cur.bevCnt[0], curIdx});
  int result = cur.bevCnt[0];
  cur.bevCnt[0] = -1;
  orderCnt--;
  for(int i=1; i<=10; i++) {
    int gap = cur.fixedBevCnt[i] - cur.bevCnt[i];
    for(int j=0; j<gap; j++) {
      supply(i);
    }
  }

  return result;
}

int getStatus(int mID)
{
  int curIdx = idToIdx[mID];

  return orderList[curIdx].bevCnt[0];
}

RESULT hurry()
{
    RESULT res;

    int cnt = 0;
    for(auto iter=sortedOrder.begin(); iter != sortedOrder.end(); iter++) {
      res.IDs[cnt] = orderList[(*iter).second].id;

      if(++cnt == 5) break;
    }
    res.cnt = cnt;

    return res;
}