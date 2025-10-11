#include <string.h>

#include <iostream>
#define MAXL (10)
using namespace std;

struct trie {
  int cnt, isLeaf;
  trie* child[26];
};

trie root;
trie nodeList[1'000'000];

int nodeCnt, pageSize;

void addRemove(trie* cur, char word[MAXL + 1], int depth, int flag) {
  int curIdx = word[depth] - 'a';
  if (cur->child[curIdx] == nullptr) {
    memset(&nodeList[nodeCnt], 0, sizeof(nodeList[nodeCnt]));
    cur->child[curIdx] = &nodeList[nodeCnt++];
  }

  cur = cur->child[curIdx];
  cur->cnt += flag;

  if (word[depth + 1] == 0) {
    cur->isLeaf = flag;
    return;
  }

  addRemove(cur, word, depth + 1, flag);
}

void init(int N, char mWordList[][MAXL + 1], int mWordSize) {
  memset(&root, 0, sizeof(root));
  nodeCnt = 0;
  pageSize = N;

  for (int i = 0; i < mWordSize; i++) {
    addRemove(&root, mWordList[i], 0, 1);
  }
}

void addWord(char mWordList[][MAXL + 1], int mWordSize) {
  for (int i = 0; i < mWordSize; i++) {
    addRemove(&root, mWordList[i], 0, 1);
  }
}

void removeWord(char mWordList[][MAXL + 1], int mWordSize) {
  for (int i = 0; i < mWordSize; i++) {
    addRemove(&root, mWordList[i], 0, -1);
  }
}

char mRet[MAXL + 1];
char* findWord(int mPageNum)  // pageNum -> word
{
  memset(mRet, 0, sizeof(mRet));
  trie* cur = &root;
  int sum = 0, depth = 0;
  int target = (mPageNum - 1) * pageSize + 1;

  while (true) {
    if (sum == target && cur->isLeaf == 1) break;

    int i;
    for (i = 0; i < 26; i++) {
      if (cur->child[i] == nullptr) continue;
      if (sum + cur->child[i]->cnt >= target) break;
      sum += cur->child[i]->cnt;
    }

    mRet[depth++] = i + 'a';
    cur = cur->child[i];
    if (cur->isLeaf == 1) sum++;
  }
  mRet[depth] = 0;
  return mRet;
}

int findPage(char mWord[])  // word -> pageNum
{
  trie* cur = &root;
  int sum = 0, depth = 0;

  while (true) {
    if (mWord[depth] == 0) break;

    for (int i = 0; i < mWord[depth] - 'a'; i++) {
      if (cur->child[i] == nullptr) continue;
      sum += cur->child[i]->cnt;
    }
    if (cur->isLeaf == 1) sum++;
    cur = cur->child[mWord[depth] - 'a'];
    depth++;
  }

  return sum / pageSize + 1;
}