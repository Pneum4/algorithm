#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
트라이 삽입 로직
- 일단 현재 문자열의 자식으로 이동 (자식이 없으면 만듬)
- 현재 문자열의 처리 로직 실행
*/

struct Trie {
  bool isTerminal;
  int childCnt;
  Trie* child[10];

  Trie() : isTerminal(false), childCnt(0) { memset(child, 0, sizeof(child)); }

  ~Trie() {
    for (int i = 0; i < 10; i++)
      if (child[i]) delete child[i];
  }

  bool insert(const string& s) {
    Trie* cur = this;

    for (int i = 0; i < (int)s.size(); i++) {
      int curNum = s[i] - '0';

      if (cur->child[curNum] == nullptr) {
        cur->child[curNum] = new Trie();
        cur->childCnt++;
      }

      cur = cur->child[curNum];

      if (cur->isTerminal) return false;
    }

    if (cur->childCnt > 0) return false;

    cur->isTerminal = true;

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int T;
  cin >> T;
  while (T--) {
    Trie* head = new Trie();
    int N;
    cin >> N;

    bool isNo = false;
    while (N--) {
      string in;
      cin >> in;
      if (isNo) continue;

      bool result = head->insert(in);

      if (!result) {
        cout << "NO" << '\n';
        isNo = true;
      }
    }
    if (!isNo) cout << "YES" << '\n';
  }

  return 0;
}
