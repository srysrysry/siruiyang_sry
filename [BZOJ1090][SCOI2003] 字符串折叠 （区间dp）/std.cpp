#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int MAXN=111;
int f[MAXN][MAXN],len;
char str[MAXN],str1[MAXN],str2[MAXN];
bool access(int l1,int r1,int l2,int r2){
    if(r1-l1>r2-l2) return 0;
    if((r2-l2+1)%(r1-l1+1)!=0) return 0;
    if((r2-l1+1)%(r1-l1+1)!=0) return 0;
    int len1=r1-l1+1,len2=r2-l2+1;
    for(int i=1;i<=len1;i++) str1[i]=str[l1+i-1];
    for(int i=1;i<=len2;i++) str2[i]=str[l2+i-1];
    int l=1;
    for(int i=1;i<=len2;i++){
        if(str2[i]!=str1[l]) return 0;
        ++l;
        if(l>len1) l=1;
    }return 1;
}
int main(){
    //freopen("6.in","r",stdin);
    memset(f,127/3,sizeof(f));
    scanf("%s",str+1),len=strlen(str+1);
    for(int i=1;i<=len;i++) f[i][i]=1;
    for(int l=1;l<len;l++){
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            for(int k=i;k<j;k++){
                f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
                if(access(i,k,k+1,j)){
                    int all=(j-i+1)/(k-i+1);
                    if(all<10) f[i][j]=min(f[i][j],f[i][k]+3);
                    else if(all<100)f[i][j]=min(f[i][j],f[i][k]+4);
                    else f[i][j]=min(f[i][j],f[i][k]+5);
                }
            }
        }
    }printf("%d\n",f[1][len]);
} 
