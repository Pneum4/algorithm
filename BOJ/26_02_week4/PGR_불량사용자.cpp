#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<bool> visited;
set<int> answerSet;

bool checkContain(string& p, string& a) {
  if (p.size() != a.size()) return false;

  for (int i = 0; i < (int)p.size(); i++) {
    if (p[i] == '*') continue;
    if (p[i] != a[i]) return false;
  }

  return true;
}

void dfs(int idx, int bitmask, vector<string>& userId,
         vector<string>& bannedId) {
  if (idx == bannedId.size()) {
    answerSet.insert(bitmask);
    return;
  }

  for (int i = 0; i < userId.size(); i++) {
    if (visited[i]) continue;
    if (!checkContain(bannedId[idx], userId[i])) continue;

    visited[i] = true;
    int nextBitmask = bitmask | (1 << i);
    dfs(idx + 1, nextBitmask, userId, bannedId);
    visited[i] = false;
  }
}

int solution(vector<string> user_id, vector<string> banned_id) {
  visited.assign(user_id.size(), false);
  answerSet.clear();
  dfs(0, 0, user_id, banned_id);

  int answer = answerSet.size();
  return answer;
}