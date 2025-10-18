import java.io.*;
import java.util.*;

// 그래프 기법없이 단순 구현-시뮬레이션 문제
// 난이도 3️⃣점
// 중요도 3️⃣점
// 분노지수 3️⃣점

public class Main {
  static int[] dr = { -1, 0, 1, 0 }; // n r s e
  static int[] dc = { 0, 1, 0, -1 };

  static enum State {
    DIRTY, CLEAN, WALL
  }

  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());
    int N = Integer.parseInt(st.nextToken());
    int M = Integer.parseInt(st.nextToken());
    st = new StringTokenizer(br.readLine());
    int cr = Integer.parseInt(st.nextToken());
    int cc = Integer.parseInt(st.nextToken());
    int cd = Integer.parseInt(st.nextToken());

    State[][] map = new State[N][M];
    for (int i = 0; i < N; ++i) {
      st = new StringTokenizer(br.readLine());
      for (int j = 0; j < M; ++j) {
        map[i][j] = Integer.parseInt(st.nextToken()) == 0 ? State.DIRTY : State.WALL;
      }
    }
    int answer = 0;

    while (true) {
      // 현재 위치 청소
      if (map[cr][cc] == State.DIRTY) {
        map[cr][cc] = State.CLEAN;
        ++answer;
      }

      int nr = -1, nc = -1, d = cd;
      for (int i = 0; i < 4; ++i) {
        d = (d + 3) % 4; // 오른쪽으로 회전
        int tnr = cr + dr[d]; // 다음 위치 확인(임시로)
        int tnc = cc + dc[d];

        if (tnr < 0 || tnr >= N || tnc < 0 || tnc >= M)
          continue;

        if (map[tnr][tnc] == State.DIRTY) { // 다음 위치가 더러우면 그위치 저장
          cd = d;
          nr = tnr;
          nc = tnc;
          break;
        }
      }
      if (nr == -1 && nc == -1) { // 주변이 모두 깨끗하면
        nr = cr + dr[(cd + 2) % 4]; // 뒤로 이동
        nc = cc + dc[(cd + 2) % 4];
        if (map[nr][nc] == State.WALL) { // 뒤도 벽이면 끝
          break;
        } else {
          cr = nr; // 뒤가 벽이 아니면 뒤로 이동
          cc = nc;
        }
      } else { // 더러웠던 그 위치로 이동
        cr = nr;
        cc = nc;
      }
    }
    System.out.println(answer);
  }
}
