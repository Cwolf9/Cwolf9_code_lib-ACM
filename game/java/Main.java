import java.util.*;

public class problems {
    public static void main (String[]args) {
        Scanner sc=new Scanner(System.in);
        int x=sc.nextInt();
        int []m=new int[x];
        for(int i=0;i<x;i++) m[i]=sc.nextInt();
        int k=0;
        for(int i=1;i<x-1;i++) {
            if((m[i]<m[i-1]&& m[i]<m[i+1])||(m[i]>m[i-1]&& m[i]>m[i+1]))
                k+=1;
        }
        System.out.println(k);
    }
}