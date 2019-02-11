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
int ask1(int x){
	printf("? %d\n",x);fflush(stdout);
	int opt=read();
	return opt;
}
int ask2(int x){
	printf("> %d\n",x);fflush(stdout);
	int num=read();
	return num; 
}
int qmax(){
	int l=0,r=1000000000,maxn=-INT_MAX;
	while(l<=r){
		int mid=(l+r)>>1;
		if(ask2(mid))maxn=max(maxn,mid),l=mid+1;
		else r=mid-1;
	}return maxn+1;
}int n,d,a[301];
int gcd(int a,int b){
	if(b==0) return a;
	return gcd(b,a%b);
}int maxn;
signed main(){
	n=read();
	maxn=qmax();
	for(int i=1;i<=30;i++){
		int s=(rand()*rand())%n+1;
		a[++a[0]]=ask1(s);
	}sort(a+1,a+31);
	d=maxn-a[1];
	for(int i=1;i<=29;i++) d=gcd(d,a[i+1]-a[1]);
	printf("! %d %d\n",maxn-d*(n-1),d);fflush(stdout);
	return 0;
}
