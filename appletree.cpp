#include <cstdio>
#include <iostream>
#include <cstring>
#define MAXN 300010
#define N 100010
using namespace std;
struct edge{
    int u,v;
}e[MAXN];
int first[MAXN],nxt[MAXN],en=1;
void adde(int u,int v){
    nxt[en]=first[u];
    e[en].u=u;e[en].v=v;
    first[u]=en++;
}
int lv[MAXN],rv[MAXN],vis[MAXN],cnt=1;
void DFS(int num){
    lv[num]=cnt++;vis[num]=1;
    for(int i=first[num];i;i=nxt[i]){
        if(!vis[e[i].v]) DFS(e[i].v);
    }
    rv[num]=cnt-1;
}

int c[MAXN],fork[MAXN];
inline int lowbit(int x) {return x&(-x);}
int sum(int x){
    int s=0;
    for(int i=x;i;i-=lowbit(i)){
        s+=c[i];
    }
    return s+x;
}
void update(int x,int i){
    int val=i-fork[x];
    fork[x]=i;
    for(int ind=x;ind<=N;ind+=lowbit(ind))
        c[ind]+=val;
}
int main()
{
   // freopen("C:\\Users\\marlin\\Desktop\\test.txt","r",stdin);
    for(int i=0;i<MAXN;i++)
        fork[i]=1;//initial
    int n,m;cin>>n;
    for(int i=1;i<n;i++){
        int a,b;scanf("%d%d",&a,&b);
        adde(a,b);adde(b,a);
    }
    DFS(1);
    cin>>m;
    for(int i=0;i<m;i++){
        char chr[3];int a;
        scanf("%s%d",chr,&a);
        if(chr[0]=='Q'){
            printf("%d\n",sum(rv[a])-sum(lv[a]-1));
        }
        else{ //change
            update(lv[a],1-fork[lv[a]]);
        }
    }
    return 0;
}

