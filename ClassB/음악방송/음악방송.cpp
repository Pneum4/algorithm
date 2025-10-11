#include <unordered_map>
#include <vector>
using namespace std;

#define MAX_TIME 2000000               // 시간의 최댓값
#define MAX_LAZY ((MAX_TIME / 100) * 4) // 세그트리 노드 최대 크기 (여유있게 4배)

// 직원 구조체
struct WORKER {
    int active;   // 현재 활성 상태인지 (삭제되면 0)
    int start, end; // 출근/퇴근 시각

    void init(int mid, int mstart, int mend) {
        active = 1;
        start = mstart;
        end = mend;
    }
};

// 특정 시간 블록 단위로 직원들을 관리
// starts: 이 블록에서 출근한 직원 목록
// ends:   이 블록에서 퇴근한 직원 목록
struct {
    int cnt;
    vector<WORKER*> starts;
    vector<WORKER*> ends;    
} Schedule[MAX_TIME / 100 + 1];

// 직원 배열 (최대 5000명)
WORKER worker[5000];
int wcnt; // 현재 직원 수

// 세그먼트 트리 (lazy propagation)
int lazyCnt[MAX_LAZY]; // lazy 배열
int workCnt[MAX_LAZY]; // 실제 세그먼트 트리 값

unordered_map<int, int> wIDs; // 직원 ID -> worker 배열 인덱스 매핑
int mTime, maxLazy;           // 방송 시간 / 세그트리 구간 최대 크기

// 초기화
void init(int musicTime)
{
    wIDs.clear();
    wcnt = 0;

    mTime = musicTime;
    maxLazy = MAX_TIME / mTime; // 방송 길이 단위로 몇 개의 구간이 생기는지

    // Schedule[] 초기화
    for (int i = 0; i <= maxLazy; i++) {
        Schedule[i].cnt = 0;
        Schedule[i].ends.clear();
        Schedule[i].starts.clear();
    }

    // 세그먼트 트리 초기화
    for (int i = 0; i < MAX_LAZY; i++) {
        lazyCnt[i] = 0;
        workCnt[i] = 0;
    }
}

// lazy 적용
void lazyprop(int node, int st, int en) {
    if (lazyCnt[node]) {
        // 해당 구간의 직원 수를 업데이트
        workCnt[node] += (en - st + 1) * lazyCnt[node];
        if (st != en) { // 리프가 아니면 자식에게 lazy 전파
            lazyCnt[node * 2] += lazyCnt[node];
            lazyCnt[node * 2 + 1] += lazyCnt[node];
        }
        lazyCnt[node] = 0;
    }
}

// 세그먼트 트리 구간 업데이트
void lazy(int node, int st, int en, int left, int right, int val)
{
    lazyprop(node, st, en);
    if (left > en || right < st) return; // 구간 불일치

    if (left <= st && en <= right) { // 완전히 포함될 경우
        workCnt[node] += (en - st + 1) * val;
        if (st != en) {
            lazyCnt[node * 2] += val;
            lazyCnt[node * 2 + 1] += val;
        }
        return;
    }
    int mid = (st + en) / 2;
    lazy(node * 2, st, mid, left, right, val);
    lazy(node * 2 + 1, mid + 1, en, left, right, val);
    workCnt[node] = workCnt[node * 2] + workCnt[node * 2 + 1];
}

// 직원 제거 (세그트리에서 반영)
void remove_worker(WORKER *p)
{
    p->active = 0;

    // 직원의 근무 구간을 방송 길이 단위로 환산
    int start = p->start / mTime + 1;
    int end = p->end / mTime - 1;

    // 세그트리에서 해당 구간을 -1로 업데이트
    lazy(1, 1, maxLazy, start, end, -1);
}

// 직원 추가
void add(int mID, int mStart, int mEnd)
{
    // 이미 존재하는 ID면 제거 후 업데이트
    if (wIDs.find(mID) != wIDs.end()) {
        int idx = wIDs[mID];
        remove_worker(&worker[idx]);
    }

    // 새로운 worker 추가
    WORKER *w = &worker[wcnt];
    wIDs[mID] = wcnt;
    wcnt++;

    w->init(mID, mStart, mEnd);

    // 출근 시간에 해당하는 블록에 추가
    int start = mStart / mTime;
    Schedule[start].starts.push_back(w);
    start++;

    // 퇴근 시간에 해당하는 블록에 추가
    int end = mEnd / mTime;
    Schedule[end].ends.push_back(w);
    end--;

    // 세그트리에 직원의 근무 구간을 +1로 업데이트
    lazy(1, 1, maxLazy, start, end, 1);
}

// 직원 삭제
void remove(int mID)
{
    if (wIDs.find(mID) == wIDs.end()) return;

    int idx = wIDs[mID];
    wIDs.erase(mID);

    WORKER *w = &worker[idx];
    remove_worker(w);
}

// 세그먼트 트리에서 특정 인덱스의 값 얻기
int get_lazycnt(int node, int st, int en, int idx)
{
    lazyprop(node, st, en);
    if (idx > en || idx < st) return 0;

    if (st == en) {
        return workCnt[node];
    }

    int mid = (st + en) / 2;
    if (idx <= mid)
        return get_lazycnt(node * 2, st, mid, idx);
    return get_lazycnt(node * 2 + 1, mid + 1, en, idx);
}

// 음악방송 시작 시간(mBSTime)에 대해 들을 수 있는 직원 수 계산
int getCnt(int mBSTime)
{
    // 기본적으로 세그트리에서 해당 구간의 인원 수를 가져옴
    int cnt = get_lazycnt(1, 1, maxLazy, mBSTime / mTime);

    // 방송 시작 시간에 출근한 직원 처리
    for (WORKER *w : Schedule[mBSTime / mTime].starts) {
        if (w->active == 0) continue;
        if (w->start <= mBSTime) cnt++;
    }

    // 방송 종료 시간에 퇴근한 직원 처리
    int etime = mBSTime + mTime;
    for (WORKER *w : Schedule[mBSTime / mTime + 1].ends) {
        if (w->active == 0) continue;
        if (w->end < etime) cnt--;
    }

    return cnt;
}