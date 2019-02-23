#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'|c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int N=301;
const int Maxn=100001;
int n,a[N],sum,ans,f[Maxn];
bool cmp(int x1,int x2){return x1>x2;}
int main(){
    n=read();
    for(int i=1;i<=n;i++) a[i]=read(),sum+=a[i];
    sort(a+1,a+n+1,cmp);
    f[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=(sum/2)+a[i];j>=a[i];j--){
            f[j]|=f[j-a[i]];
            if(f[j]) ans=max(ans,j);
        }
    }printf("%d\n",ans);
}
