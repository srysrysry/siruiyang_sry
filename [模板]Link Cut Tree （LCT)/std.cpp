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
    inline int nroot(int k){return tr[tr[k].f].ch[1]==k||tr[tr[k].f].ch[0]==k;}/*�жϸ�����û��ʵ�����Ӷ��ӣ������жϴ˵��Ƿ�Ϊsplay�ĸ�*/ 
    inline void update(int k){s[k]=s[tr[k].ch[0]]^s[tr[k].ch[1]]^w[k];return;}
    inline void rotate(int k){/*��Ҫע�������ԭ������Ҫ�и������ӹ�ϵ�ģ������ø�����splay��������߶���*/ 
        int f1=tr[k].f,f2=tr[f1].f;bool d=getf(k),d1=getf(f1);
        /*����k�����ȵĹ�ϵ*/
        tr[k].f=f2;if(nroot(f1))tr[f2].ch[d1]=k;
        /*��������k������*/
        tr[f1].ch[d]=tr[k].ch[d^1];if(tr[k].ch[d^1])tr[tr[k].ch[d^1]].f=f1;
        /*����k�븸�׵Ĺ�ϵ*/
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
    inline void push(int k){/*���ڱ���´������뵽�߶�������Ҫ֮�������´���ǣ�Ҫ��Ȼ���������*/
        if(nroot(k)) push(tr[k].f);
        pushdown(k);
        return;
    }
    inline void splay(int k){/*��kת������splay�ĸ�*/
        push(k);/*�ȱ���´�*/
        while(nroot(k)){
            int f1=tr[k].f,f2=tr[f1].f;
            if(nroot(f1))
                rotate(getf(k)==getf(f1)?f1:k);
            rotate(k);
        }
        return;
    }
    inline void access(int k){/*��ͨһ����k��ԭ���ĸ�����*/
        for(int son=0;k;k=tr[son=k].f)
            splay(k),tr[k].ch[1]=son,update(k);/*��ע���ڽ��������ֻ�д�k��ԭ��������*/
        return;
    }
   inline void makeroot(int k){/*��x��Ϊԭ���ĸ�����Ϊsplay(k)��ǰkΪ������ģ���Ϊaccess�����£�����˵��ǰsplay������������ҪΪʹkΪԭ���ĸ�Ҫ��֤k���*С������Ҫ������ʵ�ַ�ת*/
        access(k);splay(k);
        tr[k].tag^=1;return;
    }
    inline int findroot(int k){/*����k���ĸ���ͨ����k��ԭ����ͨһֱѰ�������С��*/
        access(k),splay(k);
        int son;
        while(1){
            pushdown(k);
            if(tr[k].ch[0]) k=tr[k].ch[0];
            else break;
        }
		return k;
    }
    inline void split(int x,int y){/*��ͨһ��x->y��·��*/
        makeroot(x);
        access(y);splay(y);
    }
    inline void link(int x,int y){/*����x,y ��xΪ������һ�����*/
        makeroot(x);
        if(findroot(y)!=x) tr[x].f=y;
        return;
    }
    inline void cut(int x,int y){/*�ж�x,y�ı� ��x,y����һ��splay�ϣ�Ȼ��ͽ����жϼ���*/
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
