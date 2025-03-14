import java.util.Arrays;
import java.util.Scanner;

class grader {
    private final static int MAX_VALUE_OF_N = 100;
    private final static int MAX_VALUE_OF_Q = 200;

    private static int n;
    private static int numberOfQueries = 0;
    private static int[] a;

    private static void wrong_answer(String MSG) {
        System.out.println("-1");
        System.exit(0);
    }

    private static void query() {
        numberOfQueries++;

        if (numberOfQueries > MAX_VALUE_OF_Q) {
            wrong_answer("Number of queries exceeded");
        }
    }

    public static int ask(int position) {
        query();

        if (position < 1 || position > n) {
            wrong_answer("Not correct position");
        }
        return a[position - 1];
    }


    public static int[] get_pairwise_xor(int[] positions) {
        query();

        if (positions.length == 0 || positions.length > n) {
            wrong_answer("Not correct size");
        }

        for (int i = 0; i < positions.length; i++) {
            if (positions[i] < 1 || positions[i] > n) {
                wrong_answer("Not correct position");
            }
        }
        Arrays.sort(positions);

        for (int i = 1; i < positions.length; i++) {
            if (positions[i] == positions[i - 1]) {
                wrong_answer("Not unique");
            }
        }

        int[] pairwise_xor = new int[positions.length * positions.length];

        for (int i = 0; i < positions.length; i++) {
            for (int j = 0; j < positions.length; j++) {
                int posI = positions[i];
                int posJ = positions[j];

                pairwise_xor[i * positions.length + j] = (a[posI - 1] ^ a[posJ - 1]);
            }
        }

        Arrays.sort(pairwise_xor);

        return pairwise_xor;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();

        assert (1 <= n && n <= MAX_VALUE_OF_N);

        a = new int[n];

        for (int i = 0; i < n; i++) {
            a[i] = scanner.nextInt();

            assert (0 <= a[i] && a[i] <= 1000000000);
        }

        int[] answer = Xoractive.guess(n);

        System.out.println(answer.length);

        for (int i = 0; i < answer.length; i++) {
            System.out.print(answer[i] + " ");
        }

        System.out.println("\n" + numberOfQueries);
    }
}
