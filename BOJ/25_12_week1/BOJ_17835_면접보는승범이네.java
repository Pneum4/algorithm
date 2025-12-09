import java.io.*;
import java.util.*;

public class BOJ_17835_면접보는승범이네 {
  final static long INF = Long.MAX_VALUE;
  static int N, M, K;
  static List<int[]>[] graph;
  static long[] dist;
  static int[] interview;

  static class qEle implements Comparable<qEle> {
    int e;
    long d;

   public
    qEle(int e, long d) {
      super();
      this.e = e;
      this.d = d;
    }

    @Override public int compareTo(qEle b) {
      return (int)(this.d - b.d);
    }
  }

  public static void
  main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());
    N = Integer.parseInt(st.nextToken());
    M = Integer.parseInt(st.nextToken());
    K = Integer.parseInt(st.nextToken());
    graph = new ArrayList[N + 1];
    dist = new long[N + 1];
    interview = new int[K];

    for (int i = 1; i <= N; i++) {
      graph[i] = new ArrayList<>();
      dist[i] = INF;
    }

    for (int i = 0; i < M; i++) {
      st = new StringTokenizer(br.readLine());
      int s = Integer.parseInt(st.nextToken());
      int e = Integer.parseInt(st.nextToken());
      int c = Integer.parseInt(st.nextToken());

      graph[e].add(new int[]{s, c});
    }

    st = new StringTokenizer(br.readLine());
    for (int i = 0; i < K; i++) {
      interview[i] = Integer.parseInt(st.nextToken());
    }

    PriorityQueue<qEle> pq = new PriorityQueue<>();

    for (int i = 0; i < K; i++) {
      dist[interview[i]] = 0;
      pq.add(new qEle(interview[i], 0));
    }

    while (!pq.isEmpty()) {
      qEle cur = pq.poll();

      if (dist[cur.e] < cur.d) continue;

      for (int[] next : graph[cur.e]) {
        if (dist[next[0]] > cur.d + next[1]) {
          dist[next[0]] = cur.d + next[1];
          pq.add(new qEle(next[0], dist[next[0]]));
        }
      }
    }

    int city = -1;
    long maxDist = -1;
    for (int i = 1; i <= N; i++) {
      if (dist[i] > maxDist) {
        maxDist = dist[i];
        city = i;
      }
    }

    System.out.println(city);
    System.out.println(maxDist);
  }
}
