/*

대형이미지에 소형이미지를 찍어낸다.
특정 구간의 합을 반환해야 한다.


1.
getDepth 부터 설계해보자

25*25 = 625개 돌면서 더하면 된다?
getDepth x 625 = 1000 x 625 = 62.5만

엥 그럼 그냥 더하면 되잖아?

하지만 N(대형 이미지의 크기)는 최대 10,000이다.
25 x 25를 돌기 위해서는 10,000 x 10,000 짜리 배열이 필요하다.

10,000 x 10,000 x int(4byte) = 400MB
메모리 제한이 200MB 이므로... 배열 만들기가 불가능하다.


2.
그러면 배열을 다 만들지말고,
필요한 값만 가지고있는 2차원 map을 만들면 되지 않을까?
unordered_map<int,unordered_map<int,int>> big_map;
big_map[row][col] = value;

음..
map은 이론상 접근 복잡도가 1이지만,
오버헤드가 커서 계속 접근한다면 시간이 오래걸릴 수 있다.


3.
10,000 x 10,000 만드는게 부담스러운 것이니...
bucket으로 쪼개서 관리하자.

getDepth에서 25 x 25 크기의 정사각형을 확인하니까,
bucket크기는 25로 하고, getDepth에서 2x2개만 순회하게 하자.


4.
1개의 bucket에는 최대 5,000번의 pressPrint를 할 수 있다.
그리고 1개의 bucket의 print에는 최대 25 x 25개의 픽셀이 존재할 수 있다.
음......
그렇다면 getDepth는
getDepth x pressPrint x 25 x 25 =
1,000 x 5,000 x 25 x 25 =
31억...?

문제의 조건에 따라, 작은 소형이미지가 존재할 수도 있고
또... 최악의 경우가 많이 나오지 않을수도 있다.
이대로 구현할까?


5.
pressPrint에서 랜덤한 소형이미지를 만들어서 찍어버릴 수도 있는데...
굳이 이 문제에서는 addPrint로 40개의 소형이미지 틀을 만들어놓고,
그 틀대로만 찍게 하고있다.
왜지?

그렇다면 addPrint에서 40개의 소형이미지마다 전처리를 하면 괜찮지 않을까?
getDepth에서 구간 합을 매번 구해야하니까(25x25) 비효율적인 것 같다.
addPrint에서 구간 합을 미리 구해놓고, getDepth에서 바로 불러오자!


6.
addPrint 에서 구간합 구하기 
대충..
addPrint(10) x 700 x 700 = 490만

pressPrint에서 버킷에 소형이미지 ID 넣기
pressPrint x (700/25) x (700/25) = 392만

getDepth에서 버킷내의 이미지 돌면서 구간합 구하기
getDepth x pressPrint x 1 = 500만

굳.


7.
회전은..
addPrint에서 4방향 회전하며 구간합을 계속 구하면 4배가 더 걸린다.
getDepth에서 press된 방향에따라 구간합 위치를 계산해서 더하자!



후기
누적합을 사용하지 않고, 소형이미지도 버킷으로 나눠서 대형이미지 버킷에 추가하는 식으로 해도 괜찮다.
회전을 구현하는 것이 귀찮았던것 빼고 나머지 구현은 간단했다.
누적합에 vector말고 배열을 쓰면 더 빨라질것이다..!

*/


#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

using namespace std;

#define MAX_N (10000)
#define BUC_SIZE (25)

struct pp{
	int mID, mRow, mCol, mDir;
};
pp ppDB[5005];
int pp_idx;

unordered_map<int, int> id_to_idx_ap;
int ap_idx;
vector<vector<int>> dp[40];
int ap_size[40];

vector<int> big_buc[MAX_N / BUC_SIZE + 5][MAX_N / BUC_SIZE + 5];

void init(int N)
{
	pp_idx = 0;
	id_to_idx_ap.clear();
	ap_idx = 0;
	for(int i=0; i<=N/BUC_SIZE; i++){
		for(int j=0; j<=N/BUC_SIZE; j++){
			big_buc[i][j].clear();
		}
	}

}

