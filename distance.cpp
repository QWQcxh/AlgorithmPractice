#include <iostream>
#include <cstdio>
#include <cmath>
#define MAXN 50010
using namespace std;

struct edge{
    int u,v,w;
}e[MAXN*2];
int first[MAXN],nxt[MAXN*2],en=1;
void adde(int u,int v,int w){
    nxt[en]=first[u];
    e[en].u=u;e[en].v=v;e[en].w=w;
    first[u]=en++;
}

int vis[MAXN],dist[MAXN],cni=0,t[MAXN];
struct path{
    int id,depth;
}p[MAXN*2];
void DFS(int s,int depth){
    vis[s]=1;
    p[cni].id=s;p[cni].depth=depth;
    t[s]=cni++;
    for(int i=first[s];i;i=nxt[i]){
        if(vis[e[i].v]) continue;
        dist[e[i].v]=dist[s]+e[i].w;
        DFS(e[i].v,depth+1);
        p[cni].id=s;p[cni++].depth=depth;
    }
}
int dp[MAXN*2][20];
struct RMQ{
    path *a;
    int len;
    void init(){
        for(int i=0;i<len;i++) dp[i][0]=i;
        for(int b=1;(1<<b)<len;b++)
            for(int i=0;i+(1<<b)-1<len;i++)
                dp[i][b]=a[dp[i][b-1]].depth<a[dp[i+(1<<(b-1))][b-1]].depth?
                dp[i][b-1]:dp[i+(1<<(b-1))][b-1];
    }
    int rm(int l,int r){
        int k=(int)(log((double)r-l+1)/log(2.0));
        return a[dp[l][k]].depth<a[dp[r-(1<<k)+1][k]].depth?
        dp[l][k]:dp[r-(1<<k)+1][k];
    }
    RMQ(path *a,int len):a(a),len(len){init();}
};
int lca(RMQ &rmq,int x,int y){
    return p[rmq.rm(min(t[x],t[y]),max(t[x],t[y]))].id;
}
int main()
{
   // freopen("C:\\Users\\marlin\\Desktop\\text.txt","r",stdin);
   // freopen("C:\\Users\\marlin\\Desktop\\myout.txt","w",stdout);
    int n,m;scanf("%d%d",&n,&m);
    while(m--){
        int u,v,w;char s[3];
        scanf("%d%d%d%s",&u,&v,&w,s);
        adde(u,v,w);adde(v,u,w);
    }
    DFS(1,0);
    //debug
//    for(int i=0;i<cni;i++) cout<<"p.d["<<i<<"]= "<<p[i].depth<<" and p.id["<<i<<"]= "<<p[i].id<<endl;
//    for(int i=1;i<=n;i++) cout<<"t["<<i<<"] = "<<t[i]<<endl;
    RMQ rmq(p,cni);
    int qn;scanf("%d",&qn);
    while(qn--){
        int a,b,anc;scanf("%d%d",&a,&b);
        anc=lca(rmq,a,b);
        printf("%d\n",dist[a]+dist[b]-2*dist[anc]);
    }
    return 0;
}
