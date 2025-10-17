#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 1. 공유기 위치를 결정하고 최소거리인지 판단해볼까?
//     -> 좋은 방법이 떠오르지 않는다
// 2. 반대로 최소거리를 결정하고 공유기가 가능한지 판단해볼까?
//     -> 가능할 것 같다
// 3. 근데 가능한 거리 범위가 너무 넓은데 좋은 방법 없을까?
//     -> 거리3이 가능하다면 1~2도 고려할필요 없이 가능하다 = 이진탐색이 가능
// 4. 이진탐색으로 거리를 결정하고 공유기 설치가 가능한지 확인하자

int N, C;
vector<int> pos;

bool eval(int dist) {
    int cnt = C-1;
    for(int i=0; i<N; ) {
        int cp = pos[i];
        int next = -1;
        for(int j=i+1; j<N; j++) {
            if(pos[j] - cp >= dist) {
                next = j;
                break;
            }
        }
        if(next == -1) return false;
        
        i = next;
        if(--cnt == 0) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin>>N>>C;
    pos.assign(N, 0);

    int high = 0;
    for(auto &ele: pos) {
        cin>>ele;
        high = max(high, ele);
    }

    sort(pos.begin(), pos.end());
    
    int maxDist = (high-1)/(C-1);
    int left = 0, right = maxDist + 2; // 0부터라서 +1 하고, 이진탐색때문에 +1 하고
    int answer = 0;
    while(left<right) {
        int mid = (left+right)/2;
        bool result = eval(mid);
        if(result) {
            answer = mid;
            left = mid+1;
        } else {
            right = mid;
        }
    }
    
    cout<<answer<<endl;
    
    return 0;
}