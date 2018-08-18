//HDU4933_MiaomiaosFunction_数位DP_JAVA高精度.cpp
//https://www.cnblogs.com/danceonly/p/3904449.html
/*
题意 ： 自己看吧，还是很容易理解的，就一个公式而已。

方法 ： 比赛的时候想到两次数位DP：先对所有的数进行一次mod9 的数位DP,再得出的答案x为新的mod，再进行一次mod，后来写着写着发现似乎有点问题，对于answer = 0要特判，然后没想到好的方法，比赛就结束了。

赛后用java写了一发大数过的，对于题解中用多个大质数去判这种神奇的作法只能意会下了 ， 貌似rand() 也行？
*/
import java.io.*;
import java.util.*;
import java.math.*;

public class Main {

    /**
     * @param args
     */
    public static class Pair {
        BigInteger cnt, sum;
    }
    
    public static BigInteger sum[][] = new BigInteger[105][3];
    public static BigInteger cnt[][] = new BigInteger[105][3];
    public static int bit[] = new int[105];
    public static boolean vis[][] = new boolean[105][3];
    
    public static Pair dfs(int len, int dis, boolean fp) {
        //System.out.println(len + " " + s + " " + dis + " " + fp);
        Pair ret = new Pair();
        if (len == 0) {
            ret.cnt = BigInteger.ONE; ret.sum = BigInteger.ZERO;
            return ret;
        }
        if (fp == false && vis[len][dis] == true) {
            ret.cnt = cnt[len][dis];
            ret.sum = sum[len][dis];
            return ret;
        }
        int Max;
        BigInteger Sum = BigInteger.ZERO;
        BigInteger Cnt = BigInteger.ZERO;
        if (fp == true) Max = bit[len];
        else Max = 9;
        //System.out.println("Max = " + Max);
        for (int i = 0; i <= Max; i++) {
            if (i > 0) {
                if (dis == 0 || dis == 1) {
                    ret = dfs(len-1, 2, fp==true&&i==Max);
                    Cnt = Cnt.add(ret.cnt); Sum = Sum.add(ret.sum);
                    Sum = Sum.add(ret.cnt.multiply(BigInteger.valueOf(i)));
                }else {
                    ret = dfs(len-1, 3-dis, fp==true&&i==Max);
                    Cnt = Cnt.add(ret.cnt); Sum = Sum.add(ret.sum);
                    Sum = Sum.subtract(ret.cnt.multiply(BigInteger.valueOf(i)));
                }
            }else {
                if (dis == 0) {
                    ret = dfs(len-1, dis, fp==true&&i==Max);
                    Cnt = Cnt.add(ret.cnt); Sum = Sum.add(ret.sum);
                }else {
                    ret = dfs(len-1, 3-dis, fp==true&&i==Max);
                    Cnt = Cnt.add(ret.cnt); Sum = Sum.add(ret.sum);
                }
            }
        }
        if (fp == false) {
            vis[len][dis] = true;
            sum[len][dis] = Sum;
            cnt[len][dis] = Cnt;
        }
        ret.cnt = Cnt; ret.sum = Sum;
        return ret;
    }
    public static BigInteger solve(BigInteger x) {
        if (x.equals(BigInteger.valueOf(-1))) return BigInteger.ZERO;
        String tmp = String.valueOf(x);
        for (int i = 0; i < tmp.length(); i++) {
            bit[i+1] = tmp.charAt(tmp.length() - i - 1) - '0';
        }
        return dfs(tmp.length(), 0, true).sum;
    }
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        Scanner cin = new Scanner(System.in);
        int T = cin.nextInt(); 
        for (int cas = 1; cas <= T; cas++) {
            BigInteger L, R;
            L = cin.nextBigInteger();
            R = cin.nextBigInteger();
            BigInteger answer = solve(R).subtract(solve(L.subtract(BigInteger.ONE)));
            BigInteger Mod = answer;
            if (Mod.compareTo(BigInteger.ZERO) == 0) {
                Mod = BigInteger.ZERO;
            }else {
                Mod = Mod.mod(BigInteger.valueOf(9));
                if (Mod.compareTo(BigInteger.ZERO) <= 0) Mod = Mod.add(BigInteger.valueOf(9));
            }
            if (Mod.equals(BigInteger.ZERO)) {
                System.out.println("Error!");
            }else {
                answer = answer.mod(Mod);
                if (answer.compareTo(BigInteger.ZERO) < 0) answer = answer.add(Mod);
                System.out.println(answer);
            }
        }
    }

}