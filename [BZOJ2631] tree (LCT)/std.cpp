// luogu-judger-enable-o2
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define int long long
#define mod 51061
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int N=100001;
struct Splay{
    int mul,siz,add,sum,tag,f,ch[3],val;
}tr[N];
struct LCT{
    inline int nroot(int k){return tr[tr[k].f].ch[0]==k||tr[tr[k].f].ch[1]==k;}
    inline int getf(int k){return tr[tr[k].f].ch[1]==k;}
    inline void update(int k){
        tr[k].sum=(tr[tr[k].ch[0]].sum+tr[tr[k].ch[1]].sum+tr[k].val)%mod;
        tr[k].siz=tr[tr[k].ch[0]].siz+tr[tr[k].ch[1]].siz+1;
        return;
    }
    inline void rotate(int k){
        int f1=tr[k].f,f2=tr[f1].f,d1=getf(k),d2=getf(f1);
        tr[k].f=f2;if(nroot(f1)) tr[f2].ch[d2]=k;
        tr[f1].ch[d1]=tr[k].ch[d1^1];if(tr[k].ch[d1^1]) tr[tr[k].ch[d1^1]].f=f1;
        tr[k].ch[d1^1]=f1,tr[f1].f=k;
        update(f1),update(k);
        return;
    }
    inline void calc(int k,int add,int mul){
        if(!k) return;
        tr[k].sum=(tr[k].sum*mul+add*tr[k].siz)%mod;
        tr[k].add=(tr[k].add*mul+add)%mod;
        tr[k].mul=(tr[k].mul*mul)%mod;
        tr[k].val=(tr[k].val*mul+add)%mod;
        return;
    }
    inline void pushdown(int k){
        if(tr[k].tag){
            swap(tr[k].ch[0],tr[k].ch[1]);
            tr[tr[k].ch[0]].tag^=1;
            tr[tr[k].ch[1]].tag^=1;
            tr[k].tag=0;
        }
        calc(tr[k].ch[0],tr[k].add,tr[k].mul);
        calc(tr[k].ch[1],tr[k].add,tr[k].mul);
        tr[k].add=0,tr[k].mul=1;
        return;
    }
    inline void pushr(int k){
        if(nroot(k)) pushr(tr[k].f);
        pushdown(k);
    }
    inline void splay(int k){
        pushr(k);
        while(nroot(k)){
            int f1=tr[k].f;
            if(nroot(f1)) rotate(getf(k)==getf(f1)?f1:k);
            rotate(k);
        }return;
    }
    inline void access(int k){
        for(int son=0;k;k=tr[son=k].f)
            splay(k),tr[k].ch[1]=son,update(k);
        return;
    }
    inline void makeroot(int k){
        access(k),splay(k);
        tr[k].tag^=1;
        return;
    }
    inline void split(int x,int y){
        makeroot(x);
        access(y),splay(y);
        return;
    }
    inline void link(int x,int y){
        makeroot(x);
        tr[x].f=y;
        return;
    }
    inline void cut(int x,int y){
        split(x,y);
        tr[y].ch[0]=tr[x].f=0;
        update(y);
        return;
    }
}lct;
int n,q;
char str[3];
signed main(){
    n=read();q=read();
    for(int i=1;i<=n;i++) tr[i].mul=tr[i].siz=tr[i].val=1;
    for(int i=1;i<n;i++){int u=read(),v=read();lct.link(u,v);}
    for(int i=1;i<=q;i++){
        scanf("%s",str+1);
        if(str[1]=='+'){
            int x=read(),y=read(),w=read();
            lct.split(x,y);lct.calc(y,w,1);
        }
        if(str[1]=='-'){
            int x=read(),y=read();
            lct.cut(x,y);x=read(),y=read();
            lct.link(x,y);
        }
        if(str[1]=='*'){
            int x=read(),y=read(),w=read();
            lct.split(x,y);lct.calc(y,0,w);
        }
        if(str[1]=='/'){
            int x=read(),y=read();
            lct.split(x,y);
            printf("%lld\n",tr[y].sum);
        }
    }
}

