#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<bitset>
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'|c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int N=1001;
bitset<2000000> bit;
int n,sum,ans;
int main(){
    n=read();
    bit[0]=1;
    for(int i=1;i<=n;i++){
        int x;
        scanf("%d",&x);
        sum+=x;
        bit^=(bit<<x);
    }
    for(int i=1;i<=sum;i++) if(bit[i])ans^=i;
    printf("%d\n",ans);
}
