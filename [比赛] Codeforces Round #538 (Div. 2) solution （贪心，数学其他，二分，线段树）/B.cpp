#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define int long long
using namespace std;
inline int read(){
	int f=1,ans=0;char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}
const int N=200001;
int n,m,k;
struct node{
	int val,id;
}a[N];
bool cmp(node x1,node x2){return x1.val>x2.val;}
int s[N],ans;
signed main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++) a[i].val=read(),a[i].id=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=m*k;i++) s[++s[0]]=a[i].id,ans+=a[i].val;
	printf("%lld\n",ans);sort(s+1,s+s[0]+1);
	for(int i=1;i<k;i++) printf("%lld ",s[i*m]);
}
