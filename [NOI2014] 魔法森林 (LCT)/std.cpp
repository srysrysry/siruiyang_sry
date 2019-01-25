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
const int N=200001;
int maxn[N],val[N];
struct Splay{
    int ch[3],f,tag;
}tr[N];
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
        if(k&&tr[k].tag){
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
        tr[k].ch[d1^1]=f1;tr[f1].f=k;
        update(f1),update(k);
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
        } return;
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
    void link(int x,int y){
//		printf("link x:%d y:%d\n",x,y); 
        makeroot(x);
        tr[x].f=y;
        return;
    }
    void split(int x,int y){
        makeroot(x);
        access(y),splay(y);
        return;
    }
    void cut(int x,int y){
//		printf("cut x:%d y:%d\n",x,y);
        split(x,y);
        tr[y].ch[0]=tr[x].f=0;
        update(y);
        return;
    }
    int findroot(int k){
        access(k),splay(k);
        while(1){
            pushdown(k);
            if(tr[k].ch[0]) k=tr[k].ch[0];
            else break;
        }return k;
    }
    bool qconect(int x,int y){
        if(findroot(x)==findroot(y)) return 1;
        return 0;
    }
}lct;
struct Edge{
    int u,v,aval,bval;
}e[N];
bool cmp(Edge e1,Edge e2){
    if(e1.aval==e2.aval) return e1.bval<e2.bval;
    return e1.aval<e2.aval;
}
int n,m,minn=INT_MAX;
int id,Val;
bool flag;
int main(){
//	freopen("4.in","r",stdin);
    n=read(),m=read();
    for(int i=1;i<=m;i++) e[i].u=read(),e[i].v=read(),e[i].aval=read(),e[i].bval=read();
    sort(e+1,e+m+1,cmp);
    for(int i=1;i<=m;i++){
        if(!lct.qconect(e[i].u,e[i].v)){maxn[i+n]=i+n,val[i+n]=e[i].bval;lct.link(e[i].u,i+n);lct.link(e[i].v,i+n);}
        else{
            lct.split(e[i].u,e[i].v);
            id=maxn[e[i].v],Val=val[id];
            if(Val>e[i].bval){
                maxn[i+n]=i+n,val[i+n]=e[i].bval;
                lct.cut(e[id-n].u,id);
                lct.cut(e[id-n].v,id);
                lct.link(e[i].u,i+n);
                lct.link(e[i].v,i+n);
            }
        }
        if(lct.findroot(1)==lct.findroot(n)){
            flag=1;
            lct.split(1,n);
            Val=val[maxn[n]];
            minn=min(minn,e[i].aval+Val);
        }
    }
    if(!flag){printf("-1");return 0;}
    printf("%d\n",minn);
}

