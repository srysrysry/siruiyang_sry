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
const int N=201;
int n,cnt;
double ans;
double tmp[N<<2];
struct segment_tree{
	double ans[N<<2];int rev[N<<2];
	void init(){memset(ans,0,sizeof(ans)),memset(rev,0,sizeof(rev));}
	void pushdown(int k,int l,int r){
		if(rev[k]){ans[k]=tmp[r+1]-tmp[l];return;}
		if(l==r){ans[k]=0;return;}
		else ans[k]=ans[k<<1]+ans[k<<1|1];
		return;
	}
	void add(int k,int l,int r,int x,int y,int w){
		if(x<=l&&r<=y){rev[k]+=w;pushdown(k,l,r);return;}
		int mid=l+r>>1;
		if(x<=mid) add(k<<1,l,mid,x,y,w);
		if(mid<y) add(k<<1|1,mid+1,r,x,y,w);
		pushdown(k,l,r);
		return;
	}
	double calc(){return ans[1];}
}segment;
struct node{
	double x1,x2,y;
	int w;
}x[N<<2];
int T=0;
bool cmp(node s1,node s2){return s1.y<s2.y;}
void solve(){
	if(!n) exit(0);
	ans=0,cnt=0;
	segment.init();
	for(int i=1;i<=n;i++){
		double x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		x[++cnt].x1=x1,x[cnt].x2=x2,x[cnt].y=y1,x[cnt].w=1;
		tmp[cnt]=x1;
		x[++cnt].x1=x1,x[cnt].x2=x2,x[cnt].y=y2,x[cnt].w=-1;
		tmp[cnt]=x2;
	}
	sort(tmp+1,tmp+cnt+1);
	sort(x+1,x+cnt+1,cmp);
	int M=unique(tmp+1,tmp+cnt+1)-(tmp+1);
	for(int i=1;i<cnt;i++){
		int l=lower_bound(tmp+1,tmp+M+1,x[i].x1)-tmp,r=lower_bound(tmp+1,tmp+M+1,x[i].x2)-tmp-1;
		if(l>r) continue;
		segment.add(1,1,M,l,r,x[i].w);
		ans+=(x[i+1].y-x[i].y)*segment.calc();
	}printf("Test case #%d\nTotal explored area: %.2f\n\n",++T,ans);
}
signed main(){
	while(scanf("%d",&n)) solve();
}