void addPrint(int mID, int mSize, int mCnt, int mPixel[][3])
{
	int cur_idx = ap_idx;
	ap_idx++;

	id_to_idx_ap[mID] = cur_idx;

	ap_size[cur_idx] = mSize;

	dp[cur_idx] = vector<vector<int>>(mSize);
	for(int i=0; i<mSize; i++){
		dp[cur_idx][i] = vector<int>(mSize);
	}

	for(int i=0; i<mCnt; i++){
		int r = mPixel[i][0];
		int c = mPixel[i][1];
		dp[cur_idx][r][c] = mPixel[i][2];
	}

  // 핵심 : 누적합
	for(int i=0; i<mSize; i++){
		for(int j=0; j<mSize; j++){
			dp[cur_idx][i][j] = 
				dp[cur_idx][i][j]
				+ (i > 0 ? dp[cur_idx][i-1][j] : 0) +
				+ (j > 0 ? dp[cur_idx][i][j-1] : 0) 
				- (i > 0 && j > 0 ? dp[cur_idx][i-1][j-1] : 0);
		}
	}
}

void pressPrint(int mID, int mRow, int mCol, int mDir)
{
	int cur_idx = pp_idx;
	pp_idx++;
	ppDB[cur_idx] = {mID, mRow, mCol, mDir};

	int ap_idx = id_to_idx_ap[mID];
	for(int i=mRow/BUC_SIZE; i<=(mRow + ap_size[ap_idx] - 1)/BUC_SIZE; i++){
		for(int j=mCol/BUC_SIZE; j<=(mCol + ap_size[ap_idx] - 1)/BUC_SIZE; j++){
			big_buc[i][j].push_back(cur_idx);
		}
	}
}

int get_sum(int temp_pp, int mRow, int mCol){
	int temp_ap = id_to_idx_ap[ppDB[temp_pp].mID];
	
	int prs = ppDB[temp_pp].mRow;
	int pcs = ppDB[temp_pp].mCol;
	int pre = prs + ap_size[temp_ap];
	int pce = pcs + ap_size[temp_ap];

	int grs = mRow;
	int gcs = mCol;
	int gre = mRow + 25;
	int gce = mCol + 25;

	int frs = min(max(grs - prs, 0), ap_size[temp_ap]);
	int fcs = min(max(gcs - pcs, 0), ap_size[temp_ap]);
	int fre = min(max(gre - prs, 0), ap_size[temp_ap]);
	int fce = min(max(gce - pcs, 0), ap_size[temp_ap]);
	if (frs == ap_size[temp_ap] || fcs == ap_size[temp_ap] || fre == 0 || fce == 0) return 0;

	int ffrs, ffcs, ffre, ffce;

  // 핵심 : 돌리면서 누적합
	if(ppDB[temp_pp].mDir == 0){
		ffrs = frs;
		ffcs = fcs;
		ffre = fre;
		ffce = fce;
	} else if(ppDB[temp_pp].mDir == 1){
		ffrs = fcs;
		ffcs = ap_size[temp_ap] - fre;
		ffre = fce;
		ffce = ap_size[temp_ap] - frs;
	} else if(ppDB[temp_pp].mDir == 2){
		ffrs = ap_size[temp_ap] - fre;
		ffcs = ap_size[temp_ap] - fce;
		ffre = ap_size[temp_ap] - frs;
		ffce = ap_size[temp_ap] - fcs;
	} else if(ppDB[temp_pp].mDir == 3){
		ffrs = ap_size[temp_ap] - fce;
		ffcs = frs;
		ffre = ap_size[temp_ap] - fcs;
		ffce = fre;
	}

	return dp[temp_ap][ffre-1][ffce-1]
			- (ffrs > 0 ? dp[temp_ap][ffrs-1][ffce-1]: 0)
			- (ffcs > 0 ? dp[temp_ap][ffre-1][ffcs-1]: 0)
			+ (ffcs > 0 && ffrs > 0 ? dp[temp_ap][ffrs-1][ffcs-1]: 0);
}

int getDepth(int mRow, int mCol)
{
	int sum = 0;
	unordered_set<int> visit;
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			for(int temp_pp : big_buc[mRow/BUC_SIZE + i][mCol/BUC_SIZE + j]){
				if(visit.find(temp_pp) != visit.end()) continue;
				visit.insert(temp_pp);
				sum += get_sum(temp_pp, mRow, mCol);
			}
		}
	}
	return sum;
}