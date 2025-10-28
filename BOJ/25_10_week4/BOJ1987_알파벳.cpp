#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
dfs + backtrack 방식을 이용하는 문제
시작점이 좌측 상단 1칸만 이용하는 것이라 visitedToken도 필요없다
*/

int R, C;
char board[20][20];
bool visitedAlpha[26]; // A ~ Z
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int answer = 0;

void dfs(int x, int y, int count) {
    answer = max(answer, count);
    
    for (int dir = 0; dir < 4; ++dir) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (nx >= 0 && ny >= 0 && nx < C && ny < R) {
            int alphaIdx = board[ny][nx] - 'A';
            if (!visitedAlpha[alphaIdx]) {
                visitedAlpha[alphaIdx] = true;
                dfs(nx, ny, count + 1);
                visitedAlpha[alphaIdx] = false; // backtrack
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> R >> C;
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            cin >> board[i][j];

    visitedAlpha[board[0][0] - 'A'] = true;
    dfs(0, 0, 1);

    cout << answer << '\n';
    return 0;
}
