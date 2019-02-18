#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<climits>
using namespace std;
inline int read(){
	int f=1,ans=0;char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}
const int MAXN=1000001;
int maxn[MAXN<<2],tag[MAXN<<2];
struct segment{
	void build(int k,int l,int r){
		if(l==r){maxn[k]=0;return;}
		int mid=l+r>>1;
		build(k<<1,l,mid),build(k<<1|1,mid+1,r);
		maxn[k]=max(maxn[k<<1],maxn[k<<1|1]); 
	}
	void pushdown(int k,int l,int r){
		if(!tag[k]) return;
		maxn[k<<1]+=tag[k];
		maxn[k<<1|1]+=tag[k];
		tag[k<<1]+=tag[k];
		tag[k<<1|1]+=tag[k];
		tag[k]=0;
		return;
	}
	void update(int k,int l,int r,int x,int y,int w){
		if(x<=l&&r<=y){;tag[k]+=w;maxn[k]+=w;return;}
		pushdown(k,l,r);
		int mid=l+r>>1;
		if(x<=mid) update(k<<1,l,mid,x,y,w);
		if(mid<y) update(k<<1|1,mid+1,r,x,y,w);
		maxn[k]=max(maxn[k<<1],maxn[k<<1|1]);
		return; 
	}
	int qMax(int k,int l,int r,int x,int y){
		if(x<=l&&r<=y) return maxn[k];
		pushdown(k,l,r);
		int mid=l+r>>1,res=-1;
		if(x<=mid) res=max(res,qMax(k<<1,l,mid,x,y));
		if(mid<y) res=max(res,qMax(k<<1|1,mid+1,r,x,y));
		maxn[k]=max(maxn[k<<1],maxn[k<<1|1]);
		return res;
	}
}segment;
int n,m;
struct node{
	int l,r,len;
}a[MAXN];
int tmp[MAXN<<2],minn=INT_MAX;
bool cmp(node x1,node x2){return x1.len<x2.len;}
int main(){
//	freopen("12.in","r",stdin);
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i].l=read(),a[i].r=read(),tmp[++tmp[0]]=a[i].l,tmp[++tmp[0]]=a[i].r,a[i].len=a[i].r-a[i].l;
	sort(tmp+1,tmp+tmp[0]+1);
	for(int i=1;i<=n;i++) a[i].l=lower_bound(tmp+1,tmp+tmp[0]+1,a[i].l)-tmp,a[i].r=lower_bound(tmp+1,tmp+tmp[0]+1,a[i].r)-tmp;
	sort(a+1,a+n+1,cmp); 
	int l=1;segment.build(1,1,tmp[0]);
	segment.update(1,1,tmp[0],a[1].l,a[1].r,1);
	for(int i=2;i<=n;i++){
		segment.update(1,1,tmp[0],a[i].l,a[i].r,1);
		if(segment.qMax(1,1,tmp[0],a[i].l,a[i].r)>=m){
			while(l<i){
				segment.update(1,1,tmp[0],a[l].l,a[l].r,-1);
				if(segment.qMax(1,1,tmp[0],a[i].l,a[i].r)>=m) ++l;
				else{segment.update(1,1,tmp[0],a[l].l,a[l].r,1);break;}
			}
		    minn=min(minn,a[i].len-a[l].len);
		}
	}
	if(minn==INT_MAX){printf("-1");return 0;}
	printf("%d\n",minn);
	return 0;
}
