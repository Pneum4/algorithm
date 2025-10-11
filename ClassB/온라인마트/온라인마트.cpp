#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT		(100)
#define CMD_SELL		(200)
#define CMD_CLOSE_SALE	(300)
#define CMD_DISCOUNT	(400)
#define CMD_SHOW		(500)

struct RESULT
{
	int cnt;
	int IDs[5];
};

extern void init();
extern int sell(int mID, int mCategory, int mCompany, int mPrice);
extern int closeSale(int mID);
extern int discount(int mCategory, int mCompany, int mAmount);
extern RESULT show(int mHow, int mCode);

////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<set>
#include<map>
#include<algorithm>

#define maxCategory 5
#define maxCompany 5
#define maxItemNum 50000
#define INF 2e9
using namespace std;
using pii = pair<int,int>;

struct Item {
  int mId, category, company, price, removed; // price는 할인 안된 가격
};

set<pii> saleList[maxCategory+1][maxCompany+1]; // price, mId
int totalDiscount[maxCategory+1][maxCompany+1];
int saleSize[maxCategory+1][maxCompany+1];
Item itemArr[maxItemNum + 4];
map<int, int> mIdToIdx;
int idx;

void init()
{ 
  idx = 1;
  for(int i=0; i<=maxCategory; ++i) {
    for(int j=0; j<=maxCompany; ++j) {
      saleList[i][j].clear();
      totalDiscount[i][j] = 0;
      saleSize[i][j] = 0;
    }
  }  
  mIdToIdx.clear();

	return;
}

int sell(int mID, int mCategory, int mCompany, int mPrice)
{
  int nextPrice = mPrice + totalDiscount[mCategory][mCompany];
  saleList[mCategory][mCompany].insert({nextPrice, mID});
  saleSize[mCategory][mCompany]++;
  itemArr[idx] = { mID, mCategory, mCompany, nextPrice, 0 };
  mIdToIdx[mID] = idx++;
  
	return saleSize[mCategory][mCompany];
}

int closeSale(int mID)
{
  int itemIdx = mIdToIdx[mID];
  if(itemIdx == 0 || itemArr[itemIdx].removed == 1)
    return -1;

	Item &cur = itemArr[itemIdx];
  cur.removed = 1;

  saleSize[cur.category][cur.company]--;

  return cur.price - totalDiscount[cur.category][cur.company];
}

int discount(int mCategory, int mCompany, int mAmount)
{
  totalDiscount[mCategory][mCompany] += mAmount;
  int curDis = totalDiscount[mCategory][mCompany];
  set<pii>& cur = saleList[mCategory][mCompany];
  for(auto iter = cur.begin(); iter != cur.end(); ) {
    if(iter->first - curDis > 0) break;

    if(itemArr[mIdToIdx[iter->second]].removed == 0) {
      saleSize[mCategory][mCompany]--;
      itemArr[mIdToIdx[iter->second]].removed = 1;
    }
    
    iter = saleList[mCategory][mCompany].erase(iter);
  }

	return saleSize[mCategory][mCompany];
}

RESULT show(int mHow, int mCode)
{
	RESULT res;
  int findNum[maxCategory+1][maxCompany+1] = {0};
  int count = 0;
  for(int i=0; i<5; ++i) {
    int minPrice = INF, minMid = 0, minCat=0, minComp=0;
    if(mHow == 1) {
      for(int j=1; j<=maxCompany; ++j) {
        auto iter = next(saleList[mCode][j].begin(), findNum[mCode][j]);
        while(itemArr[mIdToIdx[iter->second]].removed == 1 && iter != saleList[mCode][j].end()){
          iter++;
          findNum[mCode][j]++;
        }
        // if(iter == saleList[j][mCode].end()) continue;

        if(saleList[mCode][j].size() <= findNum[mCode][j])
          continue;

        int curPrice = iter->first - totalDiscount[mCode][j];
        if(minPrice == curPrice && minMid > iter->second) {
          minPrice = curPrice;
          minMid = iter->second;
          minComp = j;
        } if(minPrice > curPrice) {
          minPrice = curPrice;
          minMid = iter->second;
          minComp = j;
        }
      }
      findNum[mCode][minComp]++;
    } else if(mHow == 2) {
      for(int j=1; j<=maxCategory; ++j) {
        auto iter = next(saleList[j][mCode].begin(), findNum[j][mCode]);
        while(itemArr[mIdToIdx[iter->second]].removed == 1 && iter != saleList[j][mCode].end()) {
          iter++;
          findNum[j][mCode]++;
        }
        // if(iter == saleList[j][mCode].end()) continue;

        if(saleList[j][mCode].size() <= findNum[j][mCode])
          continue;

        int curPrice = iter->first - totalDiscount[j][mCode];
        if(minPrice == curPrice && minMid > iter->second) {
          minPrice = curPrice;
          minMid = iter->second;
          minCat = j;
        } else if(minPrice > curPrice) {
          minPrice = curPrice;
          minMid = iter->second;
          minCat = j;
        }
      }
      findNum[minCat][mCode]++;
    } else {
      for(int j=1; j<=maxCategory; ++j) {
        for(int k=1; k<=maxCompany; ++k) {
          auto iter = next(saleList[j][k].begin(), findNum[j][k]);
          while(itemArr[mIdToIdx[iter->second]].removed == 1 && iter != saleList[j][k].end()) {
            iter++;
            findNum[j][k]++;
          }
          // if(iter == saleList[j][k].end()) continue;

          if(saleList[j][k].size() <= findNum[j][k])
            continue;
        
          int curPrice = iter->first - totalDiscount[j][k];
          
          if(minPrice == curPrice && minMid > iter->second) {
            minPrice = curPrice;
            minMid = iter->second;
            minCat = j;
            minComp = k;
          } else if(minPrice > curPrice) {
            minPrice = curPrice;
            minMid = iter->second;
            minCat = j;
            minComp = k;
          }
        }
      }
      findNum[minCat][minComp]++;
    }
    if(minMid == 0) break;
    res.IDs[i] = minMid;
    count++;
  }
  res.cnt = count;

	return res;
}

////////////////////////////////////////////////////////////////////////

static bool run()
{
	int Q;
	int mID, mCategory, mCompany, mPrice, mAmount;
	int mHow, mCode;
	
	int ret = -1, cnt, ans;

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
			init();
			okay = true;
			break;
		case CMD_SELL:
			scanf("%d %d %d %d", &mID, &mCategory, &mCompany, &mPrice);
			ret = sell(mID, mCategory, mCompany, mPrice);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case CMD_CLOSE_SALE:
			scanf("%d", &mID);
			ret = closeSale(mID);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case CMD_DISCOUNT:
			scanf("%d %d %d", &mCategory, &mCompany, &mAmount);
			ret = discount(mCategory, mCompany, mAmount);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case CMD_SHOW:
			scanf("%d %d", &mHow, &mCode);
			res = show(mHow, mCode);
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