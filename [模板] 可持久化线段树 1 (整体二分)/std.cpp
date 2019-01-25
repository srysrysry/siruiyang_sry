#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int N=200001;
int tmp[N],a[N],n,m,s[N<<1];
struct node{
    int opt,l,r,val,id;
}q[N<<2],ls[N<<2],rs[N<<2];
int ans[N],c[N];
struct BIT{
    inline int lowbit(int x){return x&-x;}
    void add(int x,int w){
        for(int i=x;i<=n;i+=lowbit(i)) c[i]+=w;
        return;
    }
    int query(int x){
    	int res=0;
    	for(int i=x;i;i-=lowbit(i)) res+=c[i];
    	return res;
    }
}bit;
void solve(int L,int R,int st,int en){
    if(st>en) return;
    if(L==R){
        for(int i=st;i<=en;i++) if(q[i].opt){
            ans[q[i].id]=L;
        }
        return;
    }
    int mid=L+R>>1;
    int lcnt=0,rcnt=0;
    for(int i=st;i<=en;i++){
        int opt=q[i].opt;
        if(opt==0){
            if(q[i].val<=mid){bit.add(q[i].l,1);ls[++lcnt]=q[i];}
            else rs[++rcnt]=q[i];
        }else{
            int ans=bit.query(q[i].r)-bit.query(q[i].l-1);
            if(q[i].val<=ans) ls[++lcnt]=q[i];
            else q[i].val-=ans,rs[++rcnt]=q[i];
        }
    }
    for(int i=1;i<=lcnt;i++) q[st+i-1]=ls[i];
    for(int i=1;i<=rcnt;i++) q[st+lcnt+i-1]=rs[i];
    for(int i=1;i<=lcnt;i++){if(q[st+i-1].opt==0&&q[st+i-1].val<=mid) bit.add(q[st+i-1].l,-1);}
    solve(L,mid,st,st+lcnt-1);
    solve(mid+1,R,st+lcnt,en);
    return;
}
signed main(){
//	freopen("1.in","r",stdin);
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=tmp[i]=read();
    sort(tmp+1,tmp+n+1);
    for(int i=1;i<=n;i++) a[i]=lower_bound(tmp+1,tmp+n+1,a[i])-tmp;
    for(int i=1;i<=n;i++) q[i].opt=0,q[i].l=i,q[i].val=a[i];
    for(int i=1;i<=m;i++) q[i+n].opt=1,q[i+n].l=read(),q[i+n].r=read(),q[i+n].val=read(),q[i+n].id=i;
    solve(-n,n,1,n+m);
    for(int i=1;i<=m;i++) printf("%d\n",tmp[ans[i]]);
}
