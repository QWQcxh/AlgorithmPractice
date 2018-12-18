#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
using namespace std;
#define MAXM 500010
#define MAXN 50010
struct edge{
    int u,v,w;
}e[MAXM];
int first[MAXN],nxt[MAXM],en=1;
void adde(int u,int v,int w){
    nxt[en]=first[u];
    e[en].u=u;e[en].v=v;e[en].w=w;
    first[u]=en++;
}

int dist[MAXN],inq[MAXN];
int ub=-1;//upper bound
bool spfa(int src){
    memset(dist,0x7f,sizeof(dist));
    memset(inq,0,sizeof(inq));
    queue<int> q;
    q.push(src);inq[src]=1;dist[src]=0;
    while(!q.empty()){
        int v=q.front();q.pop();
//        if(cnt[v]>ub) return false;
        inq[v]=0;
        for(int i=first[v];i;i=nxt[i]){
            if(dist[e[i].v]>dist[v]+e[i].w){
                dist[e[i].v]=dist[v]+e[i].w;
                if(!inq[e[i].v]){
                    inq[e[i].v]=1;
                    q.push(e[i].v);
//                    cnt[e[i].v]++;
                }
            }
        }
    }
    return true;
}
int main()
{
    //debug
    //freopen("C:\\Users\\marlin\\Desktop\\input.txt","r",stdin);
    int n;cin>>n;
    while(n--){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        ub=max(ub,b);//get upper bound of intervals
        // d[b]-d[a-1]>=c
        adde(b+1,a,-c);
    }
    //  0<=d[i]-d[i-1]<=1
    ub++;//right shift
    for(int i=1;i<=ub+1;i++){
        adde(i-1,i,1);
        adde(i,i-1,0);
    }
    spfa(ub);
    cout<<-dist[0]<<endl;
    return 0;
}
