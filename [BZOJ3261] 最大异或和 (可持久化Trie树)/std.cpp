#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9'){ans=(ans<<3)+(ans<<1)+c-'0';c=getchar();}
    return ans*f;
}
const int N=600001;
int n,m,v[N],s[N],last[N*24],ch[N*24][2],tr[N],num;
struct Trie{
    inline void insert(int las,int k,int val,int pos,int i){
        if(pos==-1){
            last[k]=i;
            return;
        }
        int s=(val>>pos)&1;
        ch[k][s^1]=ch[las][s^1];
        ch[k][s]=++num;
        insert(ch[las][s],ch[k][s],val,pos-1,i);
        last[k]=max(last[ch[k][0]],last[ch[k][1]]);
    }
    inline int ask(int pos,int k,int val,int l){
        if(pos==-1) return s[last[k]]^val;
        int c=(val>>pos)&1;
        if(last[ch[k][c^1]]>=l) return ask(pos-1,ch[k][c^1],val,l);
        return ask(pos-1,ch[k][c],val,l);
    }
}trie;
char str[2]; 
int main(){
//	freopen("19.in","r",stdin);
    n=read(),m=read();
    tr[0]=++num;
    trie.insert(0,tr[0],0,24,0);last[0]=-1;
    for(int i=1;i<=n;i++){
        v[i]=read();
        s[i]=s[i-1]^v[i];
        tr[i]=++num;
        trie.insert(tr[i-1],tr[i],s[i],24,i);
    }
    for(int i=1;i<=m;i++){
        scanf("%s",str);
        if(str[0]=='A'){
            v[++n]=read();
            s[n]=s[n-1]^v[n];tr[n]=++num;
            trie.insert(tr[n-1],tr[n],s[n],24,n);
        }else{
            int l=read(),r=read(),x=read();
            printf("%d\n",trie.ask(24,tr[r-1],s[n]^x,l-1));
        }
    }
}

