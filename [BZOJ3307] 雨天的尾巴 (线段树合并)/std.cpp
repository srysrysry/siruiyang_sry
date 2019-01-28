#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
inline int read(){
    int f=1,ans=0;char c;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return ans*f;
}
const int N=100001;
struct node{
    int u,v,nex;
}x[N<<1];
struct Query{
    int u,v,w;
}query[N];
int n,m,fa[N][18],deep[N],head[N],tmp[N],cnt;
map<int,int> M;
void add(int u,int v){
    x[cnt].u=u,x[cnt].v=v,x[cnt].nex=head[u],head[u]=cnt++;
}
void dfs(int f,int fath){
    fa[f][0]=fath,deep[f]=deep[fath]+1;
    for(int i=1;(1<<i)<=deep[f];i++) fa[f][i]=fa[fa[f][i-1]][i-1];
    for(int i=head[f];i!=-1;i=x[i].nex){
        if(x[i].v==fath) continue;
        dfs(x[i].v,f);
    }
}
int lca(int u,int v){
    if(deep[u]<deep[v]) swap(u,v);
    for(int i=17;i>=0;i--)
        if(deep[u]-(1<<i)>=deep[v]) u=fa[u][i];
    if(u==v) return u;
    for(int i=17;i>=0;i--){
        if(fa[u][i]==fa[v][i]) continue;
        u=fa[u][i],v=fa[v][i];
    }return fa[u][0];
}
int tr[N<<4],ls[N<<6],num,rs[N<<6],maxn[N<<6],pos[N<<6];
void update(int &rt,int l,int r,int x,int y,int w){
    if(!rt) rt=++num; 
    if(l==r){maxn[rt]+=w;pos[rt]=l;return;}
    int mid=l+r>>1;
    if(x<=mid) update(ls[rt],l,mid,x,y,w);
    if(mid<y) update(rs[rt],mid+1,r,x,y,w);
    if(maxn[rs[rt]]>maxn[ls[rt]]) maxn[rt]=maxn[rs[rt]],pos[rt]=pos[rs[rt]];
    else maxn[rt]=maxn[ls[rt]],pos[rt]=pos[ls[rt]];
    return;
}
int merge(int p,int q,int l,int r){
    if(!p) return q;
    if(!q) return p;
    if(l==r){maxn[p]+=maxn[q];pos[p]=l;return p;}
    int mid=l+r>>1;
    ls[p]=merge(ls[p],ls[q],l,mid),rs[p]=merge(rs[p],rs[q],mid+1,r);
    if(maxn[rs[p]]>maxn[ls[p]]) maxn[p]=maxn[rs[p]],pos[p]=pos[rs[p]];
    else maxn[p]=maxn[ls[p]],pos[p]=pos[ls[p]];
    return p;
}
int ans[N];
void dfs1(int f,int fath){
    for(int i=head[f];i!=-1;i=x[i].nex){
        if(x[i].v==fath) continue;
        dfs1(x[i].v,f);
        tr[f]=merge(tr[f],tr[x[i].v],1,m);
    }
    if(maxn[tr[f]])ans[f]=pos[tr[f]];
}
int main(){
//	freopen("make.in","r",stdin);
    memset(head,-1,sizeof(head));
    n=read(),m=read();
    for(int i=1;i<n;i++){int u=read(),v=read();add(u,v),add(v,u);}
    for(int i=1;i<=m;i++){
        query[i].u=read(),query[i].v=read(),query[i].w=read();
        tmp[i]=query[i].w;
    }
    dfs(1,0);
    sort(tmp+1,tmp+m+1);
    for(int i=1;i<=m;i++) query[i].w=lower_bound(tmp+1,tmp+m+1,query[i].w)-tmp;
    for(int i=1;i<=m;i++){
        int u=query[i].u,v=query[i].v,color=query[i].w;
        int Lca=lca(u,v);
        update(tr[u],1,m,color,color,1),update(tr[v],1,m,color,color,1);
        update(tr[Lca],1,m,color,color,-1);
        if(fa[Lca][0]) update(tr[fa[Lca][0]],1,m,color,color,-1); 
    }
    dfs1(1,0);
    for(int i=1;i<=n;i++) printf("%d\n",tmp[ans[i]]);
}

