#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
#define MAXN 2000
struct edge{
    int u,v;
}e[MAXN];
int first[MAXN],nxt[MAXN],en;
void init_e(){
    memset(e,0,sizeof(e));
    memset(first,0,sizeof(first));
    memset(nxt,0,sizeof(nxt));
    en=1;
}
void adde(int u,int v){
    nxt[en]=first[u];
    e[en].u=u;e[en].v=v;
    first[u]=en++;
}

struct point{
    int depth,id;
}p[2*MAXN];
int t[MAXN],cni;//每个点的时间戳
void init_p(){
    memset(p,0,sizeof(p));
    memset(t,0,sizeof(t));
    cni=0;
}
void DFS(int s,int dep){
    p[cni].depth=dep;p[cni].id=s;
    t[s]=cni++;
    for(int i=first[s];i;i=nxt[i]){
        DFS(e[i].v,dep+1);
        p[cni].depth=dep;p[cni++].id=s;
    }
}

struct RMQ{
    point*a;
    int len;//interval length
    int dp[MAXN][20];
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
    RMQ(point *a,int len):a(a),len(len){init();}
};

int lca(RMQ &rmq,int u,int v){
    return p[rmq.rm(min(t[u],t[v]),max(t[u],t[v]))].id;
}
int ans[MAXN],root[MAXN];
int main()
{
   //freopen("C:\\Users\\marlin\\Desktop\\input.txt","r",stdin);
    int n,m;
    while(cin>>n){
        memset(ans,0,sizeof(ans));
        memset(root,0,sizeof(root));
        init_e();
        for(int i=0;i<n;i++){
            int u,t,v;scanf("%d : ( %d )",&u,&t);
            while(t--) {scanf("%d",&v);adde(u,v);root[v]=1;}
        }
        int rn=n;
        for(int i=1;i<=n;i++) if(!root[i]) {rn=i;break;}
        //debug
//        cout<<"root is "<<rn<<endl;
        init_p();
        DFS(rn,0);
        //debug
//        for(int i=1;i<cni;i++) cout<<"p.d is: "<<p[i].depth<<" p.id is: "<<p[i].id<<endl;
//        for(int i=1;i<n;i++) cout<<"t["<<i<<"] is: "<<t[i]<<endl;
        RMQ rmq(p,cni);
        scanf("%d",&m);
        for(int i=0;i<m;i++){
            int x,y;scanf(" ( %d %d ) ",&x,&y);
            ans[lca(rmq,x,y)]++;
        }
        for(int i=1;i<=n;i++) if(ans[i]) printf("%d:%d\n",i,ans[i]);
    }
    return 0;
}
