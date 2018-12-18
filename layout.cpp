#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
#define MAXN 1010
#define MAXM 25000
#define INF 0x7f7f7f7f
struct edge{
    int u,v,w;
}e[MAXM];
int first[MAXN],nxt[MAXM],en=1;
void adde(int u,int v,int w){
    nxt[en]=first[u];
    e[en].u=u;e[en].v=v;e[en].w=w;
    first[u]=en++;
}

int dist[MAXN],inq[MAXN],cnt[MAXN];
bool spfa(int src){
    memset(dist,0x7f,sizeof(dist));
    memset(inq,0,sizeof(inq));
    memset(cnt,0,sizeof(cnt));
    queue<int> q;
    q.push(src);dist[src]=0;inq[src]=1;cnt[src]++;
    while(!q.empty()){
        int v=q.front();q.pop();
        if(cnt[v]>MAXN) return false;
        inq[v]=0;
        for(int i=first[v];i;i=nxt[i]){
            if(dist[e[i].v]>dist[v]+e[i].w){
                dist[e[i].v]=dist[v]+e[i].w;
                if(!inq[e[i].v]){
                    cnt[e[i].v]++;
                    inq[e[i].v]=1;
                    q.push(e[i].v);
                }
            }
        }
    }
    return true;
}
int main()
{
   // freopen("C:\\Users\\marlin\\Desktop\\input.txt","r",stdin);
    int n,ml,md;cin>>n>>ml>>md;
    int a,b,d;
    while(ml--){
        scanf("%d%d%d",&a,&b,&d);
        adde(a,b,d);
    }
    while(md--){
        scanf("%d%d%d",&a,&b,&d);
        adde(b,a,-d);
    }
    for(int i=1;i<=n-1;i++)
        adde(i+1,i,0);
    if(spfa(1)){
        if(dist[n]==INF) cout<<-2<<endl;
        else cout<<dist[n]<<endl;
    }
    else cout<<-1<<endl;
}
