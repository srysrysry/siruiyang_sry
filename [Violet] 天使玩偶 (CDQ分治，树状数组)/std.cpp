// luogu-judger-enable-o2
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int MAXN=300011;
const int Maxn=1000021;
int n,m,Ans[MAXN],Mb,tot,q0[MAXN],Ma;
struct node{
    int a,b,type,idx;
}query[MAXN<<2],tmp[MAXN<<2],f[MAXN<<2];
bool operator<(node x1,node x2){
    if(x1.a==x2.a) return x1.type<x2.type;
    return x1.a<x2.a;
}
struct BIT{
    int c[Maxn];
    inline int lowbit(int x){return x&-x;}
    inline void update(int x,int val,int opt){
        if(opt==1) q0[++q0[0]]=x;
        for(;x<=Mb;x+=lowbit(x)) {
            if(opt==1)c[x]=max(c[x],val);
            else c[x]=-1;
        }
        return;
    }
    inline int query(int x){
        int res=-1;
        for(;x;x-=lowbit(x)) res=max(res,c[x]);
        return res;
    }
    inline void clear(){
        for(int i=1;i<=q0[0];i++) update(q0[i],0,-1);
        q0[0]=0;
        return;
    }
    inline void init(){memset(c,-1,sizeof(c));return;}
}bit;
inline void solve(int l,int r){
    if(l==r) return;
    int mid=l+r>>1;
    solve(l,mid),solve(mid+1,r);
    int tot=0,p=l,q=mid+1;
    while(p<=mid&&q<=r){
        if(query[p]<query[q]){
            if(query[p].type==1) bit.update(query[p].b,query[p].a+query[p].b,1);
            tmp[++tot]=query[p++];
        }else{
            if(query[q].type==2) {
                int Max=bit.query(query[q].b);
                if(Max!=-1)Ans[query[q].idx]=min(Ans[query[q].idx],query[q].a+query[q].b-Max);
            }
            tmp[++tot]=query[q++]; 
        }
    }
    while(p<=mid){
        if(query[p].type==1) bit.update(query[p].b,query[p].a+query[p].b,1);
        tmp[++tot]=query[p++];
    }
    while(q<=r){
        if(query[q].type==2) {
            int Max=bit.query(query[q].b);
            if(Max!=-1)Ans[query[q].idx]=min(Ans[query[q].idx],query[q].a+query[q].b-Max);
        }
        tmp[++tot]=query[q++]; 
    }
    for(int i=1;i<=tot;i++) query[i+l-1]=tmp[i];
    bit.clear();
    return; 
}
signed main(){
    //freopen("make.in","r",stdin);
    memset(Ans,127,sizeof(Ans));Ans[0]=0;
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        query[++tot].type=1;query[tot].a=read()+1,query[tot].b=read()+1; 
        Mb=max(Mb,query[tot].b);
        Ma=max(Ma,query[tot].a);
    }
    for(int i=1;i<=m;i++){
        query[++tot].type=read(),query[tot].a=read()+1,query[tot].b=read()+1;
        Mb=max(Mb,query[tot].b);
        Ma=max(Ma,query[tot].a);
        if(query[tot].type==2) query[tot].idx=++Ans[0];
    }Ma++,Mb++;
    for(int i=1;i<=tot;i++) f[i]=query[i];
    bit.init();solve(1,tot);
    for(int i=1;i<=tot;i++) query[i]=f[i],query[i].b=Mb-f[i].b; solve(1,tot);
    for(int i=1;i<=tot;i++) query[i]=f[i],query[i].a=Ma-f[i].a;solve(1,tot);
    for(int i=1;i<=tot;i++) query[i]=f[i],query[i].a=Ma-f[i].a,query[i].b=Mb-f[i].b; solve(1,tot);
    for(int i=1;i<=Ans[0];i++) printf("%d\n",Ans[i]);
}
