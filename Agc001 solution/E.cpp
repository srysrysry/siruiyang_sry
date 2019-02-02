#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define mod 1000000007
#define int long long
using namespace std;
inline int read(){
    int f=1,ans=0;char c;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return ans*f;
}
const int N=200001;
const int MAXN=4011;
int f[MAXN][MAXN],C[MAXN][MAXN],n,a[N],b[N],ans,zero=2001;
int calc(int a,int b){return C[a][b];}
int ksm(int A,int B){
    int Ans=1;
    while(B){
        if(B&1) Ans*=A,Ans%=mod;
        A*=A,A%=mod;
        B>>=1;
    }return Ans;
}
signed main(){
    n=read();
    for(int i=1;i<=n;i++) a[i]=read(),b[i]=read(),f[zero-a[i]][zero-b[i]]++;
    for(int i=1;i<=4001;i++)
         for(int j=1;j<=4001;j++) f[i][j]+=(f[i-1][j]+f[i][j-1]),f[i][j]%=mod;
    for(int i=0;i<=4000;i++) C[0][i]=C[i][0]=1;
    for(int i=1;i<=4000;i++)
        for(int j=1;j<=4000;j++) C[i][j]=C[i-1][j]+C[i][j-1],C[i][j]%=mod;
    for(int i=1;i<=n;i++){
        ans+=f[zero+a[i]][zero+b[i]];ans%=mod;
        ans-=calc(2*a[i],2*b[i]);ans%=mod;
    }
    ans=((ans%mod)+mod)%mod;
    printf("%d\n",(ans*ksm(2,mod-2))%mod);
}

