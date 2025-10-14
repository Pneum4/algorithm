#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// N=2000 이기 때문에 N^2으로 해결하는 방법 찾기

int main() {
    int N; cin>>N;
    vector<int> numList(N);
    for(int i=0; i<N; i++) {
        cin>>numList[i];
    }
    sort(numList.begin(), numList.end());
    
    int answer = 0;
    for(int i=0; i<N; i++) {
        int cur = numList[i];
        int l=0, r=N-1;
        bool find = false;
        while(l<r) {
            int sum = numList[l] + numList[r];
            if(sum == cur) {
                if(l!=i && r!= i) {
                    answer++;
                    break;
                }
                else if(l==i) l++;
                else if(r==i) r--;
            }
            else if(sum < cur) l++;
            else r--;
        }
    }
    cout<<answer<<endl;

    
    return 0;
}