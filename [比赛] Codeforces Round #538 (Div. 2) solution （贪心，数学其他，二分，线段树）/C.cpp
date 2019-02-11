#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<climits>
#define int long long
using namespace std;
inline int read(){
	int f=1,ans=0;char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}
const int MAXN=1000001;
int n,k,num[MAXN],prime[MAXN],cnt,minn=LLONG_MAX;
signed main(){
	n=read(),k=read();
	for(int i=2;i<=sqrt(k);i++){
		if(k%i==0){
			prime[++cnt]=i;
			num[cnt]=1;k/=i;
			while(k%i==0){k/=i;num[cnt]++;}
		}
	}if(k>1){prime[++cnt]=k;num[cnt]=1;}
	for(int i=1;i<=cnt;i++){
		int N=n,sum=0;
		while(N) sum+=(N/prime[i]),N/=prime[i];
		sum/=num[i];
		minn=min(minn,sum);
	}printf("%lld\n",minn);
}
