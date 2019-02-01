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
const int N=200001;
int tr[N<<5],n,m,num,ls[N<<5],rs[N<<5],k,deep[N<<5],fa[N<<5];
struct segment_tree{
    inline void build(int &k,int l,int r){
        k=++num;
        if(l==r){deep[k]=1;fa[k]=l;return;}
        int mid=l+r>>1;
        build(ls[k],l,mid),build(rs[k],mid+1,r);
        return;
    }
    inline void update(int las,int &k,int l,int r,int x,int y,int fath){
        k=++num;ls[k]=ls[las],rs[k]=rs[las];
        if(l==r){fa[k]=fath;deep[k]=deep[las];return;}
        int mid=l+r>>1; 
        if(x<=mid) update(ls[las],ls[k],l,mid,x,y,fath);
        if(mid<y) update(rs[las],rs[k],mid+1,r,x,y,fath);
        return;
    }
    inline int qpos(int k,int l,int r,int x,int y){
        if(l==r) return k;
        int mid=l+r>>1;
        if(x<=mid) return qpos(ls[k],l,mid,x,y);
        if(mid<y) return qpos(rs[k],mid+1,r,x,y);
    }
    inline int find_father(int id,int x){
        int pos=qpos(tr[id],1,n,x,x);
        if(fa[pos]==x) return x;
        return find_father(id,fa[pos]);
    }
}segment;
int main(){
//	freopen("21.in","r",stdin);
    n=read(),m=read();
    segment.build(tr[0],1,n);
    for(int i=1;i<=m;i++){
        int opt=read();
        if(opt==1){
            tr[i]=tr[i-1];
            int x=read(),y=read();
            int t1=segment.find_father(i,x),t2=segment.find_father(i,y);
            if(t1==t2) continue;
            int posx=segment.qpos(tr[i],1,n,t1,t1),posy=segment.qpos(tr[i],1,n,t2,t2);
            if(deep[posx]<deep[posy]) swap(posx,posy),swap(t1,t2);
            segment.update(tr[i-1],tr[i],1,n,t2,t2,t1);
            if(deep[posx]==deep[posy]) deep[posx]++;
        }
        if(opt==2) tr[i]=tr[read()];
        if(opt==3){
            int x=read(),y=read();
            tr[i]=tr[i-1];
            int t1=segment.find_father(i,x);int t2=segment.find_father(i,y);
            if(t1==t2) printf("1\n");
            else printf("0\n");
        }
    }
}

