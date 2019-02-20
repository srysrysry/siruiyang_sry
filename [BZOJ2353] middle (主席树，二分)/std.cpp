#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
inline int read(){
    int f=1,ans=0;char c;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return ans*f;
}
const int N=200001;
int n,a[N],tr[N<<1],m,sum[N<<4],num,ls[N<<4],rs[N<<4],maxnl[N<<4],maxnr[N<<4];
void pushdown(int k,int l,int r){
    #define lmaxn maxnl
    #define rmaxn maxnr
    sum[k]=sum[ls[k]]+sum[rs[k]];
    maxnl[k]=max(maxnl[ls[k]],sum[ls[k]]+maxnl[rs[k]]);
    maxnr[k]=max(maxnr[rs[k]],sum[rs[k]]+maxnr[ls[k]]);
    return;
}
void build(int &rt,int l,int r){
    #define lmaxn maxnl
    #define rmaxn maxnr
    rt=++num; 
    sum[rt]=lmaxn[rt]=rmaxn[rt]=r-l+1;
    if(l==r) return ;
    int mid=l+r>>1;
    build(ls[rt],l,mid),build(rs[rt],mid+1,r);
    pushdown(rt,l,r);
    return;
}
void update(int las,int &rt,int l,int r,int x,int y){
    #define lmaxn maxnl
    #define rmaxn maxnr
    rt=++num;ls[rt]=ls[las],rs[rt]=rs[las],sum[rt]=sum[las],lmaxn[rt]=lmaxn[las],rmaxn[rt]=rmaxn[las];
    if(l==r){
        sum[rt]=maxnl[rt]=maxnr[rt]=-1;
        return;
    }
    int mid=l+r>>1;
    if(x<=mid) update(ls[las],ls[rt],l,mid,x,y);
    if(mid<y) update(rs[las],rs[rt],mid+1,r,x,y);
    pushdown(rt,l,r);
    return;
}
int id[N],lastans,q[6];
bool cmp(int x1,int x2){return a[x1]<a[x2];}
int qsum(int k,int l,int r,int x,int y){
    if(x<=l&&r<=y) return sum[k];
    int res=0,mid=l+r>>1;
    if(x<=mid) res+=qsum(ls[k],l,mid,x,y);
    if(mid<y) res+=qsum(rs[k],mid+1,r,x,y);
    return res; 
}
int qlmax(int k,int l,int r,int x,int y){
    if(x<=l&&r<=y) return maxnl[k];
    int mid=l+r>>1;
    if(x>mid) return qlmax(rs[k],mid+1,r,x,y);
    if(y<=mid) return qlmax(ls[k],l,mid,x,y);
    return max(qlmax(ls[k],l,mid,x,y),qsum(ls[k],l,mid,x,y)+qlmax(rs[k],mid+1,r,x,y)); 
}
int qrmax(int k,int l,int r,int x,int y){
    if(x<=l&&r<=y) {
//		printf("l:%d r:%d maxnr:%d k:%d\n ",l,r,maxnr[k],k);
        return maxnr[k];
    }
    int mid=l+r>>1;
    if(x>mid) return qrmax(rs[k],mid+1,r,x,y);
    if(y<=mid) return qrmax(ls[k],l,mid,x,y);
    return max(qrmax(rs[k],mid+1,r,x,y),qsum(rs[k],mid+1,r,x,y)+qrmax(ls[k],l,mid,x,y));
}
bool check(int k){
    int res=0;
    if(q[2]+2<=q[3]) res+=qsum(tr[k],1,n,q[2]+1,q[3]-1); 
    res+=qrmax(tr[k],1,n,q[1],q[2]);
    res+=qlmax(tr[k],1,n,q[3],q[4]);
    return res>=0;
}
int main(){
    memset(maxnl,-127,sizeof(maxnl)),memset(maxnr,-127,sizeof(maxnr));
    n=read();
    for(int i=1;i<=n;i++) a[i]=read(),id[i]=i;
    sort(id+1,id+n+1,cmp);
    build(tr[0],1,n);
    for(int i=1;i<=n;i++) update(tr[i-1],tr[i],1,n,id[i],id[i]);
    m=read();
    for(int i=1;i<=m;i++){
        q[1]=(read()+lastans)%n,q[2]=(read()+lastans)%n,q[3]=(read()+lastans)%n,q[4]=(read()+lastans)%n;
        for(int i=1;i<=4;i++) q[i]++;
        sort(q+1,q+5);
        int l=1,r=n,maxn=0;
        while(l<=r){
            int mid=l+r>>1;
            if(check(mid)) l=mid+1,maxn=max(maxn,mid);
            else r=mid-1; 
        }maxn++;
        printf("%d\n",lastans=a[id[maxn]]);
    }
}

