#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
아이디어 떠오르기가 힘든 문제
-> LIS를 구하고 나머지 원소만 옮기면 최소이동 횟수이다
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin>>N;
    vector<int> answer;
    for(int i=0; i<N; i++) {
        int cur; cin>>cur;

        auto iter = lower_bound(answer.begin(), answer.end(), cur);

        if(iter == answer.end())
            answer.push_back(cur);
        else {
            *iter = cur;
        }
    }
    cout<<N-answer.size()<<endl;
    
    return 0;
}