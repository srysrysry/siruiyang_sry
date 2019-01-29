#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
inline int read(){
	int f=1,ans=0;char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}
const int N=11;
int f[N][N][(1<<10)+1],a[N][N],vis[N][N],tot,inf,n,m;
queue<pair<int,int> > que;
int bx[4]={1,-1,0,0};
int by[4]={0,0,1,-1};
int ex,ey;
int prex[N][N][(1<<10)+1],prey[N][N][(1<<10)+1],presta[N][N][(1<<10)+1];
void spfa(int sta){
	while(!que.empty()){
		int xx=que.front().first,yy=que.front().second;que.pop();
		vis[xx][yy]=0;
		for(int i=0;i<4;i++){
			int dx=xx+bx[i],dy=yy+by[i];
			if(dx<=0||dx>n||dy<=0||dy>m) continue;
			if(f[dx][dy][sta]>f[xx][yy][sta]+a[dx][dy]){
				f[dx][dy][sta]=f[xx][yy][sta]+a[dx][dy];
				prex[dx][dy][sta]=xx,prey[dx][dy][sta]=yy,presta[dx][dy][sta]=sta;
				if(!vis[dx][dy])vis[dx][dy]=1,que.push(make_pair(dx,dy));
			}
		}
	}
}
int ans[N][N];
void dfs(int x,int y,int sta){
	if(!presta[x][y][sta]) return;
	ans[x][y]=1;
	dfs(prex[x][y][sta],prey[x][y][sta],presta[x][y][sta]);
	int xx=prex[x][y][sta],yy=prey[x][y][sta],Sta=presta[x][y][sta];
	if(x==xx&&y==yy) dfs(x,y,sta-Sta);
} 
int main(){
	memset(f,127/3,sizeof(f));inf=f[0][0][0];
    n=read(),m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			if(!a[i][j]) ex=i,ey=j,tot++,f[i][j][1<<(tot-1)]=0;
		}
	}
	for(int sta=1;sta<=(1<<tot)-1;sta++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				for(int SS=sta;SS;SS=sta&(SS-1)) if(f[i][j][sta]>f[i][j][SS]+f[i][j][sta-SS]-a[i][j]) f[i][j][sta]=f[i][j][SS]+f[i][j][sta-SS]-a[i][j],prex[i][j][sta]=i,prey[i][j][sta]=j,presta[i][j][sta]=SS;
				if(f[i][j][sta]!=inf) vis[i][j]=1,que.push(make_pair(i,j));
			}
		}
		spfa(sta);
	}
	printf("%d\n",f[1][1][(1<<tot)-1]);
	dfs(1,1,(1<<tot)-1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!a[i][j]) printf("x");
			else if(ans[i][j]) printf("o");
			else printf("_");
		}printf("\n"); 
	}
}

