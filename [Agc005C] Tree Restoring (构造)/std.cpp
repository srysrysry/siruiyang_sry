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
const int N=101;
int n,a[N],Num[N],maxn=INT_MIN,minn=INT_MAX;
int main(){
    n=read();
    for(int i=1;i<=n;i++) a[i]=read(),maxn=max(maxn,a[i]),minn=min(minn,a[i]);
    if(maxn>n||minn<1){printf("Impossible");return 0;}
    if((maxn+1)/2!=minn){printf("Impossible");return 0;}
    for(int i=1;i<=n;i++) Num[a[i]]++;
    if(Num[maxn]==1){printf("Impossible");return 0;}
    if(Num[minn]!=(maxn%2)+1){printf("Impossible");return 0;}
    for(int i=minn+1;i<=maxn;i++)
         if(!Num[i]||Num[i]==1){printf("Impossible");return 0;}
    printf("Possible");
}

