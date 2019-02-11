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
const int N=2001;
int n,a[N],ans;
int main(){
    n=read();
    for(int i=1;i<=2*n;i++) a[i]=read();
    sort(a+1,a+2*n+1);
    for(int i=1;i<=2*n;i+=2) ans+=a[i];
    printf("%d\n",ans);
}

