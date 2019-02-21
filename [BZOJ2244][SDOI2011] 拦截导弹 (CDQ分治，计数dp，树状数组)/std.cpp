#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define int long long
#define pi pair<int,double>
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int MAXN=50001;
int q0[MAXN];
struct node{
    int a,b,id;
}k[MAXN],tmp[MAXN],K[MAXN];
int n,f1[MAXN],f2[MAXN];
double Num1[MAXN],Num2[MAXN];
int t1[MAXN],t2[MAXN];
double s[MAXN];
struct Segment_Tree{
    int Maxn[MAXN<<2];
    double Cnt[MAXN<<2];
    void update(int k,int l,int r,int x,int y,int val,double cnt){
        if(l==r){
            if(Maxn[k]==val) Cnt[k]+=cnt;
            else if(Maxn[k]<val) Maxn[k]=val,Cnt[k]=cnt;
            return;
        }
        int mid=l+r>>1;
        if(x<=mid) update(k<<1,l,mid,x,y,val,cnt);
        if(mid<y) update(k<<1|1,mid+1,r,x,y,val,cnt);
        if(Maxn[k<<1]!=Maxn[k<<1|1]){
            if(Maxn[k<<1]<Maxn[k<<1|1]) Maxn[k]=Maxn[k<<1|1],Cnt[k]=Cnt[k<<1|1];
            else Maxn[k]=Maxn[k<<1],Cnt[k]=Cnt[k<<1];
        }else Maxn[k]=Maxn[k<<1],Cnt[k]=Cnt[k<<1]+Cnt[k<<1|1];
        return;
    }
    int qmax(int k,int l,int r,int x,int y){
        if(x<=l&&r<=y) return Maxn[k];
        int mid=l+r>>1,res=0;
        if(x<=mid) res=max(res,qmax(k<<1,l,mid,x,y));
        if(mid<y) res=max(res,qmax(k<<1|1,mid+1,r,x,y));
        return res;
    }
    pi qcnt(int k,int l,int r,int x,int y){
        if(x<=l&&r<=y) return make_pair(Maxn[k],Cnt[k]);
        int mid=l+r>>1;
        if(x<=mid){
            pi f1=qcnt(k<<1,l,mid,x,y);
            if(mid<y){
                pi f2=qcnt(k<<1|1,mid+1,r,x,y);
                if(f1.first==f2.first) return make_pair(f1.first,f1.second+f2.second);
                else{
                    if(f1.first<f2.first) return f2;
                    return f1;
                }
            }return f1;
        }
        if(mid<y) return qcnt(k<<1|1,mid+1,r,x,y);
    }
    void reset(int k,int l,int r,int x,int y){
        Maxn[k]=Cnt[k]=0;
        if(l==r) return;
        int mid=l+r>>1;
        if(x<=mid) reset(k<<1,l,mid,x,y);
        if(mid<y) reset(k<<1|1,mid+1,r,x,y);
        return; 
    }
    void Update(int x,int val,double cnt){q0[++q0[0]]=x;update(1,1,n,x,x,val,cnt);return;}
    int Qmax(int x,int y){return qmax(1,1,n,x,y);}
    double Qcnt(int x,int y){return qcnt(1,1,n,x,y).second;}
    void clear(){
        for(int i=1;i<=q0[0];i++) reset(1,1,n,q0[i],q0[i]);
        return; 
    }
    void debug(int k,int l,int r){
        printf("%d %d\n",Maxn[k],Cnt[k]);
        if(l==r) return;
        int mid=l+r>>1;
        debug(k<<1,l,mid),debug(k<<1|1,mid+1,r);
        return;
    }
}segment;
bool cmpid(node x1,node x2){return x1.id<x2.id;}
bool cmpa1(node x1,node x2){
    if(x1.a==x2.a) return x1.id<x2.id;
    return x1.a>x2.a;
} 
bool cmpa2(node x1,node x2){
    if(x1.a==x2.a) return x1.id<x2.id;
    return x1.a<x2.a;
}
void cdq1(int l,int r){
    if(l==r) return;
    sort(k+l,k+r+1,cmpid);
    int mid=l+r>>1;
    cdq1(l,mid); 
    q0[0]=0;
    sort(k+l,k+mid+1,cmpa1);
    sort(k+mid+1,k+r+1,cmpa1);
    int p=l,q=mid+1;
    while(p<=mid&&q<=r){
        if(k[p].a>=k[q].a){
            segment.Update(k[p].b,f1[k[p].id],Num1[k[p].id]);
            p++;
        }else{
            int Maxn_=segment.Qmax(k[q].b,n)+1;
            double Num_=segment.Qcnt(k[q].b,n);
            if(f1[k[q].id]==Maxn_) Num1[k[q].id]+=Num_;
            else if(Maxn_>f1[k[q].id]) f1[k[q].id]=Maxn_,Num1[k[q].id]=Num_; 
            q++;
        }
    }
    while(p<=mid){
        segment.Update(k[p].b,f1[k[p].id],Num1[k[p].id]);
        p++;
    }
    while(q<=r){
        int Maxn_=segment.Qmax(k[q].b,n)+1;
        double Num_=segment.Qcnt(k[q].b,n);
        if(f1[k[q].id]==Maxn_) Num1[k[q].id]+=Num_;
        else if(Maxn_>f1[k[q].id]) f1[k[q].id]=Maxn_,Num1[k[q].id]=Num_; 
        q++;
    }
    segment.clear();
    cdq1(mid+1,r);
    return; 
}
void cdq2(int l,int r){
    if(l==r) return;
    sort(k+l,k+r+1,cmpid);
    int mid=l+r>>1;
    cdq2(l,mid);
    sort(k+l,k+mid+1,cmpa2);
    sort(k+mid+1,k+r+1,cmpa2);q0[0]=0;
    int p=l,q=mid+1;
    while(p<=mid&&q<=r){
        if(k[p].a<=k[q].a){
            segment.Update(k[p].b,f2[k[p].id],Num2[k[p].id]);
            p++; 
        }else{
            int Maxn_=segment.Qmax(1,k[q].b)+1;
            double Num_=segment.Qcnt(1,k[q].b);
            if(f2[k[q].id]==Maxn_) Num2[k[q].id]+=Num_;
            else if(Maxn_>f2[k[q].id]) f2[k[q].id]=Maxn_,Num2[k[q].id]=Num_; 
            q++;
        }
    }
    while(p<=mid){
        segment.Update(k[p].b,f2[k[p].id],Num2[k[p].id]);
        p++; 
    }
    while(q<=r){
        int Maxn_=segment.Qmax(1,k[q].b)+1;
        double Num_=segment.Qcnt(1,k[q].b);
        if(f2[k[q].id]==Maxn_) Num2[k[q].id]+=Num_;
        else if(Maxn_>f2[k[q].id]) f2[k[q].id]=Maxn_,Num2[k[q].id]=Num_; 
        q++;
    }
    segment.clear();
    cdq2(mid+1,r);
    return;
}
signed main(){
    //freopen("1.in","r",stdin);
    //freopen("4.out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++) t1[i]=k[i].a=read(),t2[i]=k[i].b=read(),k[i].id=i;
    sort(t1+1,t1+n+1),sort(t2+1,t2+n+1);
    for(int i=1;i<=n;i++) k[i].a=lower_bound(t1+1,t1+n+1,k[i].a)-t1,k[i].b=lower_bound(t2+1,t2+n+1,k[i].b)-t2;
    for(int i=1;i<=n;i++) K[i]=k[i];
    for(int i=1;i<=n;i++) f1[i]=Num1[i]=1;
    cdq1(1,n);
    for(int i=1;i<=n;i++) k[i]=K[n-i+1],k[i].id=i,f2[i]=Num2[i]=1;
    //for(int i=1;i<=n;i++) printf("%d %d\n",k[i].a,k[i].b);
    //system("pause");
    cdq2(1,n);
    for(int i=1;i<=n;i++) s[i]=f2[i];
    for(int i=1;i<=n;i++) f2[i]=s[n-i+1];
    for(int i=1;i<=n;i++) s[i]=Num2[i];
    for(int i=1;i<=n;i++) Num2[i]=s[n-i+1];
    int Ans=0;
    for(int i=1;i<=n;i++) Ans=max(Ans,f1[i]+f2[i]-1);
    printf("%d\n",Ans);
    double all=0;
    for(int i=1;i<=n;i++) if(f1[i]==Ans) all+=Num1[i];
    for(int i=1;i<=n;i++){
        if(f1[i]+f2[i]-1==Ans) printf("%.5lf ",(double)(Num1[i]*Num2[i])/all);
        else printf("%.5lf ",0.0);
    }return 0;
}/*
4
1 4
2 2
3 3
1 2
*/
