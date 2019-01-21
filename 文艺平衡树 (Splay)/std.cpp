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
const int N=100111;
struct Splay_node{
    int ch[2],cnt,size,num,f;
    bool tag;
}tr[N];
int rt,new_node,val[N];
int n,m;
struct Splay{
    void pushdown(int k){
        if(tr[k].tag&&k){
            tr[tr[k].ch[0]].tag^=1;tr[tr[k].ch[1]].tag^=1;
            swap(tr[k].ch[0],tr[k].ch[1]);
            tr[k].tag=0;
        }return;
    }
    void update(int k){
        tr[k].size=tr[k].cnt;
        tr[k].size+=tr[tr[k].ch[0]].size;
        tr[k].size+=tr[tr[k].ch[1]].size;
        return; 
    }
    int getf(int k){return tr[tr[k].f].ch[1]==k;}
    void rotate(int k){
        int f1=tr[k].f,f2=tr[f1].f;bool d=getf(k);
        pushdown(f1),pushdown(k);
        tr[f1].ch[d]=tr[k].ch[d^1];tr[tr[k].ch[d^1]].f=f1;
        tr[k].ch[d^1]=f1;tr[f1].f=k;tr[k].f=f2;
        if(f2) tr[f2].ch[tr[f2].ch[1]==f1]=k;
        update(f1),update(k);
        return; 
    }
    void splay(int k,int goal){
        for(int fa;(fa=tr[k].f)!=goal;rotate(k)) 
            if(tr[fa].f!=goal) rotate(getf(k)==getf(fa)?fa:k);
        if(!goal)rt=k;
        return;
    }
    int build(int l,int r,int fa){
        if(l>r) return 0;
        int mid=l+r>>1,k=++new_node;
        tr[k].f=fa,tr[k].num=val[mid],tr[k].cnt=1,tr[k].size=1;
        tr[k].ch[0]=build(l,mid-1,k);
        tr[k].ch[1]=build(mid+1,r,k);
        update(k);
        return k;
    }
    int find(int k){
        int now=rt;
        while(1){
        	pushdown(now);
            if(k<=tr[tr[now].ch[0]].size) now=tr[now].ch[0];
            else{
                k-=tr[tr[now].ch[0]].size+1;
                if(!k) return now;
                now=tr[now].ch[1];
            }
        }
    }
    void reverse(int x,int y){
        int l=x-1,r=y+1;
        int f1=find(l),f2=find(r);
        splay(f1,0);
        splay(f2,rt);
        int k=tr[tr[rt].ch[1]].ch[0];
        tr[k].tag^=1;
        return;
    }
    void dfs(int k){
        if(k==0) return;
        pushdown(k);
        dfs(tr[k].ch[0]);
        if(tr[k].num!=INT_MAX&&tr[k].num!=INT_MIN) printf("%d ",tr[k].num);
        dfs(tr[k].ch[1]);
        return;
    }
}S;
int main(){
    n=read(),m=read();
    val[1]=INT_MIN,val[n+2]=INT_MAX;
    for(int i=2;i<=n+1;i++) val[i]=i-1;
    rt=S.build(1,n+2,0);
    for(int i=1;i<=m;i++){
        int l=read(),r=read();
        S.reverse(l+1,r+1);
    }
    S.dfs(rt);
    return 0;
}
