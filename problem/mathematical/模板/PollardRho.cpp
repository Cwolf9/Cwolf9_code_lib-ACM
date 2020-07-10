//https://blog.csdn.net/HOWARLI/article/details/53669023
//https://blog.csdn.net/HOWARLI/article/details/51823336
LL MO(LL q,LL w,LL mo){
    LL ans=0;
    for(;w;w>>=1,q=(q+q)%mo)if(w&1)ans=(ans+q)%mo;
    return ans;
}
LL ksm(LL q,LL w,LL mo){
    LL ans=1;
    for(;w;w>>=1,q=MO(q,q,mo))if(w&1)ans=MO(ans,q,mo);
    return ans;
}
LL RD(LL mo){return (LL)rand()*(LL)rand()%mo;}
bool MillerR(LL q){
    if(q==2||q==3||q==5||q==7||q==11||q==13)return 1;
    if(q==1||!(q&1)||!(q%3)||!(q%5)||!(q%7)||!(q%11)||!(q%13))return 0;
    fo(i,1,5)if(ksm(RD(q-1)+1,q-1,q)!=1)return 0;
    return 1;
}
LL gcd(LL x,LL y){return y<1?x:(gcd(y,x%y));}
void PollarR(LL n){
    if(!(n&1))for(;!(n&1);n>>=1)pr[++pr[0]]=2;
    if(n<2)return;
    if(MillerR(n)){pr[++pr[0]]=n;return;}
    LL x1=0,x2=0,C,P=1;
    printf("%lld\n",n);
    for(;P<2||P==n;P=gcd(abs(x1-x2),n)){
        x2=(MO(x2,x2,n)+C)%n,x2=(MO(x2,x2,n)+C)%n;
        x1=(MO(x1,x1,n)+C)%n;
        while(x1==x2)x1=C=RD(n),x2=(MO(C,C,n)+C)%n;
    }
    PollarR(P);
    PollarR(n/P);
}