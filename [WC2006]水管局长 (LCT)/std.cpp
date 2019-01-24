#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int N=300001;
struct Splay{
    int f,ch[3],tag;
}tr[N];
int n,m,q,val[N],maxn[N];
struct LCT{
    int getf(int k){return tr[tr[k].f].ch[1]==k;}
    int nroot(int k){return tr[tr[k].f].ch[0]==k||tr[tr[k].f].ch[1]==k;}
    void update(int k){
        maxn[k]=k;
        if(val[maxn[tr[k].ch[0]]]>val[maxn[k]]) maxn[k]=maxn[tr[k].ch[0]];
        if(val[maxn[tr[k].ch[1]]]>val[maxn[k]]) maxn[k]=maxn[tr[k].ch[1]];
        return;
    }
    void pushdown(int k){
        if(tr[k].tag){
            swap(tr[k].ch[0],tr[k].ch[1]);
            tr[tr[k].ch[0]].tag^=1;
            tr[tr[k].ch[1]].tag^=1;
            tr[k].tag=0;
        }return;
    }
    void rotate(int k){
        int f1=tr[k].f,f2=tr[f1].f,d1=getf(k),d2=getf(f1);
        tr[k].f=f2;if(nroot(f1)) tr[f2].ch[d2]=k;
        tr[f1].ch[d1]=tr[k].ch[d1^1];if(tr[k].ch[d1^1]) tr[tr[k].ch[d1^1]].f=f1;
        tr[k].ch[d1^1]=f1,tr[f1].f=k;
        update(f1),update(k);
        return;
    }
    void pushr(int k){
        if(nroot(k)) pushr(tr[k].f);
        pushdown(k);
    }
    void splay(int k){
        pushr(k);
        while(nroot(k)){
            int f1=tr[k].f;
            if(nroot(f1)) rotate(getf(k)==getf(f1)?f1:k);
            rotate(k);
        }return;
    }
    void access(int k){
        for(int son=0;k;k=tr[son=k].f)
            splay(k),tr[k].ch[1]=son,update(k);
        return;
    }
    void makeroot(int k){
        access(k),splay(k);
        tr[k].tag^=1;
        return;
    }
    void split(int x,int y){
        makeroot(x);
        access(y),splay(y);
        return;
    }
    void link(int x,int y){
        makeroot(x);
        tr[x].f=y;
        return; 
    }
    void cut(int x,int y){
        split(x,y);
        tr[y].ch[0]=tr[x].f=0;
        return;
    }
}lct;
struct Edge{
    int u,v,w,id;
}x[N];
struct Query{
    int opt,x,y;
}query[N];
int M[1001][1001],dis[1001][1001],f[N],Hash[1001][1001];
bool cmp(Edge x1,Edge x2){return x1.w<x2.w;}
int find(int k){
    if(f[k]==k) return k;
    return f[k]=find(f[k]);
}
stack<int> Q;
int main(){
//	freopen("6.in","r",stdin);
    n=read(),m=read(),q=read();
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=m;i++) x[i].u=read(),x[i].v=read(),x[i].w=read(),dis[x[i].u][x[i].v]=dis[x[i].v][x[i].u]=x[i].w;
    for(int i=1;i<=q;i++){
        query[i].opt=read(),query[i].x=read(),query[i].y=read();
        if(query[i].opt==2) M[query[i].x][query[i].y]=M[query[i].y][query[i].x]=1;
    }
    sort(x+1,x+m+1,cmp);
    for(int i=1;i<=m;i++) x[i].id=i+n,val[i+n]=x[i].w,maxn[i+n]=i+n,Hash[x[i].u][x[i].v]=Hash[x[i].v][x[i].u]=i+n;
    for(int i=1;i<=m;i++){
        if(M[x[i].u][x[i].v]) continue;
        int t1=find(x[i].u),t2=find(x[i].v);
        if(t1==t2) continue;
        f[t2]=t1;
        lct.link(x[i].u,x[i].id);
        lct.link(x[i].v,x[i].id);
    }
    for(int i=q;i>=1;i--){
        if(query[i].opt==1){lct.split(query[i].x,query[i].y);Q.push(val[maxn[query[i].y]]);}
        else{
            int xx=query[i].x,yy=query[i].y;
            lct.split(xx,yy);
            int id=maxn[yy],w=val[id];
            if(w>dis[xx][yy]){
                lct.cut(x[id-n].u,id),lct.cut(x[id-n].v,id);
                lct.link(xx,Hash[xx][yy]),lct.link(yy,Hash[xx][yy]);
            }
        }
    }while(!Q.empty()) printf("%d\n",Q.top()),Q.pop();
}
