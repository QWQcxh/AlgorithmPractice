#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define INF 2147483647
#define MAXM 151000
#define MAXN 31000
using namespace std;
struct node{
    int id;
    int len;//len is weight or path length
    node(int id=0,int len=0):id(id),len(len){}
};
int dist[MAXN],vis[MAXN],u[MAXM],v[MAXM],w[MAXM],first[MAXN],nxt[MAXM];
int n,m;//node num,and edge num

bool operator<(const node&n1,const node &n2){
    return n1.len>n2.len;
}
int dijkstra(int s,int t){
    priority_queue<node> pq;
    for(int i=0;i<n+3;i++) vis[i]=0;
    for(int i=0;i<n+3;i++) dist[i]=INF;
    pq.push(node(s,0));
    for(int i=1;i<n;i++)
        pq.push(node(i,INF));
    while(!pq.empty()){
        node nod=pq.top();
        pq.pop();
        if(vis[nod.id]) continue;
        else if(nod.id==t) return nod.len;
        int vnum=nod.id;
        dist[vnum]=nod.len;
        vis[vnum]=1;
        for(int e=first[vnum];e;e=nxt[e])//update
            if(dist[v[e]]>dist[vnum]+w[e]){
                dist[v[e]]=dist[vnum]+w[e];
                pq.push(node(v[e],dist[v[e]]));
            }
    }
    return 0;
}
int main()
{
   //freopen("C:\\Users\\marlin\\Desktop\\output.txt","r",stdin);
    scanf("%d%d",&n,&m);
    int e=1;
    while(m--){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        nxt[e]=first[a];u[e]=a;v[e]=b;w[e]=c;first[a]=e++;
    }
    cout<<dijkstra(1,n)<<endl;
    return 0;
}

