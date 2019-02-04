#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
using namespace std;
inline int read()
{
	int f=1,ans=0;char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}
int n,m; 
void print(){
	int opt=rand()%3+1;
	if(opt==1) printf("add");
	if(opt==2) printf("mul");
	if(opt==3) printf("cover");
}
const int MAXN=500001;
int a[MAXN];
pair<int,int> e[MAXN];
int main(){
//	freopen("41.in","w",stdout);
	srand(time(0));
	n=200000,m=200000;
	for(int i=1;i<=n;i++) a[i]=i;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++) printf("%d ",rand()%500001);printf("\n");
	for(int i=1;i<n;i++) printf("%d %d\n",i,i+1);
//    random_shuffle(a+1,a+n+1);
//    for(int i=2;i<=n;i++) e[i].first=a[i],e[i].second=a[rand()%(i-1)+1];
//    random_shuffle(e+2,e+n+1);
//    for(int i=2;i<=n;i++) 
//        if(rand()%2==0) cout<<e[i].first<<" "<<e[i].second<<endl;
//        else cout<<e[i].second<<" "<<e[i].first<<endl;
	for(int i=1;i<=m;i++){
		int opt=rand()%6+1;
		if(opt==1) printf("%d %d\n",opt,rand()%n+1);
		if(opt==2){
			printf("%d %d %d %d ",opt,rand()%n+1,rand()%n+1,rand()%50000+1);
			print();printf("\n");
		}
		if(opt==3){
			printf("%d %d %d ",opt,rand()%n+1,rand()%50000+1);
			print();printf("\n");
		}
		if(opt==4){
			printf("%d %d %d\n",opt,rand()%n+1,rand()%n+1);
		}
		if(opt==5){
			printf("%d %d\n",opt,rand()%n+1);
		}
		if(opt==6) printf("%d %d %d\n",opt,rand()%n+1,rand()%n+1); 
	}
}

