package pro;

import java.util.*;
import static java.util.Collections.sort;
import static java.util.Collections.swap;

class Solution {
  static class UserSolution {
    // 각 리그는 TreeSet임
    TreeSet<setEle>[] leagues;
    // size는 각 리그에 포함된 사람수(N/L)
    int N, L, size;

    static class setEle implements Comparable<setEle> {
      int id, abil;

      public setEle(int id, int abil) {
        super();
        this.id = id;
        this.abil = abil;
      }

      // 능력치 내림차순, id 오름차순 구현
      @Override
      public int compareTo(setEle b) {
        if (this.id == b.id)
          return 0;
        else if (this.abil != b.abil)
          return b.abil - this.abil;
        else
          return this.id - b.id;
      }
    }

    void init(int N, int L, int mAbility[]) {
      this.N = N;
      this.L = L;
      // size는 각 리그에 포함된 사람수(N/L)
      this.size = N / L;

      leagues = new TreeSet[L];
      for (int i = 0; i < L; ++i) {
        leagues[i] = new TreeSet<setEle>();
      }

      // 리그 배열에는 setEle(id, ability) 가 저장됨
      for (int i = 0; i < L; ++i) {
        for (int j = size * i; j < size * (i + 1); ++j) {
          leagues[i].add(new setEle(j, mAbility[j]));
        }
      }
    }

    int move() {
      // id 합을 구하기위한 sum
      int sum = 0;
      // 모든 리그를 돌면서 첫번째 원소(최댓값)는 first에 임시로 유지
      // 마찬가지로 마지막 원소(최솟값)은 last에 임시로 유지
      ArrayList<setEle> first = new ArrayList<>(L);
      ArrayList<setEle> last = new ArrayList<>(L);

      // 리그를 돌면서 바로 최댓값 최솟값 바꿔버리면 다음 리그를 순환할때 원래 없었던 원소가 참조되는 문제 발생
      // 일단 최댓값 최솟값을 모두 뽑아버리고, 나중에 각 리그에 삽입해야함
      // 최대 최소 뽑아내는 코드
      for (int i = 1; i < L; ++i) {
        setEle a = null, b = null;

        a = leagues[i - 1].pollLast();
        last.add(a);
        sum += a.id;

        b = leagues[i].pollFirst();
        first.add(b);
        sum += b.id;
      }

      // 삽입 코드
      for (int i = 0; i < L - 1; ++i) {
        leagues[i].add(first.get(i));
        leagues[i + 1].add(last.get(i));
      }
      return sum;
    }

    int trade() {
      int sum = 0;
      // move와 마찬가지로 바뀌는 선수는 다 뽑아버리고 나중에 추가해야됨. 동시에 추가하면 그게 또 뽑히는 문제 발생함
      ArrayList<setEle> mid = new ArrayList<>(L);
      ArrayList<setEle> first = new ArrayList<>(L);
      for (int i = 1; i < L; ++i) {
        setEle a;

        // 중간값 찾을때 순차탐색해서 size/2만큼 걸림
        // LeftMaxHeap, RightMinHeap을 사용해서 최적화 가능하긴함 -> 안해도 통과
        Iterator<setEle> iter = leagues[i - 1].iterator();
        for (int j = 0; j < size / 2 - 1; ++j) {
          iter.next();
        }
        a = iter.next();
        // 중간값 탐색시 첫번째 원소는 size개, 나머지는 size-1개임(이전 루프에서 poll당했음)
        if (i == 1)
          a = iter.next();

        leagues[i - 1].remove(a);
        mid.add(a);

        setEle b = leagues[i].pollFirst();
        first.add(b);

        sum += a.id + b.id;
      }

      for (int i = 0; i < L - 1; ++i) {
        leagues[i].add(first.get(i));
        leagues[i + 1].add(mid.get(i));
      }

      return sum;
    }

  }

  private static Scanner sc;
  private static UserSolution usersolution = new UserSolution();

  private final static int CMD_INIT = 100;
  private final static int CMD_MOVE = 200;
  private final static int CMD_TRADE = 300;

  private static boolean run() throws Exception {

    int query_num = sc.nextInt();
    int ans;
    boolean ok = false;

    for (int q = 0; q < query_num; q++) {
      int query = sc.nextInt();

      if (query == CMD_INIT) {
        int N = sc.nextInt();
        int L = sc.nextInt();
        int mAbility[] = new int[N];
        for (int i = 0; i < N; i++) {
          mAbility[i] = sc.nextInt();
        }
        usersolution.init(N, L, mAbility);
        ok = true;
      } else if (query == CMD_MOVE) {
        int ret = usersolution.move();

        ans = sc.nextInt();
        if (ans != ret) {
          ok = false;
        }
      } else if (query == CMD_TRADE) {
        int ret = usersolution.trade();

        ans = sc.nextInt();
        if (ans != ret) {
          ok = false;
        }
      }
    }
    return ok;
  }

  public static void main(String[] args) throws Exception {
    int T, MARK;

    System.setIn(new java.io.FileInputStream("inputPro.txt"));
    sc = new Scanner(System.in);
    T = sc.nextInt();
    MARK = sc.nextInt();

    for (int tc = 1; tc <= T; tc++) {
      int score = run() ? MARK : 0;
      System.out.println("#" + tc + " " + score);
    }
    sc.close();
  }

}
