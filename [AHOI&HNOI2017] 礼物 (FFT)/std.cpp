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
const int MAXN=400001;
const double pi=acos(-1);
struct complex{
    complex(double xx=0,double yy=0){x=xx,y=yy;}
    double x,y;
};
complex operator+(complex a,complex b){return complex(a.x+b.x,a.y+b.y);}
complex operator-(complex a,complex b){return complex(a.x-b.x,a.y-b.y);}
complex operator*(complex a,complex b){return complex(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
int n,m;
complex f[MAXN],g[MAXN];
int flip[MAXN];
void fft(complex *f,int opt){
    for(int i=0;i<n;i++) if(i<flip[i]){complex tmp;tmp=f[i];f[i]=f[flip[i]];f[flip[i]]=tmp;}
    for(int p=2;p<=n;p<<=1){
        int len=(p>>1);
        complex tmp=complex(cos(pi/len),opt*sin(pi/len));
        for(int be=0;be<n;be+=p){
            complex buf=complex(1,0);
            for(int l=be;l<be+len;l++){
                complex t=buf*f[len+l];
                f[len+l]=f[l]-t;f[l]=f[l]+t;
                buf=buf*tmp;
            }
        }
    }
}
complex A[MAXN],B[MAXN];
int ansA,ansB,ans;
complex B1[MAXN];
double eps=1e-2;
int main(){
//	freopen("gift1.in","r",stdin);
    n=read(),m=read();
    for(int i=1;i<=n;i++) A[i].x=(double)read(),ansA+=A[i].x*A[i].x;
    for(int i=1;i<=n;i++) B[i].x=(double)read(),ansB+=B[i].x*B[i].x;
    ans+=(ansA+ansB);
    ansA=0,ansB=0;
    for(int i=1;i<=n;i++) ansA+=A[i].x,ansB+=B[i].x;
    int a=n,b=2*(ansA-ansB);
    double mid=-b/(double)2/a;
    int Minn=INT_MAX,pos;
    for(int i=(int)mid-10;i<=(int)mid+10;i++){
        int ANS=a*i*i+b*i;
        if(ANS<Minn){Minn=ANS;pos=i;}
    }
    ans+=(a*pos*pos+b*pos);
    for(int i=1;i<=n;i++) A[i+n]=A[i];
    int S=n;
    m=n,n=2*n;
    for(int i=1;i<=n;i++) B1[i]=B[n-i+1];
    m+=n;
    for(n=1;n<=m;n<<=1);
    for(int i=0;i<=n;i++) flip[i]=((flip[i>>1]>>1)|(i&1?n>>1:0));
    fft(A,1),fft(B1,1);
    for(int i=0;i<=n;i++) A[i]=A[i]*B1[i];
    fft(A,-1);
    for(int i=0;i<=n;i++) A[i].x=A[i].x/n+eps;
    int maxn=0;
    for(int i=0;i<n;i++) maxn=max(maxn,(int)A[i].x);
    maxn*=2;
    ans-=maxn;
    printf("%d\n",ans);
}
