#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int MAXN=4000011;
int n,q1[MAXN],q2[MAXN],S;
struct BIT{
    int c[MAXN];
    int lowbit(int x){return x&-x;}
    void add(int x,int val,int opt){
        if(opt==1)q1[++q1[0]]=x,q2[++q2[0]]=val;
        for(;x<=n;x+=lowbit(x)) c[x]+=val;
    }
    int query(int x){
        int res=0;
        for(;x;x-=lowbit(x)) res+=c[x];
        return res;
    }
}bit;
struct node{
    int x,y,val,type;
}query[MAXN<<1];
int tot,Ans[MAXN<<1];
bool operator<(node x1,node x2){
    if(x1.x==x2.x) return x1.type<x2.type;
    return x1.x<x2.x;
}
node tmp[MAXN];
void cdq(int l,int r){
    if(l==r) return;
    int mid=l+r>>1;
    cdq(l,mid),cdq(mid+1,r);
    q1[0]=q2[0]=0;
    int p=l,q=mid+1,tot=0;
    while(p<=mid&&q<=r){
        if(query[p]<query[q]){
            if(query[p].type==1) bit.add(query[p].y,query[p].val,1);
            tmp[++tot]=query[p++];
        }else{
            if(query[q].type==2) Ans[query[q].val]-=bit.query(query[q].y);
            if(query[q].type==3) Ans[query[q].val]+=bit.query(query[q].y);
            tmp[++tot]=query[q++];
        }
    }
    while(p<=mid){
        if(query[p].type==1) bit.add(query[p].y,query[p].val,1);
        tmp[++tot]=query[p++];
    }
    while(q<=r){
        if(query[q].type==2) Ans[query[q].val]-=bit.query(query[q].y);
        if(query[q].type==3) Ans[query[q].val]+=bit.query(query[q].y);
        tmp[++tot]=query[q++];
    }
    for(int i=1;i<=tot;i++) query[l+i-1]=tmp[i];
    for(int i=1;i<=q1[0];i++) bit.add(q1[i],-q2[i],-1);
    return;
}
int main(){
//	freopen("2.in","r",stdin);
//	freopen("11.out","w",stdout);
    S=read(),n=read()+1;
    while(1){
        int opt=read();
        if(opt==1) query[++tot].type=1,query[tot].x=read()+1,query[tot].y=read()+1,query[tot].val=read();
        if(opt==2){
            int x1=read()+1,y1=read()+1,x2=read()+1,y2=read()+1;
            query[++tot].type=2,query[tot].x=x1-1,query[tot].y=y2,query[tot].val=++Ans[0];
            query[++tot].type=2,query[tot].x=x2,query[tot].y=y1-1,query[tot].val=Ans[0];
            query[++tot].type=3,query[tot].x=x1-1,query[tot].y=y1-1,query[tot].val=Ans[0];
            query[++tot].type=3,query[tot].x=x2,query[tot].y=y2,query[tot].val=Ans[0];
            Ans[Ans[0]]=(x2-x1+1)*(y2-y1+1)*S;
        }
        if(opt==3) break;
    }
    cdq(1,tot);
    for(int i=1;i<=Ans[0];i++) printf("%d\n",Ans[i]);
    return 0;
}

