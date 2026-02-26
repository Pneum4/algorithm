#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/*
투포인터 문제

자료구조 : map은 없는 원소에 접근하면 기본 생성자가 호출됨
  ummap[100]; -> 100이 없는 경우 {100, 0} 자동추가
  String은 "" 추가, char은 null문자 추가
*/

using namespace std;
const int INF = 2e9;

vector<int> solution(vector<string> gems) {
  unordered_set<string> distinctGem(gems.begin(), gems.end());
  int gemCard = distinctGem.size();
  int gemSize = gems.size();

  unordered_map<string, int> counter;

  vector<int> answer = {1, gemSize};

  int minSize = INF;
  int s = 0;
  for (int e = 0; e < gemSize; e++) {
    counter[gems[e]]++;

    while (counter.size() == gemCard) {
      int curSize = e - s + 1;

      if (curSize < minSize) {
        minSize = curSize;
        answer[0] = s + 1;
        answer[1] = e + 1;
      }

      counter[gems[s]]--;
      if (counter[gems[s]] == 0) {
        counter.erase(gems[s]);
      }
      s++;
    }
  }

  return answer;
}

/*
(map.erase 사용)
테스트 13 〉	통과 (11.97ms, 12.5MB)
테스트 14 〉	통과 (13.58ms, 12.4MB)
테스트 15 〉	통과 (13.83ms, 13.6MB)

(map.find 사용)
테스트 13 〉	통과 (16.38ms, 12.5MB)
테스트 14 〉	통과 (15.46ms, 12.5MB)
테스트 15 〉	통과 (18.03ms, 13.6MB)
*/