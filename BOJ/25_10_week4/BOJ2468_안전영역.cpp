#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

/*
visited Token으로 dfs 100번 반복하면 풀리는 문제
*/

int N;
// visited token의 id는 차오른 물의 높이랑 동일
// 물의 높이 1~100까지 탐색하는데 id도 동일하게 부여함
vector<vector<int>> map, visited;
int dr[4] = { 1,0,-1,0 };
int dc[4] = { 0,1,0,-1 };

void dfs(int r, int c, int id) {
	for (int d = 0; d < 4; d++) {
		int nr = r + dr[d];
		int nc = c + dc[d];
		if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
		if (map[nr][nc] <= id || visited[nr][nc] == id) continue;

		visited[nr][nc] = id;
		dfs(nr, nc, id);
	}
}

int main() {
	//FILE *fp;
	//freopen_s(&fp, "input.txt", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N;
	map.assign(N, vector<int>(N, 0));
	visited.assign(N, vector<int>(N, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	int answer = 1;
	for (int id = 1; id <= 100; id++) {
		int result = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] <= id || visited[i][j] == id) continue;
				visited[i][j] = id;
				dfs(i, j, id);
				result++;
			}
		}
		answer = max(answer, result);

		if (result == 0) break;
	}

	cout << answer << endl;
}