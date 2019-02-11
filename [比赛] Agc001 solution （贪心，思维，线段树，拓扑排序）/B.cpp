#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define int long long
using namespace std;
inline int read(){
    int f=1,ans=0;char c;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return ans*f;
}
int gcd(int a,int b){
    if(b==0) return a;
    return gcd(b,a%b);
}
int n,x;
signed main(){
    n=read(),x=read();
    printf("%lld",3*(n-gcd(n,x)));
}

