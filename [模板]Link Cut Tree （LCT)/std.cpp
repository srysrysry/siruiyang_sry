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
const int N=300001;
struct node{
    int f,ch[3],tag;
}tr[N];
int s[N],w[N];
struct LCT{
    inline int getf(int k){return tr[tr[k].f].ch[1]==k;}
    inline int nroot(int k){return tr[tr[k].f].ch[1]==k||tr[tr[k].f].ch[0]==k;}/*判断父亲有没有实边连接儿子，即可判断此点是否为splay的根*/ 
    inline void update(int k){s[k]=s[tr[k].ch[0]]^s[tr[k].ch[1]]^w[k];return;}
    inline void rotate(int k){/*主要注意的是在原树上是要有父亲连接关系的，而不用父亲在splay中连接虚边儿子*/ 
        int f1=tr[k].f,f2=tr[f1].f;bool d=getf(k),d1=getf(f1);
        /*处理k与祖先的关系*/
        tr[k].f=f2;if(nroot(f1))tr[f2].ch[d1]=k;
        /*处理父亲与k的子树*/
        tr[f1].ch[d]=tr[k].ch[d^1];if(tr[k].ch[d^1])tr[tr[k].ch[d^1]].f=f1;
        /*处理k与父亲的关系*/
        tr[k].ch[d^1]=f1;tr[f1].f=k;
        update(f1),update(k);
        return;
    }
    inline void pushdown(int k){
        if(k&&tr[k].tag){
            swap(tr[k].ch[0],tr[k].ch[1]);
            tr[tr[k].ch[0]].tag^=1;
            tr[tr[k].ch[1]].tag^=1;
            tr[k].tag=0;
        }return;
    }
    inline void push(int k){/*对于标记下传可以想到线段树都是要之上往下下传标记，要不然会产生错误*/
        if(nroot(k)) push(tr[k].f);
        pushdown(k);
        return;
    }
    inline void splay(int k){/*将k转到到此splay的根*/
        push(k);/*先标记下传*/
        while(nroot(k)){
            int f1=tr[k].f,f2=tr[f1].f;
            if(nroot(f1))
                rotate(getf(k)==getf(f1)?f1:k);
            rotate(k);
        }
        return;
    }
    inline void access(int k){/*打通一条从k到原树的根的链*/
        for(int son=0;k;k=tr[son=k].f)
            splay(k),tr[k].ch[1]=son,update(k);/*请注意在建完后上面只有从k到原树根的链*/
        return;
    }
   inline void makeroot(int k){/*将x设为原树的根，因为splay(k)后当前k为深度最大的，因为access所导致，所以说当前splay无右子树，若要为使k为原树的根要保证k深度*小，所以要在树上实现反转*/
        access(k);splay(k);
        tr[k].tag^=1;return;
    }
    inline int findroot(int k){/*查找k树的根，通过将k于原根打通一直寻找深度最小的*/
        access(k),splay(k);
        int son;
        while(1){
            pushdown(k);
            if(tr[k].ch[0]) k=tr[k].ch[0];
            else break;
        }
		return k;
    }
    inline void split(int x,int y){/*打通一条x->y的路径*/
        makeroot(x);
        access(y);splay(y);
    }
    inline void link(int x,int y){/*连接x,y 以x为根后连一条虚边*/
        makeroot(x);
        if(findroot(y)!=x) tr[x].f=y;
        return;
    }
    inline void cut(int x,int y){/*切断x,y的边 把x,y放在一颗splay上，然后就进行判断即可*/
        makeroot(x);
        if(findroot(y)==x&&tr[x].f==y&&!tr[x].ch[1]){
            tr[x].f=tr[y].ch[0]=0;
            update(y);
        }return;
    }
}lct;
int n,m;
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++) w[i]=read();
    while(m--){
        int opt=read();
        if(opt==0){int x=read(),y=read();lct.split(x,y);printf("%d\n",s[y]);}
        if(opt==1){int x=read(),y=read();lct.link(x,y);}
        if(opt==2){int x=read(),y=read();lct.cut(x,y);}
        if(opt==3){int x=read(),W=read();lct.splay(x);w[x]=W;lct.update(x);}
    }
    return 0;
}
