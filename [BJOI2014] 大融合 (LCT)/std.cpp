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
const int N=100001;
struct Splay{
    int ch[3],siz,unsiz,f,tag;
}tr[N];
struct LCT{
    int nroot(int k){return tr[tr[k].f].ch[0]==k||tr[tr[k].f].ch[1]==k;}
    int getf(int k){return tr[tr[k].f].ch[1]==k;}
    void pushdown(int k){
        if(k&&tr[k].tag){
            swap(tr[k].ch[0],tr[k].ch[1]);
            tr[tr[k].ch[0]].tag^=1;
            tr[tr[k].ch[1]].tag^=1;
            tr[k].tag=0;
        }return;
    }
    void update(int k){
        tr[k].siz=tr[tr[k].ch[0]].siz+tr[tr[k].ch[1]].siz+tr[k].unsiz+1;
        return;
    }
    void rotate(int k){
        int f1=tr[k].f,f2=tr[f1].f,d1=getf(k),d2=getf(f1);
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
            int f1=tr[k].f;
            if(nroot(f1)) rotate(getf(k)==getf(f1)?f1:k);
            rotate(k);
        }return;
    }
    void access(int k){
        for(int son=0;k;k=tr[son=k].f){
            splay(k);tr[k].unsiz+=tr[tr[k].ch[1]].siz;
            tr[k].unsiz-=tr[son].siz;
            tr[k].ch[1]=son;
            update(k);
        }return;
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
        split(x,y);
        tr[x].f=y;tr[y].unsiz+=tr[x].siz;
        update(y);
        return;
    }
}lct;
int n,q;
char str[4];
int main(){
//	freopen("5.in","r",stdin);
    n=read(),q=read();
    for(int i=1;i<=q;i++){
        scanf("%s",str+1);
        if(str[1]=='A'){
            int x=read(),y=read();
            lct.link(x,y); 
        }else{
            int x=read(),y=read();
            lct.split(x,y);
            printf("%d\n",(tr[x].unsiz+1)*(tr[y].unsiz+1));
        }
    }
}

