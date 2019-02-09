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
complex f[MAXN],g[MAXN],f1[MAXN];
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
double q[MAXN];
int main(){
//	freopen("13.in","r",stdin);
	n=read();
	for(int i=1;i<=n;i++) scanf("%lf",&q[i]);
	for(int i=1;i<=n;i++) f[i].x=q[i],g[i].x=(double)1/(double)i/(double)i;
	for(int i=0;i<=n;i++) f1[i]=f[n-i];
	int m=2*n;
	for(n=1;n<=m;n<<=1);	
	for(int i=0;i<=n;i++) flip[i]=((flip[i>>1]>>1)|(i&1?n>>1:0));
	fft(f,1),fft(g,1),fft(f1,1);
	for(int i=0;i<=n;i++) f[i]=f[i]*g[i],f1[i]=f1[i]*g[i];
	fft(f,-1),fft(f1,-1);
	for(int i=0;i<=n;i++) f[i].x=f[i].x/n,f1[i].x=f1[i].x/n;
	for(int i=1;i<=m/2;i++) printf("%.3lf\n",f[i].x-f1[(m/2)-i].x);
	return 0; 
}
