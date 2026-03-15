#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int cnt[200000 + 4];
int parent[200000 + 4];
unordered_map<string, int> nameToId;
int nameIdx;

int find(int x) {
  if (x == parent[x])
    return x;
  else
    return parent[x] = find(parent[x]);
}

int unionTwo(int a, int b) {
  int pa = find(a);
  int pb = find(b);

  if (pa != pb) {
    parent[pb] = pa;
    cnt[pa] += cnt[pb];
  }
  return cnt[pa];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    nameToId.clear();
    nameIdx = 1;

    int N;
    cin >> N;
    int idA, idB;

    for (int i = 1; i <= 2 * N; i++) {
      parent[i] = i;
      cnt[i] = 1;
    }

    for (int i = 0; i < N; i++) {
      string a, b;
      cin >> a >> b;
      if (nameToId.find(a) == nameToId.end()) nameToId[a] = nameIdx++;
      if (nameToId.find(b) == nameToId.end()) nameToId[b] = nameIdx++;

      cout << unionTwo(nameToId[a], nameToId[b]) << '\n';
    }
  }

  return 0;
}
