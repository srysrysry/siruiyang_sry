#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
inline int read(){
    int f=1,ans=0;char c;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return ans*f;
}
const int N=200011;
struct node{
        int f,ch[3],siz,tag;
    }tr[N];
struct LCT{
    int getf(int k){return tr[tr[k].f].ch[1]==k;}
    int nroot(int k){return tr[tr[k].f].ch[0]==k||tr[tr[k].f].ch[1]==k;}
    void update(int k){tr[k].siz=tr[tr[k].ch[0]].siz+tr[tr[k].ch[1]].siz+1;}
    void pushdown(int k){
        if(k&&tr[k].tag){
            swap(tr[k].ch[0],tr[k].ch[1]);
            tr[tr[k].ch[0]].tag^=1;
            tr[tr[k].ch[1]].tag^=1;
            tr[k].tag=0;
            return;
        }return;
    }
    void rotate(int k){
        int f1=tr[k].f,f2=tr[f1].f;bool d1=getf(k),d2=getf(f1);
        tr[k].f=f2;if(nroot(f1)) tr[f2].ch[d2]=k;
        tr[f1].ch[d1]=tr[k].ch[d1^1];if(tr[k].ch[d1^1]) tr[tr[k].ch[d1^1]].f=f1;
        tr[k].ch[d1^1]=f1;tr[f1].f=k;
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
            int f1=tr[k].f,f2=tr[f1].f;
            if(nroot(f1))
                rotate(getf(k)==getf(f1)?f1:k);
            rotate(k);
        }
    }
    void access(int k){
        for(int fa=0;k;k=tr[fa=k].f)
             splay(k),tr[k].ch[1]=fa,update(k);
    }
    void makeroot(int k){
        access(k);splay(k);
        tr[k].tag^=1;
    }
    void split(int x,int y){
        makeroot(x);
        access(y);splay(y);
    }
    void link(int x,int y){
        makeroot(x);
        tr[x].f=y;
        return;
    }
    void cut(int x,int y){
        split(x,y);
        tr[y].ch[0]=tr[x].f=0;
        update(y);
    }
    int qsiz(int k){return tr[k].siz;}
}lct;
int n,k[N],m;
int main(){
//    freopen("1.in","r",stdin);
    n=read();
    for(int i=1;i<=n;i++) k[i]=read();
    for(int i=1;i<=n;i++){
        int en=i+k[i];
        if(en<=n) lct.link(i,en);
        else lct.link(i,n+1);
    }
    m=read();
    for(int i=1;i<=m;i++){
        int opt=read();
        if(opt==1){int x=read()+1;lct.split(x,n+1);printf("%d\n",lct.qsiz(n+1)-1);}
        else{
            int x=read(),w=read();x+=1;
            if(x+k[x]<=n) lct.cut(x,x+k[x]);
            else lct.cut(x,n+1);
            k[x]=w;
            if(x+k[x]<=n) lct.link(x,x+k[x]);
            else lct.link(x,n+1); 
        }
    }
}

