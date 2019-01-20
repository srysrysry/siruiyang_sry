#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define mod 200503
#define int long long
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int MAXN=600001; 
const int N=14;
struct node{
    int u,v,nex;
}x[MAXN];
int bit[N],mi,mj,n,m,ans,pre=1,tot[3],state[3][MAXN],w[3][MAXN],dp[3][MAXN],now,cnt,head[MAXN],M[N][N],endi,endj;
char str[MAXN];
void init(){memset(head,-1,sizeof(head)),cnt=0;return;}
void add(int u,int v){
    x[cnt].u=u,x[cnt].v=v,x[cnt].nex=head[u],head[u]=cnt++;
}
void hash(int sta,int val){
    int u=sta%mod;
    for(int i=head[u];i!=-1;i=x[i].nex){
        if(state[now][x[i].v]==sta){
            dp[now][x[i].v]+=val;
            return;
        }
    }
    tot[now]++;state[now][tot[now]]=sta;
    add(u,tot[now]);dp[now][tot[now]]=val;
    return;
}
signed main(){
    memset(head,-1,sizeof(head));
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        	scanf("%s",str+1);
        	int len=strlen(str+1);
        	for(int k=1;k<=len;k++)
        		if(str[k]=='.') M[i][k]=1,endi=i,endj=k;
        }
    for(int i=1;i<=m;i++) bit[i]=i<<1;
    tot[now]=1,state[now][1]=0,dp[now][1]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=tot[now];j++) state[now][j]<<=2;
        for(int j=1;j<=m;j++){
            init();
            mi=i,mj=j; 
            swap(pre,now);
            tot[now]=0;
            for(int k=1;k<=tot[pre];k++){
                int sta=state[pre][k],val=dp[pre][k];
                int is_d=(sta>>bit[j])%4,is_r=(sta>>bit[j-1])%4;

                if(!M[i][j]){
                    if(!is_d&&!is_r) hash(sta,val);
                    continue;
                }
                if(!is_d&&!is_r){
                    if(M[i+1][j]&&M[i][j+1]) hash(sta+(1<<bit[j-1])+2*(1<<bit[j]),val);
                }
                if(is_d&&!is_r){
                    if(M[i][j+1]) hash(sta,val);
                    if(M[i+1][j]) hash(sta-is_d*(1<<bit[j])+is_d*(1<<bit[j-1]),val);
                }
                if(!is_d&&is_r){
                    if(M[i+1][j]) hash(sta,val);
                    if(M[i][j+1]) hash(sta-is_r*(1<<bit[j-1])+is_r*(1<<bit[j]),val);
                }
                if(is_d==1&&is_r==1){
                    int count=1;
                    for(int r=j+1;r<=m;r++){
                        if((sta>>bit[r])%4==1) count++;
                        if((sta>>bit[r])%4==2) count--;
                        if(!count){
                            hash(sta-(1<<bit[j])-(1<<bit[j-1])-(1<<bit[r]),val);
                            break;
                        }
                    }
                };
                if(is_d==2&&is_r==2){
                    int count=1;
                    for(int l=j-2;l>=1;l--){
                        if((sta>>bit[l])%4==1) count--;
                        if((sta>>bit[l])%4==2) count++;
                        if(!count){
                            hash(sta-2*(1<<bit[j])-2*(1<<bit[j-1])+(1<<bit[l]),val);
                            break;
                        }
                    }
                }
                if(is_d==1&&is_r==2)
                    hash(sta-2*(1<<bit[j-1])-(1<<bit[j]),val);
                if(is_d==2&&is_r==1)
                    if(i==endi&&j==endj) ans+=val;
            }
        }
    }
    printf("%lld\n",ans);
}
