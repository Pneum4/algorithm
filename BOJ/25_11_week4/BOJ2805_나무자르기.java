import java.io.*;
import java.util.*;

public class BOJ2805_나무자르기 {
  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());

    int N = Integer.parseInt(st.nextToken());
    long M = Integer.parseInt(st.nextToken());

    long[] arr = new long[N];
    long max = 0;

    st = new StringTokenizer(br.readLine());
    for (int i = 0; i < N; ++i) {
      arr[i] = Long.parseLong(st.nextToken());
      max = Math.max(max, arr[i]);
    }

    long l = 0, r = max;
    long answer = 0;
    while (l <= r) {
      long m = (l + r) / 2;
      long sum = 0;
      for (int i = 0; i < N; ++i) {
        if (arr[i] > m)
          sum += arr[i] - m;
      }

      if (sum >= M) {
        answer = m;
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
    System.out.println(answer);
  }

}
