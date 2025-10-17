#include<iostream>
#include<vector>
#include<algorithm>
#include<deque>
using namespace std;

//오른쪽으로 그림자를 비춰서 그림자 꼭지가 어디에 있는지 찾는 문제랑 비슷
//시퀸스 + 기준점의 한쪽에서 min/max 찾는다 = 스택사용
//최적화 ) vector에 push_back하고 reverse 하는것보다 미리 정적할당하고 뒤에서부터 넣는게 빠르지 않나?
//	-> 실제로 최적화를 해봤는데 시간차이가 없다

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int N; cin >> N;
	vector<int> seq(N, 0), answer;
	deque<int> stk;

	for (auto &ele : seq)
		cin >> ele;

	for (int i = N - 1; i >= 0; i--) {
		int cur = seq[i];
		if (stk.empty()) {
			stk.push_back(cur);
			answer.push_back(-1);
			continue;
		}
		while (!stk.empty() && stk.back() <= cur) {
			stk.pop_back();
		}

		if (stk.empty()) {
			answer.push_back(-1);
		}
		else {
			answer.push_back(stk.back());
		}

		stk.push_back(cur);
	}

	reverse(answer.begin(), answer.end());

	for (auto &ele : answer) {
		cout << ele << " ";
	}cout << endl;
}
