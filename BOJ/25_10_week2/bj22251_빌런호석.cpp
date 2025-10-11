#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("input.txt", "r", stdin);

  int N, K, P, X;
  cin >> N >> K >> P >> X;

  // [방법1]
  // 7seg의 각 위치를 bool 배열로 나타낸 후
  // 각 bool 배열의 모든 원소를 비교해서 반전 개수 찾기

  // top right bottom left middle
  bool onOff[10][7] = {{0, 0, 0, 0, 0, 0, 1},   // 0
                       {1, 0, 0, 1, 1, 1, 1},   // 1
                       {0, 0, 1, 0, 0, 1, 0},   // 2
                       {0, 0, 0, 0, 1, 1, 0},   // 3
                       {1, 0, 0, 1, 1, 0, 0},   // 4
                       {0, 1, 0, 0, 1, 0, 0},   // 5
                       {0, 1, 0, 0, 0, 0, 0},   // 6
                       {0, 0, 0, 1, 1, 1, 1},   // 7
                       {0, 0, 0, 0, 0, 0, 0},   // 8
                       {0, 0, 0, 0, 1, 0, 0}};  // 9
  int diff[10][10];
  memset(diff, 0, sizeof(diff));

  // 숫자간의 차이를 미리 계산해놓기
  for (int i = 0; i < 10; i++) {
    for (int j = i + 1; j < 10; j++) {
      int cnt = 0;
      for (int k = 0; k < 7; k++) {
        if (onOff[i][k] != onOff[j][k]) {
          cnt++;
        }
      }
      diff[i][j] = diff[j][i] = cnt;
    }
  }

  // [방법2]
  // 7seg의 각 위치를 2진수 숫자로 나타낸 후
  // 2개씩 xor 시켜서 비트가 다른 위치의 개수를 찾고
  // popcount()함수로 xor(다른가?) 결과값의 1개수를 센다

  int bits[10] = {
      0b1111110,  // 0
      0b0110000,  // 1
      0b1101101,  // 2
      0b1111001,  // 3
      0b0110011,  // 4
      0b1011011,  // 5
      0b1011111,  // 6
      0b1110000,  // 7
      0b1111111,  // 8
      0b1111011   // 9
  };

  // int diff[10][10];
  memset(diff, 0, sizeof(diff));
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      // 서로 다른 비트만 1로
      int xorMask = bits[i] ^ bits[j];
      // 2진수의 1개수를 반환하는 함수
      diff[i][j] = __builtin_popcount(xorMask);
    }
  }

  // 여기 부분은 방법1 방법2 똑같음
  int answer = 0;
  for (int i = 1; i <= N; i++) {
    // X와 비교해서 반전 개수 찾기
    int mod = 10, ori = X, tar = i;
    int cnt = 0;
    for (int i = 0; i < K; i++) {
      cnt += diff[ori % mod][tar % mod];
      ori /= mod;
      tar /= mod;
    }
    if (cnt <= P) answer++;
  }
  // 자기 자신은 무조건 포함되니깐 1개 빼줘야됨
  cout << answer - 1 << '\n';

  return 0;
}
