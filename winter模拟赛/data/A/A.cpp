#include<iostream>
#include<cstring>
#include<cstdio>
#include<climits>
#include<algorithm>
#define mod 998244353
#define ll long long
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int N=500001;
ll mul[N<<2],sum[N<<2],ans[N<<2];
int ff,cnt,n,q,deep[N],fa[N],top[N],seg[N],id[N],son[N],cover[N<<2];
int rt,head[N],val[N<<2];
struct node{
    int u,v,nex;
}x[N<<1];
inline void add(int u,int v){
    x[cnt].u=u,x[cnt].v=v,x[cnt].nex=head[u],head[u]=cnt++;
}
ll maxnson[N],size[N];
inline void Getrt(int f,int fath){
    size[f]=1;
    for(int i=head[f];i!=-1;i=x[i].nex){
        if(x[i].v==fath) continue;
        Getrt(x[i].v,f);
        size[f]+=size[x[i].v];
        maxnson[f]=max(maxnson[f],size[x[i].v]);
    }
    maxnson[f]=max(maxnson[f],n-size[f]);
    if((maxnson[rt]==maxnson[f])&&(f<rt)||(maxnson[f]<maxnson[rt])) rt=f;
    return;
}
inline int getrt(){
    rt=0;
    maxnson[0]=INT_MAX;
    Getrt(1,0);
    return rt;
}
struct Node{
    int deep,u;
}a[4];
bool cmp(Node x1,Node x2){return x1.deep<x2.deep;}
struct LCA{
    int fa[N][20],deep[N];
    inline void init(){memset(fa,0,sizeof(fa)),memset(deep,0,sizeof(deep));}
    inline void dfs(int f,int fath){
        fa[f][0]=fath;deep[f]=deep[fath]+1;
        for(int i=1;(1<<i)<=deep[f];i++) fa[f][i]=fa[fa[f][i-1]][i-1];
        for(int i=head[f];i!=-1;i=x[i].nex){
            if(x[i].v==fath) continue;
            dfs(x[i].v,f);
        }
    }
    inline int lca(int u,int v){
        if(deep[u]<deep[v]) swap(u,v);
        for(int i=19;i>=0;i--)
           if(deep[u]-(1<<i)>=deep[v]) u=fa[u][i];
           if(u==v) return u;
        for(int i=19;i>=0;i--){
            if(fa[u][i]==fa[v][i]) continue;
            u=fa[u][i],v=fa[v][i];
        }return fa[u][0];
    }
    inline int getlca(int rt,int u,int v){
        int k1=lca(rt,u),k2=lca(rt,v),k3=lca(u,v);
        int d1=deep[k1],d2=deep[k2],d3=deep[k3];
        a[1].deep=d1,a[1].u=k1;a[2].deep=d2,a[2].u=k2;a[3].deep=d3,a[3].u=k3;
        sort(a+1,a+4,cmp);
        return a[3].u;
    }
}Q;
struct INIT{
    inline void dfs1(int f,int fath){
        fa[f]=fath;
        size[f]=1;deep[f]=deep[fath]+1;
        for(int i=head[f];i!=-1;i=x[i].nex){
            if(x[i].v==fath) continue;
            dfs1(x[i].v,f);
            size[f]+=size[x[i].v];
            if(size[son[f]]<size[x[i].v]) son[f]=x[i].v;
        }return;
    }
    inline void dfs2(int f,int fath){
        if(son[f]){
            seg[son[f]]=++seg[0];
            top[son[f]]=top[f];
            id[seg[0]]=son[f];
            dfs2(son[f],f);
        }
        for(int i=head[f];i!=-1;i=x[i].nex){
            if(x[i].v==fath||x[i].v==son[f]) continue;
            seg[x[i].v]=++seg[0];
            top[x[i].v]=x[i].v;
            id[seg[0]]=x[i].v;
            dfs2(x[i].v,f);
        }return;
    }
}INNt;
struct segment_tree{
    inline void pushdown(int k,int l,int r){
        int mid=l+r>>1;
        if(cover[k]!=ff){
            cover[k<<1]=cover[k],cover[k<<1|1]=cover[k];
            sum[k<<1]=0,sum[k<<1|1]=0,mul[k<<1]=1,mul[k<<1|1]=1;
            ans[k<<1]=(mid-l+1)*cover[k],ans[k<<1|1]=(r-mid)*cover[k];ans[k<<1]%=mod;ans[k<<1|1]%=mod;
            cover[k]=ff;
        }
        ans[k<<1]=(((ans[k<<1]*mul[k])%mod)+((sum[k]*(mid-l+1)%mod)))%mod;
        ans[k<<1|1]=(((ans[k<<1|1]*mul[k])%mod)+((sum[k]*(r-mid)))%mod)%mod;
        mul[k<<1]*=mul[k],mul[k<<1]%=mod;mul[k<<1|1]*=mul[k],mul[k<<1|1]%=mod;
        sum[k<<1]*=mul[k],sum[k<<1]%=mod;sum[k<<1|1]*=mul[k],sum[k<<1|1]%=mod;
        sum[k<<1]+=sum[k],sum[k<<1]%=mod;sum[k<<1|1]+=sum[k],sum[k<<1|1]%=mod;
        mul[k]=1,sum[k]=0;
        return;
    }
    inline void build(int k,int l,int r){
        mul[k]=1,sum[k]=0;
        if(l==r){ans[k]=val[id[l]];return;}
        int mid=l+r>>1;
        build(k<<1,l,mid),build(k<<1|1,mid+1,r);
        ans[k]=ans[k<<1]+ans[k<<1|1];
        ans[k]%=mod;
        return;
    }
    inline void add(int k,int l,int r,int x,int y,int w){
        if(x<=l&&r<=y){
            ans[k]+=(r-l+1)*1ll*w;ans[k]%=mod;
            sum[k]+=w;sum[k]%=mod;
            return;
        } 
        pushdown(k,l,r);
        int mid=l+r>>1; 
        if(x<=mid) add(k<<1,l,mid,x,y,w);
        if(mid<y) add(k<<1|1,mid+1,r,x,y,w);
        ans[k]=ans[k<<1]+ans[k<<1|1];
        ans[k]%=mod;
        return;
    }
    inline void mul1(int k,int l,int r,int x,int y,int w){
        if(x<=l&&r<=y){
            ans[k]*=w*1ll;ans[k]%=mod;
            sum[k]*=w*1ll,sum[k]%=mod;
            mul[k]*=w*1ll;mul[k]%=mod;
            return;
        }
        pushdown(k,l,r);
        int mid=l+r>>1;
        if(x<=mid) mul1(k<<1,l,mid,x,y,w);
        if(mid<y) mul1(k<<1|1,mid+1,r,x,y,w);
        ans[k]=ans[k<<1]+ans[k<<1|1];
        ans[k]%=mod;
        return;
    }
    inline int query(int k,int l,int r,int x,int y){
        if(x<=l&&r<=y) return ans[k];
        pushdown(k,l,r);
        int mid=l+r>>1,res=0;
        if(x<=mid) res+=query(k<<1,l,mid,x,y);
        if(mid<y) res+=query(k<<1|1,mid+1,r,x,y);
        ans[k]=ans[k<<1]+ans[k<<1|1];
        ans[k]%=mod;
        return res%mod;
    }
    inline void change(int k,int l,int r,int x,int y,ll w){
        if(x<=l&&r<=y){
            cover[k]=w,ans[k]=(r-l+1)*w;
            cover[k]%=mod,ans[k]%=mod;
            sum[k]=0,mul[k]=1;
            return;
        }
        pushdown(k,l,r);
        int mid=l+r>>1;
        if(x<=mid) change(k<<1,l,mid,x,y,w);
        if(mid<y) change(k<<1|1,mid+1,r,x,y,w);
        ans[k]=ans[k<<1]+ans[k<<1|1];
        ans[k]%=mod;
        return;
    }
}segment;
inline void add(int x,int y,int w){
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(deep[fx]<deep[fy]) swap(fx,fy),swap(x,y);
        segment.add(1,1,seg[0],seg[fx],seg[x],w);
        x=fa[fx],fx=top[x];
    }
    if(deep[x]>deep[y]) swap(x,y);
    segment.add(1,1,seg[0],seg[x],seg[y],w);
    return;
}
inline void mul1(int x,int y,int w){
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(deep[fx]<deep[fy]) swap(fx,fy),swap(x,y);
        segment.mul1(1,1,seg[0],seg[fx],seg[x],w);
        x=fa[fx],fx=top[x];
    }
    if(deep[x]>deep[y]) swap(x,y);
    segment.mul1(1,1,seg[0],seg[x],seg[y],w);
    return;
}
inline void change(int x,int y,int w){
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(deep[fx]<deep[fy]) swap(fx,fy),swap(x,y);
        segment.change(1,1,seg[0],seg[fx],seg[x],w);
        x=fa[fx],fx=top[x];
    }
    if(deep[x]>deep[y]) swap(x,y);
    segment.change(1,1,seg[0],seg[x],seg[y],w);
    return;
}
inline ll ask(int x,int y){
    ll res=0;int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(deep[fx]<deep[fy]) swap(x,y),swap(fx,fy);
        res+=segment.query(1,1,seg[0],seg[fx],seg[x]);
        res%=mod;
        x=fa[fx],fx=top[x];
    }
    if(deep[x]>deep[y]) swap(x,y);
    res+=segment.query(1,1,seg[0],seg[x],seg[y]);
    res%=mod;
    return res;
}
inline int lca(int x,int y){
    int fx=top[x],uu=x,fy=top[y],lst=x;
    while(fx!=fy){
        if(deep[fx]<deep[fy]) swap(fx,fy),swap(x,y);
        lst=fx;
        x=fa[fx],fx=top[x];
    }
    if(deep[x]>deep[y]) swap(x,y);
    if(x!=uu) return 0;
    if(fa[lst]==x) return lst;
    return son[x];
}
char str[8];
int main(){
	freopen("50.in","r",stdin);
	freopen("50.out","w",stdout);
    memset(cover,-1,sizeof(cover));ff=cover[1];
    memset(head,-1,sizeof(head));
    n=read(),q=read();
    for(int i=1;i<=n;i++) val[i]=read();
    for(int i=2;i<=n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    rt=getrt();
    Q.init();Q.dfs(rt,0);
    INNt.dfs1(rt,0);seg[rt]=1,id[1]=rt,seg[0]=1,top[rt]=rt;INNt.dfs2(rt,0);
    segment.build(1,1,seg[0]);
    for(int i=1;i<=q;i++){ 
        int opt=read();
        if(opt==1) rt=read();
        if(opt==2){
            int u=read(),v=read(),w=read();scanf("%s",str+1);
            if(str[1]=='a') add(u,v,w);
            if(str[1]=='m') mul1(u,v,w);
            if(str[1]=='c') change(u,v,w);
        }
        if(opt==3){
            int u=read(),w=read();scanf("%s",str+1);
            if(str[1]=='a'){
                w%=mod;
                if(u==rt){segment.add(1,1,seg[0],1,seg[0],w);continue;}
                int k;
                if(k=lca(u,rt)){int l=seg[k]-1,r=seg[k]+size[k]-1;segment.add(1,1,seg[0],1,l,w);if(r+1<=n)segment.add(1,1,seg[0],r+1,n,w);}
                else segment.add(1,1,seg[0],seg[u],seg[u]+size[u]-1,w);
            }
            if(str[1]=='m'){
                w%=mod;
                if(u==rt){segment.mul1(1,1,seg[0],1,seg[0],w);continue;}
                int k;
                if(k=lca(u,rt)){int l=seg[k]-1,r=seg[k]+size[k]-1;segment.mul1(1,1,seg[0],1,l,w);if(r+1<=n)segment.mul1(1,1,seg[0],r+1,n,w);}
                else segment.mul1(1,1,seg[0],seg[u],seg[u]+size[u]-1,w);
            }
            if(str[1]=='c'){
                w%=mod;
                if(u==rt){segment.change(1,1,seg[0],1,seg[0],w);continue;}
                int k;
                if(k=lca(u,rt)){int l=seg[k]-1,r=seg[k]+size[k]-1;segment.change(1,1,seg[0],1,l,w);if(r+1<=n)segment.change(1,1,seg[0],r+1,n,w);}
                else segment.change(1,1,seg[0],seg[u],seg[u]+size[u]-1,w%mod);
            }
        }
        if(opt==4){
            int u=read(),v=read();
            printf("%d\n",ask(u,v)%mod);
        }
        if(opt==5){
            int u=read();
            int k;
            if(u==rt){printf("%d\n",ans[1]%mod);continue;}
 			if(k=lca(u,rt)){int l=seg[k]-1,r=seg[k]+size[k]-1;ll res=0;res+=segment.query(1,1,seg[0],1,l);if(r+1<=n)res+=segment.query(1,1,seg[0],r+1,n);printf("%d\n",res%mod);}
            else printf("%d\n",((segment.query(1,1,seg[0],seg[u],seg[u]+size[u]-1)%mod)+mod)%mod);
        }
        if(opt==6){
            int u=read(),v=read();
            printf("%d\n",Q.getlca(rt,u,v));
        }
    }
    return 0;
}
