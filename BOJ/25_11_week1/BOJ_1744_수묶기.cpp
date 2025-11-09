#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
수학문제 풀듯이 그리디하게 하면 됨
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // freopen("input.txt", "r", stdin);

  int N;
  cin >> N;
  vector<int> lte0, zeros, ones, gte2;  // less than equal , greater than equal
  for (int i = 0; i < N; i++) {
    int in;
    cin >> in;
    if (in < 0)
      lte0.push_back(in);
    else if (in == 0)
      zeros.push_back(in);
    else if (in == 1)
      ones.push_back(in);
    else
      gte2.push_back(in);
  }

  sort(lte0.begin(), lte0.end());
  sort(gte2.begin(), gte2.end(), greater<int>());

  int answer = 0;
  if ((int)lte0.size() % 2 == 1) {
    if (zeros.empty()) answer += lte0.back();
    lte0.pop_back();
  }
  if ((int)gte2.size() % 2 == 1) {
    answer += gte2.back();
    gte2.pop_back();
  }

  for (int i = 0; i < lte0.size() / 2; i++) {
    int fi = i * 2;
    answer += lte0[fi] * lte0[fi + 1];
  }

  for (int i = 0; i < gte2.size() / 2; i++) {
    int fi = i * 2;
    answer += gte2[fi] * gte2[fi + 1];
  }

  answer += (int)ones.size();

  cout << answer << '\n';

  return 0;
}
