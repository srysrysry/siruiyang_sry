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
const int N=220;
int f[N][N][3],sum[N][N],s[N];
void init(){
	f[2][1][0]=f[2][2][1]=1;
	sum[2][1]=sum[2][2]=1;
	sum[1][1]=1;
	s[2]=2,s[1]=1;
	for(int i=3;i<=20;i++){
		for(int j=1;j<=i;j++){
			for(int k=1;k<j;k++) f[i][j][1]+=f[i-1][k][0];
			for(int k=j;k<=i;k++) f[i][j][0]+=f[i-1][k][1];
			sum[i][j]=f[i][j][1]+f[i][j][0];
			s[i]+=sum[i][j];
		}
	}
}
int T,n,kth,S[N];
int solve_first(){
	int ans=0;
	for(int i=1;i<=n;i++){
		S[i]=S[i-1]+sum[n][i];
		if(S[i]==kth) return i;
		if(S[i-1]<kth&&S[i]>=kth) return i;
	}return n;
}
int Num[N],M[N],Q[N];
/*
1 >
0 <
*/ 
int floyd[N];
void solve(int pos,int las,int kth,int sta){
	if(pos==0) return;
	memset(floyd,0,sizeof(floyd));
	for(int i=1;i<=n;i++){
	    if(Num[i]) continue;
	    floyd[++floyd[0]]=i;
	}sort(floyd+1,floyd+floyd[0]+1);
	if(sta==1){
		/*
		end
		*/
		int End=pos,MAXN=0;
		for(int i=1;i<=floyd[0];i++){
			if(floyd[i]<las){MAXN=max(MAXN,i);}
		}End=MAXN;
		int Ans=0,maxn=-1;
		for(int i=1;i<=End;i++){
			Ans+=f[pos][i][0];
			if(Ans>=kth){maxn=i;break;}
		}
		if(maxn==-1) maxn=End;Ans=0;
		for(int i=1;i<maxn;i++) Ans+=f[pos][i][0];
		int st=0,Pos,ans=0;
		for(int i=1;i<=n;i++){
			if(Num[i]) continue;
			ans++;
			if(ans==maxn){Pos=i;break;}
		}
		Q[++Q[0]]=Pos;
		Num[Pos]=1;
		solve(pos-1,Pos,kth-Ans,0);
	}else{
		/*begin*/
		int Begin=1;
		for(int i=1;i<=floyd[0];i++){
			if(floyd[i]>las){Begin=i;break;}
		}
		int Ans=0,maxn=-1;
		for(int i=Begin;i<=pos;i++){
			Ans+=f[pos][i][1];
			if(Ans>=kth){maxn=i;break;}
		}if(maxn==-1) maxn=pos;
		Ans=0;
		for(int i=Begin;i<maxn;i++) Ans+=f[pos][i][1];
		int st=0,Pos,ans=0;
		for(int i=1;i<=n;i++){
			if(Num[i]) continue;
			ans++;
			if(ans==maxn){Pos=i;break;}
		}
		Q[++Q[0]]=Pos;
		Num[Pos]=1;
		solve(pos-1,Pos,kth-Ans,1);
	}
}
signed main(){
//	freopen("2.in","r",stdin);
	init();
	T=read();
	while(T--){
		memset(Q,0,sizeof(Q));
		memset(Num,0,sizeof(Num));
		n=read(),kth=read();
		if(s[n]<kth){printf("-1");continue;}
		int first=solve_first();
		Q[++Q[0]]=first;
		kth-=S[first-1];
		Num[first]=1;
		if(f[n][first][1]<kth) solve(n-1,first,kth-f[n][first][1],0);
		else solve(n-1,first,kth,1);
		for(int i=1;i<=n;i++) printf("%d ",Q[i]);
		printf("\n");
	}
}
