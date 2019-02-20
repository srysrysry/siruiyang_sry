#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int N=10001;
struct Splay{
    int ch[3],tag,f;
}tr[N];
struct LCT{
    int getf(int k){return tr[tr[k].f].ch[1]==k;}
    int nroot(int k){return tr[tr[k].f].ch[0]==k||tr[tr[k].f].ch[1]==k;}
    void pushdown(int k){
        if(tr[k].tag){
            swap(tr[k].ch[0],tr[k].ch[1]);
            tr[tr[k].ch[0]].tag^=1;
            tr[tr[k].ch[1]].tag^=1;
            tr[k].tag=0;
        }return;
    }
    void rotate(int k){
        int f1=tr[k].f,f2=tr[f1].f;int d1=getf(k),d2=getf(f1);
        tr[k].f=f2;if(nroot(f1)) tr[f2].ch[d2]=k;
        tr[f1].ch[d1]=tr[k].ch[d1^1];if(tr[k].ch[d1^1]) tr[tr[k].ch[d1^1]].f=f1;
        tr[k].ch[d1^1]=f1;tr[f1].f=k;
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
                rotate(getf(f1)==getf(f2)?f1:k);
            rotate(k);
        }return;
    }
    void access(int k){
        for(int son=0;k;k=tr[son=k].f)
            splay(k),tr[k].ch[1]=son;
        return;
    }
    void makeroot(int k){
        access(k),splay(k);
        tr[k].tag^=1;
        return;
    }
    void link(int x,int y){
        makeroot(x);
        tr[x].f=y;
    }
    int findroot(int k){
        access(k),splay(k);
        while(1){
            pushdown(k);
            if(tr[k].ch[0]) k=tr[k].ch[0];
            else break;
        }return k;
    }
    void cut(int x,int y){
        makeroot(x);access(y);splay(y);
        tr[y].ch[0]=tr[x].f=0;
        return;
    }
    bool connect(int x,int y){
        makeroot(x);
        if(findroot(y)!=x) return 0;
        return 1;
    }
}lct;
int n,m;
char str[11];
int main(){
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        scanf("%s",str+1);
        if(str[1]=='Q'){
            int x=read(),y=read();
            bool k=lct.connect(x,y);
            if(k) printf("Yes\n");
            else printf("No\n");
        }
        if(str[1]=='C'){
            int x=read(),y=read();
            lct.link(x,y);
        }
        if(str[1]=='D'){
            int x=read(),y=read();
            lct.cut(x,y);
        }
    }
}

