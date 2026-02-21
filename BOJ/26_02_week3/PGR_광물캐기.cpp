#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
const int INF = 2e9;

/*
dfs or Greedy
*/

unordered_map<string, int> scoreMap[3];
vector<string> minerals;

int mineralSize = 0, answer = INF;

void stackSearch(int idx, vector<int>& remain, int rst) {
  if (idx >= mineralSize ||
      (remain[0] == 0 && remain[1] == 0 && remain[2] == 0)) {
    answer = min(answer, rst);
    return;
  }

  for (int i = 0; i < 3; i++) {
    if (remain[i] == 0) {
      continue;
    }
    remain[i]--;
    int nextRst = rst;
    int j = idx;
    for (; j < min(mineralSize, idx + 5); j++) {
      nextRst += scoreMap[i][minerals[j]];
    }

    stackSearch(j, remain, nextRst);
    remain[i]++;
  }
}

int solution(vector<int> picks, vector<string> _minerals) {
  mineralSize = _minerals.size();
  minerals = _minerals;
  scoreMap[0].insert({"diamond", 1});
  scoreMap[0].insert({"iron", 1});
  scoreMap[0].insert({"stone", 1});
  scoreMap[1].insert({"diamond", 5});
  scoreMap[1].insert({"iron", 1});
  scoreMap[1].insert({"stone", 1});
  scoreMap[2].insert({"diamond", 25});
  scoreMap[2].insert({"iron", 5});
  scoreMap[2].insert({"stone", 1});

  stackSearch(0, picks, 0);
  return answer;
}

/*
Gemini가 추천한 방법 -> DFS => Greedy
*/
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

struct Group {
  int diamond = 0;
  int iron = 0;
  int stone = 0;
  int total_score = 0;  // 정렬 기준 (가중치 합)
};

bool compare(const Group& a, const Group& b) {
  return a.total_score > b.total_score;
}

int solution(vector<int> picks, vector<string> minerals) {
  int answer = 0;
  int totalPicks = picks[0] + picks[1] + picks[2];

  // 1. 캘 수 있는 광물 범위 한정 (곡괭이 개수 vs 광물 수)
  int limit = min((int)minerals.size(), totalPicks * 5);
  vector<Group> groups;

  // 2. 5개씩 묶어서 가중치 계산
  for (int i = 0; i < limit; i += 5) {
    Group g;
    for (int j = i; j < min(i + 5, limit); j++) {
      if (minerals[j] == "diamond") {
        g.diamond++;
        g.total_score += 25;
      } else if (minerals[j] == "iron") {
        g.iron++;
        g.total_score += 5;
      } else {
        g.stone++;
        g.total_score += 1;
      }
    }
    groups.push_back(g);
  }

  // 3. 피로도가 높은 구간 순으로 정렬
  sort(groups.begin(), groups.end(), compare);

  // 4. 좋은 곡괭이부터 순서대로 할당
  for (auto& g : groups) {
    if (picks[0] > 0) {  // 다이아 곡괭이
      answer += (g.diamond + g.iron + g.stone);
      picks[0]--;
    } else if (picks[1] > 0) {  // 철 곡괭이
      answer += (g.diamond * 5 + g.iron + g.stone);
      picks[1]--;
    } else if (picks[2] > 0) {  // 돌 곡괭이
      answer += (g.diamond * 25 + g.iron * 5 + g.stone);
      picks[2]--;
    }
  }

  return answer;
}