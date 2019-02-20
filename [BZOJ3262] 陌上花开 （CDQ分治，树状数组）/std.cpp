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
const int MAXN=200001;
int n,q1[MAXN],q2[MAXN];
int k,Ans[MAXN];
struct BIT{
    int c[MAXN];
    int lowbit(int x){return x&-x;}
    void add(int x,int val,int opt){
        if(opt==1)q1[++q1[0]]=x;q2[++q2[0]]=val;
        for(int i=x;i<=k;i+=lowbit(i)) c[i]+=val;
        return; 
    }
    int query(int x){
        int res=0;
        for(int i=x;i;i-=lowbit(i)) res+=c[i];
        return res;
    }
    void mem(){memset(c,0,sizeof(c));return;}
}bit;
struct node{
    int a,b,c,pos;
}x[MAXN],f[MAXN];
bool cmp(node x1,node x2){
    if(x1.a==x2.a){
        if(x1.b==x2.b) return x1.c<x2.c;
        return x1.b<x2.b;
    }
    return x1.a<x2.a;
}
int num[MAXN];
node tmp[MAXN];
int Cnt[MAXN],Tot;
bool cmp2(node x1,node x2){
    if(x1.b==x2.b){
        if(x1.c==x2.c) return x1.a<x2.a;
        return x1.c<x2.c;
    }return x1.b<x2.b;
}
void cdq(int l,int r){
    if(l==r) return;
    int mid=l+r>>1;
    cdq(l,mid),cdq(mid+1,r);
    sort(x+l,x+mid+1,cmp2);
    sort(x+mid+1,x+r+1,cmp2);
    int p=l,q=mid+1,tot=0;q1[0]=q2[0]=0;
    while(p<=mid&&q<=r){
        if(x[p].b<=x[q].b){
            bit.add(x[p].c,Cnt[x[p].pos],1);
            tmp[++tot]=x[p++];
        }else{
            Ans[x[q].pos]+=bit.query(x[q].c);
            tmp[++tot]=x[q++];
        }
    }
    while(p<=mid) bit.add(x[p].c,Cnt[x[p].pos],1),tmp[++tot]=x[p++];
    while(q<=r) Ans[x[q].pos]+=bit.query(x[q].c),tmp[++tot]=x[q++];
    for(int i=1;i<=tot;i++) x[l+i-1]=tmp[i];
    for(int i=1;i<=q1[0];i++) bit.add(q1[i],-q2[i],-1);
    return;
}
signed main(){
//	freopen("3.in","r",stdin);
//	freopen("3.out","w",stdout);
    n=read(),k=read();
    for(int i=1;i<=n;i++) f[i].a=read(),f[i].b=read(),f[i].c=read(),f[i].pos=i;
    sort(f+1,f+n+1,cmp);
    for(int i=1;i<=n;i++){
        x[++Tot]=f[i];
        x[Tot].pos=Tot;
        int r=i;
        while(f[i].a==f[r].a&&f[i].b==f[r].b&&f[i].c==f[r].c&&i<=n&&r<=n) r++;
        Cnt[Tot]=r-i;
        i=r-1;
    }
    cdq(1,Tot);
    for(int i=1;i<=Tot;i++) num[Ans[i]+Cnt[i]-1]+=Cnt[i];
    for(int i=0;i<n;i++) printf("%lld\n",num[i]);
}
