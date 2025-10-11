package pro;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.StringTokenizer;

class 계산게임 {
	private static BufferedReader br;
	private static UserSolution usersolution = new UserSolution();

	private final static int CMD_INIT = 100;
	private final static int CMD_PUT = 200;
	private final static int CMD_FIND = 300;
	private final static int CMD_CHANGE = 400;

	private final static int MAX_CARD_NUM = 5;
	private final static int MAX_RET_NUM = 4;

	private final static int numbers[] = new int[MAX_CARD_NUM];
	private final static int ret_numbers[] = new int[MAX_RET_NUM];
	private final static int ans_numbers[] = new int[MAX_RET_NUM];

	private static boolean run() throws Exception {

		StringTokenizer stdin = new StringTokenizer(br.readLine(), " ");

		int query_num = Integer.parseInt(stdin.nextToken());
		int ret, ans;
		boolean ok = false;

		for (int q = 0; q < query_num; q++) {
			stdin = new StringTokenizer(br.readLine(), " ");
			int query = Integer.parseInt(stdin.nextToken());

			if (query == CMD_INIT) {
				int joker = Integer.parseInt(stdin.nextToken());
				for (int i = 0; i < MAX_CARD_NUM; i++)
					numbers[i] = Integer.parseInt(stdin.nextToken());
				usersolution.init(joker, numbers);
				ok = true;
			} else if (query == CMD_PUT) {
				int dir = Integer.parseInt(stdin.nextToken());
				for (int i = 0; i < MAX_CARD_NUM; i++)
					numbers[i] = Integer.parseInt(stdin.nextToken());
				usersolution.putCards(dir, numbers);
			} else if (query == CMD_FIND) {
				int num, Nth;
				num = Integer.parseInt(stdin.nextToken());
				Nth = Integer.parseInt(stdin.nextToken());
				ans = Integer.parseInt(stdin.nextToken());
				ret = usersolution.findNumber(num, Nth, ret_numbers);
				if (ans != ret) {
					ok = false;
				}
				if (ans == 1) {
					for (int i = 0; i < MAX_RET_NUM; i++) {
						ans_numbers[i] = Integer.parseInt(stdin.nextToken());
						if (ans_numbers[i] != ret_numbers[i]) {
							ok = false;
						}
					}
				}
			} else if (query == CMD_CHANGE) {
				int value = Integer.parseInt(stdin.nextToken());
				usersolution.changeJoker(value);
			}
		}
		return ok;
	}

	public static void main(String[] args) throws Exception {
		int T, MARK;

		System.setIn(new java.io.FileInputStream("inputPro.txt"));
		br = new BufferedReader(new InputStreamReader(System.in));

		StringTokenizer stinit = new StringTokenizer(br.readLine(), " ");
		T = Integer.parseInt(stinit.nextToken());
		MARK = Integer.parseInt(stinit.nextToken());

		for (int tc = 1; tc <= T; tc++) {
			int score = run() ? MARK : 0;
			System.out.println("#" + tc + " " + score);
		}

		br.close();
	}
}

class UserSolution {
	final static int MAX_ADD = 50_000, MAX_SUM = 20;

	static int[] cards;
	static int leftIdx, rightIdx, joker;
	LinkedList<Integer> sumToIdx[][];

	void init(int mJoker, int mNumbers[]) {
		cards = new int[MAX_ADD * 2 + 5 + 4];
		leftIdx = rightIdx = MAX_ADD;
		sumToIdx = new LinkedList[MAX_SUM][MAX_SUM];
		joker = mJoker % 20;

		for (int i = 0; i < MAX_SUM; i++) {
			for (int j = 0; j < MAX_SUM; j++) {
				sumToIdx[i][j] = new LinkedList<>();
			}
		}

		int sum1 = 0, sum2 = 0;
		for (int i = 0; i < 5; i++) {
			cards[MAX_ADD + i] = mNumbers[i];
		}

		for (int i = 0; i < 2; i++) {
			update(leftIdx + i, 1);
		}
		
		rightIdx += 5;
	}

	void update(int s, int d) {
		int sum = 0, jokerCnt = 0;
		for (int i = s; i < s + 4; i++) {
			if (cards[i] == -1) {
				jokerCnt++;
				continue;
			}
			sum += cards[i];
		}
		for (int i = 0; i < 20; i++) {
			int jokerSum = (sum + jokerCnt * i) % 20;
			switch (d) {
			case 0 :
				sumToIdx[i][jokerSum].add(0, s);
				break;
			case 1 :
				sumToIdx[i][jokerSum].add(s);
				break;
			}
		}

	}

	void putCards(int mDir, int mNumbers[]) {
		switch (mDir) {
		case 0 :
			leftIdx -= 5;
			for (int i = 0; i < 5; i++) {
				cards[leftIdx + i] = mNumbers[i];
			}
			for (int i = 4; i >= 0; i--) {
				update(leftIdx + i, mDir);
			}
			break;
		case 1 :
			for (int i = 0; i < 5; i++) {
				cards[rightIdx + i] = mNumbers[i];
			}
			for (int i = 0; i < 5; i++) {
				update(rightIdx + i - 3, mDir);
			}
			rightIdx += 5;
			break;
		}
		
	}

	int findNumber(int mNum, int mNth, int ret[]) {
		if (sumToIdx[joker][mNum].size() < mNth)
			return 0;
		
		int curIdx = sumToIdx[joker][mNum].get(mNth - 1);
		for (int i = 0; i < 4; i++) {
			ret[i] = cards[curIdx + i];
		}

		return 1;
	}

	void changeJoker(int mValue) {
		joker = mValue % 20;
	}
}