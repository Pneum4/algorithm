#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 1. dp로 미리 f1~fq를 계산해버리면
//   -> dp[q][N] 만큼 공간이 필요하고 (5만 * 2만)
//   -> 쿼리는 O(1) 복잡도로 반환이 가능하다 -> 공간복잡도 터짐

// 2. lca를 사용해서 f_(2^0)~f_(2^19)를 계산해버리면
//   -> dp[log2+1][N] 만큼 공간이 필요하고 (20 * 2만)
//   -> 쿼리는 O(log n) 복잡도로 반환이 가능하다 -> 쿼리가 조금 느리지만
//   공간복잡도 줄어듬

// 3. lca 공식
//   -> dp[k][n] = dp[k-1][dp[k-1][n]]
//   -> dp[k][n] : f_2^k (n) 의 함수값
//   -> f8(n) = f4(f4(n)) 임을 이용

// 4. 쿼리가 11인 경우 구하는 방법
//   -> f11(n) = f8(f2(f1(n)))

int N, Q, maxDepth;
vector<int> f;
vector<vector<int>> lca;  // Lowest Common Ancestor

void calcLCA() {
  for (int i = 1; i <= N; i++) {
    lca[0][i] = f[i];
  }

  for (int i = 1; i < maxDepth; i++) {
    for (int j = 1; j <= N; j++) {
      lca[i][j] = lca[i - 1][lca[i - 1][j]];
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;

  f.assign(N + 1, 0);
  for (int i = 1; i <= N; i++) cin >> f[i];

  maxDepth = ceil(log2(500'000)) + 1;

  cin >> Q;
  lca.assign(maxDepth, vector<int>(N + 1, 0));

  calcLCA();

  for (int i = 0; i < Q; i++) {
    int a, b;
    cin >> a >> b;

    int answer = b;
    for (int i = 0; i < maxDepth; i++) {
      if ((a & (1 << i)) != 0) {
        answer = lca[i][answer];
      }
    }

    cout << answer << '\n';
  }

  return 0;
}
