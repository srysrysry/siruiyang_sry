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
const int N=1001;
struct node{
    int x,y,w;
}k[N];
int n;
double delta=0.997,eps=1e-14;
double calc(double x1,double y1){
    double ans=0;
    for(int i=1;i<=n;i++) ans+=sqrt(((double)k[i].x-x1)*((double)k[i].x-x1)+((double)k[i].y-y1)*((double)k[i].y-y1))*k[i].w;
    return ans;
}
double sx,sy;
double x,y,best,now,bx,by,T;
double Rand(){return T*(rand()*2-RAND_MAX);}
int main(){
    n=read();
    for(int i=1;i<=n;i++) k[i].x=read(),k[i].y=read(),k[i].w=read(),sx+=k[i].x,sy+=k[i].y;
    x=(double)sx/n,y=(double)sy/n;
    best=now=calc(x,y);bx=x,by=y;
    double xnow=bx,ynow=by;
    srand(19260817);
    for(T=100000;T>=eps;T*=delta){
        double x0,y0;
        x0=xnow+Rand(),y0=ynow+Rand();
        double val=calc(x0,y0);
        if(val<best) best=val,bx=x0,by=y0;
        if(val<now) now=val,xnow=x0,ynow=y0;
    }
    printf("%.3lf %.3lf\n",bx,by);
}
