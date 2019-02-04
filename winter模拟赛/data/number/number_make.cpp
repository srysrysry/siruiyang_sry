#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
using namespace std;
inline int read(){
	int f=1,ans=0;char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}
int n,opt;
int main(){
	freopen("20.in","w",stdout);
	srand(time(0));
	n=100000,opt=3;
	printf("%d %d\n" ,n,opt);
	for(int i=1;i<=n;i++) printf("%d ",rand()%500+500);printf("\n");
	for(int i=1;i<=n;i++) printf("%d ",rand()%500+500);printf("\n");
	return 0;
}

