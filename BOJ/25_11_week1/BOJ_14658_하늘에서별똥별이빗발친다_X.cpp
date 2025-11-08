#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using pii = pair<int, int>;

/*
정답 사각형을 생각하자
정답 사각형은 여러개 일 수 있지만, 최대한 우 하 로 끌어 당겼을때 경우만
고려한다면 정답 사각형은 반드시 2가지 경우만 가능하다
1. 좌 상단 꼭지점에 점 1개가 있는 경우
2. 좌 상 변 각각에 점 2개가 있는 경우
따라서 꼭지점을 1~2 개씩 묶어서 좌상단 사각형을 그리면, 반드시 정답 사각형이
존재한다.
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int N, M, L, K;
  cin >> N >> M >> L >> K;

  vector<pii> pos(K);
  for (int i = 0; i < K; i++) {
    cin >> pos[i].first >> pos[i].second;
  }

  int answer = 0;
  for (int i = 0; i < K; i++) {
    // j = i + 1 로 하면은 82%에서 터진다
    for (int j = i; j < K; j++) {
      int up = min(pos[i].first, pos[j].first);
      int left = min(pos[i].second, pos[j].second);
      int down = up + L;
      int right = left + L;

      int count = 0;
      for (int k = 0; k < K; k++) {
        int r = pos[k].first;
        int c = pos[k].second;
        if (r >= up && r <= down && c >= left && c <= right) count++;
      }
      answer = max(answer, count);
    }
  }

  cout << K - answer << '\n';

  return 0;
}
