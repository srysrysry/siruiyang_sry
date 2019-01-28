#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define ll long long
using namespace std;
inline int read(){
    int f=1,ans=0;char c;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return ans*f;
}
const int N=200001;
int tr[N],n;
ll sum[N<<5],ans,ans1,ans2;
int num,ls[N<<5],rs[N<<5];
void update(int &rt,int l,int r,int x,int y){
    if(!rt) rt=++num;
//  printf("rt:%d\n",rt);
    sum[rt]++;
    if(l==r) return;
    int mid=l+r>>1;
    if(x<=mid) update(ls[rt],l,mid,x,y);
    if(mid<y) update(rs[rt],mid+1,r,x,y);
    return; 
}
int merge(int p,int q,int l,int r){
    if(!p) return q;
    if(!q) return  p;
    ans1+=sum[rs[p]]*sum[ls[q]];
    ans2+=sum[rs[q]]*sum[ls[p]];
    sum[p]+=sum[q];
    if(l==r) return p; 
    int mid=l+r>>1;
    ls[p]=merge(ls[p],ls[q],l,mid),rs[p]=merge(rs[p],rs[q],mid+1,r);
    return p;
}
int dfs(){
    int tmp=read();
    if(!tmp){
        int a=dfs(),b=dfs();
        ans1=ans2=0;
        a=merge(a,b,1,n);
        ans+=min(ans1,ans2);
        return a; 
    }
    update(tr[tmp],1,n,tmp,tmp);
    return tr[tmp];
}
signed main(){
//  freopen("2.in","r",stdin);
    n=read();
    dfs();
    printf("%lld\n",ans);
}
