#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<ctime>
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int N=21;
int n,m,a[N];
double T=20000,delta=0.999,eps=1e-14,x[N],ave;
double calc(){
    for(int i=1;i<=m;i++) x[i]=0;
    int minn;
    for(int i=1;i<=n;i++){
        minn=1;
        for(int j=1;j<=m;j++)
            if(x[j]<x[minn]) minn=j;
        x[minn]+=a[i];
    }
    double tmp=0;
    for(int i=1;i<=m;i++) tmp+=(x[i]-ave)*(x[i]-ave);
    return sqrt((double)tmp/m);
}
int times=5;
int main(){
//	freopen("1.in","r",stdin);
    srand(time(0));
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read(),ave+=(double)a[i];ave/=(double)m;
    
    double best=calc();double ans=calc();
    while(times--){
        T=20000;
        for(;T>eps;T*=delta){
        int xx,yy;
        while((xx=rand()%n+1)==(yy=rand()%n+1));
        swap(a[xx],a[yy]);
        double tmp=calc();
        if(tmp<best) best=tmp;
        if(tmp<ans||exp((double)(ans-tmp)/T)<rand()/RAND_MAX) ans=tmp;
        else swap(xx,yy);
    }
    }
    
    
    printf("%.2lf\n",best);
}
