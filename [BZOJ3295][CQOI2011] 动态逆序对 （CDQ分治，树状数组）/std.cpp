#include<iostream>
#include<cstdio>
#include<cstring>
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
const int MAXN=100001;
struct node{
    int a,b,c;
}x[MAXN];
int n,m,M[MAXN],q0[MAXN],q1[MAXN],val[MAXN],tot;
bool cmp1(node x1,node x2){
    return x1.a>x2.a;
}
struct BIT{
    int c[MAXN];
    int lowbit(int x){return x&-x;}
    void add(int x,int val,int opt){
        if(opt==1) q0[++q0[0]]=x,q1[++q1[0]]=val;
        for(;x<=n;x+=lowbit(x)) c[x]+=val;
    }
    int query(int x){
        int res=0;
        for(;x;x-=lowbit(x)) res+=c[x];
        return res;
    }
}bit;
node tmp[MAXN];
int Ans1[MAXN],Ans2[MAXN],Ans[MAXN];
void cdq1(int l,int r){
    if(l==r) return;
    int mid=l+r>>1;
    cdq1(l,mid),cdq1(mid+1,r);
    q0[0]=q1[0]=0;
    int p=l,q=mid+1,tot=0;
    while(p<=mid&&q<=r){
        if(x[p].b>x[q].b){
            bit.add(x[p].c,1,1);
            tmp[++tot]=x[p++];
        }else{
            Ans1[x[q].a]+=bit.query(x[q].c-1);
            tmp[++tot]=x[q++];
        }
    }
    while(p<=mid){
        bit.add(x[p].c,1,1);
        tmp[++tot]=x[p++];
    }
    while(q<=r){
        Ans1[x[q].a]+=bit.query(x[q].c-1);
        tmp[++tot]=x[q++];
    }
    for(int i=1;i<=tot;i++) x[l+i-1]=tmp[i];
    for(int i=1;i<=q0[0];i++) bit.add(q0[i],-q1[i],-1);
    return;
}
void cdq2(int l,int r){
    if(l==r) return;
    int mid=l+r>>1;
    cdq2(l,mid),cdq2(mid+1,r);
    q0[0]=q1[0]=0;
    int p=l,q=mid+1,tot=0;
    while(p<=mid&&q<=r){
        if(x[p].b<x[q].b){
            bit.add(x[p].c,1,1);
            tmp[++tot]=x[p++];
        }else{
            Ans2[x[q].a]+=(bit.query(n)-bit.query(x[q].c));
            tmp[++tot]=x[q++];
        }
    }
    while(p<=mid){
        bit.add(x[p].c,1,1);
        tmp[++tot]=x[p++];
    }
    while(q<=r){
        Ans2[x[q].a]+=(bit.query(n)-bit.query(x[q].c));
        tmp[++tot]=x[q++];
    }
    for(int i=1;i<=tot;i++) x[l+i-1]=tmp[i];
    for(int i=1;i<=q0[0];i++) bit.add(q0[i],-q1[i],-1);
    return;
}
int Pos[MAXN];
signed main(){
//	freopen("make.in","r",stdin);
    n=read(),m=read();
    for(int i=1;i<=n;i++) val[i]=read(),Pos[val[i]]=i;
    for(int i=1;i<=m;i++){int Val=read(),pos=Pos[Val];x[++tot].a=tot,x[tot].b=pos,x[tot].c=Val;M[pos]=1;}
    for(int i=1;i<=n;i++){
        if(M[i]) continue;
        x[++tot].a=tot,x[tot].b=i,x[tot].c=val[i];
    } 
    sort(x+1,x+tot+1,cmp1);
    cdq1(1,tot);
    sort(x+1,x+tot+1,cmp1);
    cdq2(1,tot);
    for(int i=1;i<=n;i++) Ans[i]=Ans1[i]+Ans2[i];
    for(int i=n;i>=0;i--) Ans[i]=Ans[i]+Ans[i+1];
    for(int i=1;i<=m;i++) printf("%lld\n",Ans[i]);
}
