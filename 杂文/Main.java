import java.io.*;
import java.text.DecimalFormat;
import java.util.*;
import java.math.*;
import java.util.Arrays;

class Chess {
    
    public int n;

    public int[] currentSolution;

    public long sum;
    
    public StringBuilder stringBuilder = new StringBuilder();

    public void cacu(int n) {
        this.n = n;
        this.sum = 0;
        this.currentSolution = new int[2 * n];
        Arrays.fill(this.currentSolution, -1);
        backtrack(0);
    }

    public boolean isOk(int t, int id) {
        int up = 0;
        int right = 0;
        for(int i = 0; i <= t; i++) {
            if(currentSolution[i] == 0) {
                right++;
            } else if(currentSolution[i] == 1) {
                up++;
            }
        }
        if(id == 0 && right < n) {
            return true;
        }
        if(id == 1 && up < n) {
            return true;
        }
        return false;
    }
    
    public void output() {
        for(int i = 0; i < 2 * n; i++) {
            stringBuilder.append(currentSolution[i]);
        }
        stringBuilder.append("\n");
    }

    public void backtrack(int t) {
        if(t >= 2 * n) {
            sum++;
            output();
            return;
        }
        if(isOk(t, 0)) {
            currentSolution[t] = 0;
            backtrack(t + 1);
        }
        if(isOk(t, 1)) {
            currentSolution[t] = 1;
            backtrack(t + 1);
        }
        currentSolution[t] = -1;
    }
}
package com.aekc.test;

public class Main {
    
    public static void main(String[] args) {
        Chess chess = new Chess();
        chess.cacu(4);
        System.out.println(chess.sum);
        System.out.println(chess.stringBuilder.toString());
    }
}


