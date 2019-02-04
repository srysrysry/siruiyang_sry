#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
int n,m,mod=998244353;
int ksm(int a,int b){
    int ans=1;
    while(b){
        if(b&1) ans*=a,ans%=mod;
        a*=a,a%=mod;
        b>>=1;
    }
    return ans;
}
int C(int a,int b){
    int s1=1,s2=1;
    for(int i=a;i>=a-b+1;i--) s1*=i,s1%=mod;
    for(int i=b;i>=1;i--) s2*=i,s2%=mod;
    return ((s1%mod)*ksm(s2,mod-2)%mod)%mod;
}
int lucas(int a,int b){
    if(b==0) 
    return 1;
    return (C(a%mod,b%mod)*lucas(a/mod,b/mod))%mod;
}
const int MAXN=100001;
int opt,a[MAXN],b[MAXN];
signed main(){
	freopen("7.in","r",stdin);
	n=read(),opt=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();
	if(opt==1){printf("%lld\n",lucas(a[1]+b[1],a[1]));return 0;}
	if(opt==2){
		int ans=0;
		for(int i=1;i<=n;i++)
		     for(int j=i+1;j<=n;j++) ans+=lucas(a[i]+a[j]+b[i]+b[j],a[i]+b[i]),ans%=mod;
		printf("%d\n",ans);
	}if(opt==3){
		int ans=0;
		for(int i=1;i<=n;i++)
		     for(int j=i+1;j<=n;j++) ans+=lucas(a[i]+a[j]+b[i]+b[j],a[i]+a[j]),ans%=mod;
		printf("%d\n",ans);
	}
}

