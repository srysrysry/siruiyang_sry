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
const int MAXN=201;
int f[MAXN][MAXN][5],M[5][5][5],l1,l2,l3,l4;
bool d;
int get(char s){
    if(s=='W') return 1;
    if(s=='I') return 2;
    if(s=='N') return 3;
    if(s=='G') return 4;
} 
void print(int opt){
    if(opt==1) printf("W");
    if(opt==2) printf("I");
    if(opt==3) printf("N");
    if(opt==4) printf("G");
    d=1;
    return;
}
char str[210];
void init(){
    l1=read(),l2=read(),l3=read(),l4=read();
    #define getf get
    for(int i=1;i<=l1;i++){
        scanf("%s",str+1);
        int s1=getf(str[1]),s2=getf(str[2]);
        M[s1][s2][1]=1;
    }
    for(int i=1;i<=l2;i++){
        scanf("%s",str+1);
        int s1=getf(str[1]),s2=getf(str[2]);
        M[s1][s2][2]=1;
    }
    for(int i=1;i<=l3;i++){
        scanf("%s",str+1);
        int s1=getf(str[1]),s2=getf(str[2]);
        M[s1][s2][3]=1;
    }
    for(int i=1;i<=l4;i++){
        scanf("%s",str+1);
        int s1=getf(str[1]),s2=getf(str[2]);
        M[s1][s2][4]=1;
    }scanf("%s",str+1);
}
int main(){
    init();
    int len=strlen(str+1);
    for(int i=1;i<=len;i++) f[i][i][getf(str[i])]=1;
    for(int l=1;l<len;l++){
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            for(int k=i;k<j;k++)
                for(int f1=1;f1<=4;f1++){
                    if(!f[i][k][f1]) continue;
                    for(int f2=1;f2<=4;f2++){
                        if(!f[k+1][j][f2]) continue;
                        for(int f3=1;f3<=4;f3++){
                            if(M[f1][f2][f3]) f[i][j][f3]=1;
                        }
                    }
                }
        }
    }
    for(int i=1;i<=4;i++){
        if(f[1][len][i]) print(i);
    }
    if(!d){printf("The name is wrong!");return 0;}
    return 0;
}
