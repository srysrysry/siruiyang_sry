#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define mod 998244353
#define int long long
using namespace std;
inline int read(){
    int f=1,ans=0;char c;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return ans*f;
}
const int N=200001;
const int MAXN=2011;
int f[MAXN][MAXN],C[MAXN][MAXN],n,a[N],b[N],ans,zero=1001;
int calc(int a,int b){return C[a][b];}
int ksm(int A,int B){
    int Ans=1;
    while(B){
        if(B&1) Ans*=A,Ans%=mod;
        A*=A,A%=mod;
        B>>=1;
    }return Ans;
}int opt,num[MAXN];
void solve1(){printf("%d\n",C[a[1]][b[1]]);return;}
void solve2(){
	int Ans=0,lst=-1;
	for(int i=1;i<=n;i++) num[a[i]+b[i]]++;
	for(int i=1;i<=2000;i++)
	    for(int j=1;j<=2000;j++) {
	    	if(i!=j) Ans+=calc(i,j)*num[i]*num[j],Ans%=mod; 
	    	else Ans+=calc(i,j)*num[i]*(num[i]-1),Ans%=mod;
		}
	printf("%d\n",(Ans*ksm(2,mod-2))%mod);
	return;
}
signed main(){
//	freopen("20.in","r",stdin);
//	freopen("20.out","w",stdout);
    n=read(),opt=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++) b[i]=read(),f[zero-a[i]][zero-b[i]]++;
     for(int i=0;i<=2000;i++) C[0][i]=C[i][0]=1;
    for(int i=1;i<=2000;i++)
        for(int j=1;j<=2000;j++) C[i][j]=C[i-1][j]+C[i][j-1],C[i][j]%=mod;
    if(opt==1){solve1();return 0;}
    if(opt==2){solve2();return 0;}
    for(int i=1;i<=2001;i++)
         for(int j=1;j<=2001;j++) f[i][j]+=(f[i-1][j]+f[i][j-1]),f[i][j]%=mod;
   
    for(int i=1;i<=n;i++){
        ans+=f[zero+a[i]][zero+b[i]];ans%=mod;
        ans-=calc(2*a[i],2*b[i]);ans%=mod;
    }
    ans=((ans%mod)+mod)%mod;
    if(opt==3)printf("%d\n",(ans*ksm(2,mod-2))%mod);
}

