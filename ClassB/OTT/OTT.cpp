#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#define CMD_INIT        (100)
#define CMD_ADD         (200)
#define CMD_ERASE       (300)
#define CMD_WATCH       (400)
#define CMD_SUGGEST     (500)

struct RESULT
{
    int cnt;
    int IDs[5];
};

extern void init(int N);
extern int add(int mID, int mGenre, int mTotal);
extern int erase(int mID);
extern int watch(int uID, int mID, int mRating);
extern RESULT suggest(int uID);

////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<unordered_set>
#include<list>

#define MAX_GENRE 5
#define MAX_MOVIE 10000
#define MAX_USER 1000

using namespace std;
using pii = pair<int,int>;

struct Movie {
  int genre, total, removed;
  unordered_set<int> watchUid;
};

int mIdx;

Movie movieList[MAX_MOVIE+1];
set<pii, greater<pii>> genreMovieList[MAX_GENRE + 1];
list<pii> userWatchList[MAX_USER+1];

map<int, int> midToIdx;
map<int, int> idxToMid;

void init(int N)
{
  mIdx = 0;
  for(int i=0; i<MAX_GENRE + 1; ++i) {
    genreMovieList[i].clear();
  }
  for(int i=0; i<MAX_USER; ++i) {
    userWatchList[i].clear();
  }
  midToIdx.clear();
  idxToMid.clear();

  return;
}

int add(int mID, int mGenre, int mTotal)
{
  if(midToIdx.count(mID) == 1) return 0;

  midToIdx[mID] = mIdx;
  idxToMid[mIdx] = mID;

  movieList[mIdx] = Movie{mGenre, mTotal, 0};
  genreMovieList[0].insert({mTotal, mIdx});
  genreMovieList[mGenre].insert({mTotal, mIdx});

  mIdx++;
  return 1;
}

int erase(int mID)
{ 
  if(midToIdx.count(mID) == 0)
    return 0;
  

  int curIdx = midToIdx[mID];
  Movie& curMovie = movieList[curIdx];

  if(curMovie.removed == 1) return 0;

  curMovie.removed = 1;
  genreMovieList[0].erase({curMovie.total, curIdx});
  genreMovieList[curMovie.genre].erase({curMovie.total, curIdx});

  midToIdx.erase(mID);
  idxToMid.erase(curIdx);

  return 1;
}

int watch(int uID, int mID, int mRating)
{
  if(midToIdx.find(mID) == midToIdx.end())
    return 0;

  int curIdx = midToIdx[mID];

  if(movieList[curIdx].watchUid.find(uID) != movieList[curIdx].watchUid.end())
    return 0;

  Movie& curMovie = movieList[curIdx];
  userWatchList[uID].push_front({curIdx, mRating});

  genreMovieList[0].erase({curMovie.total, curIdx});
  genreMovieList[curMovie.genre].erase({curMovie.total, curIdx});
  
  curMovie.total += mRating;
  // movieList[curIdx].total += mRating;
  genreMovieList[0].insert({curMovie.total, curIdx});
  genreMovieList[curMovie.genre].insert({curMovie.total, curIdx});

  movieList[curIdx].watchUid.insert(uID);

  return 1;
}

RESULT suggest(int uID)
{   
    RESULT res;

    int count = 0;
    int maxRating = 0, maxGenre = 0;

    auto iter = userWatchList[uID].begin();
    while(iter != userWatchList[uID].end() && count < 5) {
      int curIdx = (*iter).first;
      int curRating = (*iter).second;

      if(movieList[curIdx].removed == 1) {
        iter = userWatchList[uID].erase(iter);
        continue;
      } else {
        if(maxRating < curRating) {
          maxRating = curRating;
          maxGenre = movieList[curIdx].genre;
        }

        count++;
        iter++;
      }
    }

    count = 0;
    for(auto iter = genreMovieList[maxGenre].begin(); iter != genreMovieList[maxGenre].end(); ++iter) {
      int curIdx = iter->second;
      if(movieList[curIdx].watchUid.count(uID) == 1)
        continue;

      res.IDs[count++] = idxToMid[curIdx];
      
      if(count == 5) break;
    }
    res.cnt = count;

    return res;
}

static bool run()
{
    int Q, N;
    int mID, mGenre, mTotal, mRating, uID;
    
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
            scanf("%d", &N);
            init(N);
            okay = true;
            break;
        case CMD_ADD:
            scanf("%d %d %d", &mID, &mGenre, &mTotal);
            ret = add(mID, mGenre, mTotal);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_ERASE:
            scanf("%d", &mID);
            ret = erase(mID);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_WATCH:
            scanf("%d %d %d", &uID, &mID, &mRating);
            ret = watch(uID, mID, mRating);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_SUGGEST:
            scanf("%d", &uID);
            res = suggest(uID);
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


