#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<ctime>
#include<climits>
using namespace std;
inline int read(){
	int f=1,ans=0;char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}
const int N=234;
int Hash[N],vis[N][N],Num[N][N],w[N][N];
int f[N][(1<<5)];
int c[N][N],inf,T,n,m,k,tot,num,color[N][N],v[N][N],H[N],minn=INT_MAX;
int bx[4]={1,-1,0,0};
int by[4]={0,0,1,-1};
queue<pair<int,int> > que;
inline int calc(int x,int y){return Num[x][y];}
inline void spfa(int sta){
	while(!que.empty()){
		 int xx=que.front().first,yy=que.front().second;que.pop();
		 vis[xx][yy]=0;
		 for(int i=0;i<4;i++){
		 	int dx=xx+bx[i],dy=yy+by[i];
		 	if(dx<1||dx>n||dy<1||dy>m) continue;
		 	if(c[dx][dy]!=-1&&f[calc(dx,dy)][sta]>f[calc(xx,yy)][sta]+w[dx][dy]){
		 		f[calc(dx,dy)][sta]=f[calc(xx,yy)][sta]+w[dx][dy];
		 		if(!vis[dx][dy]) vis[dx][dy]=1,que.push(make_pair(dx,dy));
			 }
		 }
	}
}
int maxn=0;
inline int work(){
	for(int i=1;i<=n*m;i++) if(Hash[i]) H[i]=rand()%k+1;
	for(int i=1;i<=n;i++)
	     for(int j=1;j<=m;j++){
	     	if(color[i][j]==-1){c[i][j]=-1;continue;}
	     	else c[i][j]=H[color[i][j]];
	    }
	memset(f,127/3,sizeof(f));inf=f[0][0];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(c[i][j]==-1) continue;
			f[calc(i,j)][(1<<(c[i][j]-1))]=w[i][j];
		}
	}
	for(int sta=1;sta<=(1<<k)-1;sta++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(c[i][j]==-1) continue;
				for(int S=sta;S;S=sta&(S-1)) if(f[calc(i,j)][sta]>f[calc(i,j)][S]+f[calc(i,j)][sta-S]-w[i][j]) f[calc(i,j)][sta]=f[calc(i,j)][S]+f[calc(i,j)][sta-S]-w[i][j];
				if(f[calc(i,j)][sta]!=inf) vis[i][j]=1,que.push(make_pair(i,j));
			}
		}
		spfa(sta);
	}
	int Minn=300000; 
	for(int i=1;i<=n;i++)
	     for(int j=1;j<=m;j++) Minn=min(Minn,f[calc(i,j)][(1<<k)-1]);
	return Minn;
	
}
int kuai;
inline bool check(int xx){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) {
			if(v[i][j]<=xx) w[i][j]=999;
			else w[i][j]=1001;
		}
	}
	int tot=0,tmp=INT_MAX;
	while(tot<=200){tot++;tmp=min(tmp,work());}
	printf("%d\n",tmp);
	kuai=(tmp+500)/1000;
	return tmp<=kuai*1000;
}/*999 1001 999 1001      1 2 3 4 5(жа) 6 7 8  9  1 2 3 4 5(жа) 6 7 8 9*/
int R;
signed main(){
//	freopen("11.in","r",stdin);
	srand(time(0));
	T=read();
	while(T--){
		memset(Hash,0,sizeof(Hash));
		minn=INT_MAX;Num[0][0]=0,tot=0,R=0;
		n=read(),m=read(),k=read();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				color[i][j]=read();
				if(color[i][j]!=-1)Hash[color[i][j]]=1;
			}
		for(int i=1;i<=n;i++)
		     for(int j=1;j<=m;j++) Num[i][j]=++Num[0][0]; 
		for(int i=1;i<=n;i++)
		    for(int j=1;j<=m;j++) v[i][j]=read(),R=max(R,v[i][j]);
		int l=0,r=1e6;minn=INT_MAX;
		printf("%d\n",check(6));return 0;
		while(l<=r){
			int mid=l+r>>1;
			if(check(mid)) r=mid-1,minn=min(minn,mid);
			else l=mid+1;
		}
		printf("%d %d\n",kuai,minn);
	} 
}
