#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<climits>
#define int long long
using namespace std;
inline int read(){
    int f=1,ans=0;char c;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return ans*f;
}
const int N=150001;
struct Matrix{
    int s[2][2];
    void clear(){memset(s,0,sizeof(s));}
}tmp[N<<2],t[N];
int cnt,head[N],dp[N][4],m;
struct node{
    int u,v,nex;
}x[N<<1];
void add(int u,int v){
    x[cnt].u=u,x[cnt].v=v,x[cnt].nex=head[u],head[u]=cnt++;
}
Matrix operator*(Matrix a,Matrix b){
    Matrix c;
    c.s[0][0]=c.s[0][1]=c.s[1][1]=c.s[1][0]=INT_MIN;
    for(int i=0;i<=1;i++)
         for(int j=0;j<=1;j++)
              for(int k=0;k<=1;k++) {
              	    c.s[i][j]=max(c.s[i][j],a.s[i][k]+b.s[k][j]);
              }
    return c;
}
int n,v[N],fa[N],deep[N],siz[N],son[N],top[N],low[N],seg[N],rev[N];
void dfs1(int u,int fath){
    fa[u]=fath,deep[u]=deep[fath]+1;siz[u]=1;
    for(int i=head[u];i!=-1;i=x[i].nex){
        if(x[i].v==fath) continue;
        dfs1(x[i].v,u);
        siz[u]+=siz[x[i].v];
        if(siz[x[i].v]>siz[son[u]]) son[u]=x[i].v; 
    } return;
} 
void dfs2(int u,int fath){
    if(son[u]){
        top[son[u]]=top[u];
        seg[son[u]]=++seg[0];
        rev[seg[0]]=son[u];
        dfs2(son[u],u);
        low[u]=low[son[u]];
    }
    else low[u]=u;
    for(int i=head[u];i!=-1;i=x[i].nex){
        if(x[i].v==fath||x[i].v==son[u]) continue;
        top[x[i].v]=x[i].v;
        seg[x[i].v]=++seg[0];
        rev[seg[0]]=x[i].v;
        dfs2(x[i].v,u);
    }return;
}
void Dp(int f,int fath){
    dp[f][1]=v[f];dp[f][0]=0;
    for(int i=head[f];i!=-1;i=x[i].nex){
        if(x[i].v==fath) continue;
        Dp(x[i].v,f);
        dp[f][0]+=max(dp[x[i].v][1],dp[x[i].v][0]);
        dp[f][1]+=dp[x[i].v][0];
    }return;
}
struct segment_tree{
    void build(int k,int l,int r){
        if(l==r){
            int f0=0,f1=v[rev[l]];
            for(int i=head[rev[l]];i!=-1;i=x[i].nex){
                if(x[i].v==fa[rev[l]]||x[i].v==son[rev[l]]) continue;
                f0+=max(dp[x[i].v][0],dp[x[i].v][1]);
                f1+=dp[x[i].v][0];
            }
            Matrix K;K.s[0][0]=K.s[0][1]=f0;K.s[1][0]=f1;K.s[1][1]=-(1ll<<60);
            tmp[k]=t[l]=K;
            return;
        }
        int mid=l+r>>1;
        build(k<<1,l,mid);
        build(k<<1|1,mid+1,r);
        tmp[k]=tmp[k<<1]*tmp[k<<1|1];
    }
    Matrix res;
    void query(int k,int l,int r,int x,int y){
        if(x<=l&&r<=y){if(res.s[0][0]!=LLONG_MIN||res.s[0][1]!=LLONG_MIN||res.s[1][0]!=LLONG_MIN||res.s[1][1]!=LLONG_MIN) res=res*tmp[k];else res=tmp[k];return;}
        int mid=l+r>>1;
        if(x<=mid)query(k<<1,l,mid,x,y);
        if(mid<y)query(k<<1|1,mid+1,r,x,y);
        return;
    }
    Matrix Get(int x){res.s[0][0]=res.s[1][1]=res.s[0][1]=res.s[1][0]=LLONG_MIN;query(1,1,n,seg[top[x]],seg[low[x]]);return res;}
    void modify(int k,int l,int r,int x,int y){
        if(l==r){tmp[k]=t[l];return;}
        int mid=l+r>>1;
        if(x<=mid) modify(k<<1,l,mid,x,y);
        if(mid<y) modify(k<<1|1,mid+1,r,x,y);
        tmp[k]=tmp[k<<1]*tmp[k<<1|1];
        return;
    }
    void change(int x,int w){
        t[seg[x]].s[1][0]+=w-v[x];v[x]=w;
        while(x){
            Matrix a=Get(top[x]);
            modify(1,1,n,seg[x],seg[x]);
            Matrix b=Get(top[x]);x=fa[top[x]];
            if(!x) break;
            t[seg[x]].s[0][1]=t[seg[x]].s[0][0]+=max(b.s[0][0],b.s[1][0])-max(a.s[0][0],a.s[1][0]);
            t[seg[x]].s[1][0]+=b.s[0][0]-a.s[0][0];
        }
        return;
    }
}segment;
int sum;
int pd[2]={INT_MAX,INT_MIN};
char str[4];
signed main(){
	freopen("defense.in","r",stdin);
	freopen("defense.out","w",stdout);
    memset(head,-1,sizeof(head)),memset(dp,-127,sizeof(dp));
    n=read(),m=read();scanf("%s",str+1);
    for(int i=1;i<=n;i++) v[i]=read(),sum+=v[i];
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    dfs1(1,0);seg[1]=rev[1]=seg[0]=top[1]=1;dfs2(1,0);
    Dp(1,0);
    segment.build(1,1,n);
    for(int i=1;i<=m;i++){
        int x=read(),w1=read(),y=read(),w2=read();
        if(w1==0&&w2==0&&(fa[x]==y||fa[y]==x)){printf("-1\n");continue;}
        int valx=v[x],valy=v[y],tmp=0;
        segment.change(x,pd[w1]);if(!w1) tmp+=pd[w1]-valx;
        segment.change(y,pd[w2]);if(!w2) tmp+=pd[w2]-valy;
		Matrix k=segment.Get(1);
		int ans=0;
        ans=sum-max(k.s[0][0],k.s[1][0])+tmp;
        printf("%lld\n",ans);
        segment.change(x,valx);
        segment.change(y,valy);
    }
}
