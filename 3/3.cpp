#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
inline int read()
{
	int f=1,ans=0;char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}
const int MAXN=601;
int n,fa[MAXN],val[MAXN],num=1,ch[MAXN][27],tot=1,fail[MAXN],f[MAXN][4097],bst_pos[MAXN][4097],bst_sta[MAXN][4097];
int p1[MAXN*4097],p2[MAXN*4097];
struct AC_automation{
	void init(){for(int i=0;i<26;i++) ch[0][i]=1;}
	void insert(char *s){
		int len=strlen(s),rt=1;
		for(int i=0;i<len;i++){
			int v=s[i]-'A';
			if(!ch[rt][v]) ch[rt][v]=++tot,fa[tot]=v;
			rt=ch[rt][v];
		}
		val[rt]|=num;num<<=1;
	}
	void getfail(){
		queue<int> que;
		while(!que.empty()) que.pop();
		fail[1]=0;que.push(1);
		while(!que.empty()){
			int u=que.front();que.pop();
			for(int i=0;i<26;i++){
				if(!ch[u][i]) ch[u][i]=ch[fail[u]][i];
				else{
					int v=ch[u][i];
					fail[v]=ch[fail[u]][i];
					que.push(v);
				}
			}
		}
	}
	void Init(){for(int i=1;i<=tot;i++) val[i]|=val[fail[i]];}
	void solve(){
		queue<pair<int,int> > que;
		while(!que.empty()) que.pop();
		memset(f,-1,sizeof(f));
		f[0][0]=0;
		que.push(make_pair(0,0));
		while(!que.empty()){
			int u=que.front().first,sta=que.front().second;que.pop();
			if(sta==(1<<n)-1){
				int siz=0,lst=u;
				p1[++siz]=u,p2[siz]=sta;
				while(lst>1){
					int pos=bst_pos[p1[siz]][p2[siz]],sta=bst_sta[p1[siz]][p2[siz]];
					p1[++siz]=pos,p2[siz]=sta;
					lst=pos;
				}
				for(int i=siz-1;i>=1;i--) printf("%c",fa[p1[i]]+'A');
				return;
			}
			for(int i=0;i<26;i++){
				if(f[ch[u][i]][(sta|(val[ch[u][i]]))]==-1){
				    f[ch[u][i]][(sta|(val[ch[u][i]]))]=f[u][sta]+1;
				    bst_pos[ch[u][i]][(sta|(val[ch[u][i]]))]=u;
					bst_sta[ch[u][i]][(sta|(val[ch[u][i]]))]=sta;
					que.push(make_pair(ch[u][i],(sta|(val[ch[u][i]]))));
				}
			}
		} 
	}
}AC;
char str[MAXN];
int main(){
	n=read();
	AC.init();
	for(int i=1;i<=n;i++){
		scanf("%s",str);
		AC.insert(str);
	}
	AC.getfail();
	AC.Init();
	AC.solve();
	return 0;
}
