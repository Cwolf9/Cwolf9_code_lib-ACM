import java.io.*;
import java.util.*;
import java.math.*;
//import java.io.OutputStream;
//import java.io.IOException;
//import java.io.InputStream;
//import java.io.PrintWriter;
//import java.util.Arrays;
//import java.io.IOException;
//import java.io.InputStreamReader;
//import java.util.Scanner;
//import java.util.StringTokenizer;
//import java.io.BufferedReader;
//import java.util.Comparator;
//import java.io.InputStream;



public class Main {
    class lp implements Comparable<lp>{
        public int u,v;
        public int w;
        lp(int a, int b, int c){
            this.u=a;this.v=b;this.w=c;
        }
        public int compareTo(lp a) {
            return this.w - a.w;
        }
    }
    public static void main(String[] args) throws FileNotFoundException {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Task solver = new Task();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task {
        static int MXN = 1000006;
        static int mod = 1000000007;
        static int BASE_MAX = 62;
        long[] invF = new long[MXN];
        long[] bs = new long[BASE_MAX+2];
        long[] ar = new long[MXN];
        List list = new ArrayList();
        int zero;
        public void solve(int testNumber, InputReader cin, PrintWriter cout) {
            int tim = cin.nextInt(), cas = 1;
            while(tim != 0) {
                cout.println("Case #"+cas+":");
                ++ cas; -- tim;
                int n  = cin.nextInt();
                for(int i = 0; i < n; ++i) ar[i] = cin.nextLong();
                for(int i = 0; i <= BASE_MAX; ++i) bs[i] = 0;
                int all = go(n);
                int q = cin.nextInt();
                while(q != 0) {
                    -- q;
                    int cnt = 0;
                    long ans = 0, k = cin.nextLong();
                    if(zero == 1) -- k;
                    if(k >= (1L<<all)) {
                        cout.println(-1);
                        continue;
                    }
                    while (k != 0) {
                        if(k % 2 == 1) ans ^= (long)list.get(cnt);
                        k /= 2;
                        ++ cnt;
                    }
                    cout.println(ans);
                }
            }
//            Task.pair[] ar = new Task.pair[10];
//            Task.pair[] br = ar.clone();
//            Arrays.sort(br, new Comparator<Task.pair>() {
//                public int compare(Task.pair o1, Task.pair o2) {
//                    long s1 = o1.x - o1.y;
//                    long s2 = o2.x - o2.y;
//                    return Long.compare(s1, s2);
//                }
//            });
        }
        public int go(int n) {
            int cnt = 0;
            for(int i = 0; i < n; ++i) {
                for(int j = BASE_MAX; j >= 0; --j) {
                    if(((ar[i] >> j) & 1) == 0) continue;
                    if(bs[j] != 0) ar[i] ^= bs[j];
                    else {
                        bs[j] = ar[i]; ++ cnt;
                        for(int k = j-1; k >= 0; --k) if(((bs[j]>>k)&1)==1&&bs[k]!=0)bs[j]^=bs[k];
                        for(int k = j+1; k <= BASE_MAX; ++k) if(((bs[k]>>j)&1)==1)bs[k]^=bs[j];
                        break;
                    }
                }
            }
            if(cnt != n) zero = 1;
            else zero = 0;
            list.clear();
            for(int i = 0; i <= BASE_MAX; ++i) if(bs[i] != 0) list.add(bs[i]);
            return cnt;
        }
        static class pair {
            long x;
            long y;
            long answer;
        }
        public long ksm(int a, int b) {
            long res = 1, tmp = a;
            while(b != 0) {
                if(b % 2 == 1) {
                    res = res * tmp;
                    if(res >= mod) res %= mod;
                }
                tmp = tmp * tmp;
                if(tmp >= mod) tmp %= mod;
                b >>= 1;
            }
            return res;
        }
        public void pre_init() {
            invF[0] = invF[1] = 1;
            for(int i = 2; i < MXN; ++i) {
                invF[i] = (mod - mod/i)*invF[mod%i];
                if(invF[i] >= mod) invF[i] %= mod;
            }
        }
    }


    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) throws FileNotFoundException {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            //File file = new File("in.txt");
            //reader = new BufferedReader(new FileReader(file), 32768);
            tokenizer = null;
        }
        public boolean hasNext() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {//hasMoreElements
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (Exception e) {//IOException
                    return false;
                    //throw new RuntimeException(e);
                }
            }
            return true;
        }
        public String next() {
            if(hasNext()) return tokenizer.nextToken();
            return null;
        }
        public int nextInt() {
            return Integer.parseInt(next());
        }
        public Long nextLong() {
            return Long.parseLong(next());
        }
        public double nextDouble() {
            return Double.parseDouble(next());
        }

        public BigInteger nextBigInteger() {
            return new BigInteger(next());
        }
        public BigDecimal nextBigDecimal() {
            return new BigDecimal(next());
        }
        String nextLine() {
            String str = "";
            try {
                str = reader.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }

}