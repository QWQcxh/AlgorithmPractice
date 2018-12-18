#include <iostream>
#include <queue>
#include <cstring>
#define MAXM 1000
#define MAXN 30
#define INF 2147483647
using namespace std;
int R[30],T[30];
struct edge{
    int u,v,w;
}e[MAXM];
int first[30],nxt[MAXM],en;
void adde(int u,int v,int w){
    nxt[en]=first[u];
    e[en].u=u;e[en].v=v;e[en].w=w;
    first[u]=en++;
}
void build(int num){
    en=1;
    memset(e,0,sizeof(e));
    memset(first,0,sizeof(first));
    memset(nxt,0,sizeof(nxt));
    //0<=d[i]-d[i-1]<=T[i]
    for(int i=1;i<=24;i++){
        adde(i-1,i,T[i]);
        adde(i,i-1,0);
    }
    // R[i]<=d[i]-d[i-8]<=num
    for(int i=8;i<=24;i++){
       // adde(i-8,i,num); can remove
        adde(i,i-8,-R[i]);
    }
    //0<=R[i-8+24]-R[i]<=num-R[i]
    for(int i=1;i<8;i++){
        adde(i,i+16,num-R[i]);
    }
    //d[24]-d[0]==num
    adde(0,24,num);//maybe
    adde(24,0,-num);
}
int dist[30],inq[30],cnt[30];
bool spfa(){
    queue<int> q;
    for(int i=0;i<=24;i++){
        dist[i]=INF;inq[i]=0;cnt[i]=0;
    }
    q.push(24);cnt[24]=1;inq[24]=1;dist[24]=0;
    while(!q.empty()){
        int v=q.front();q.pop();
        if(cnt[v]>24) return false;
        inq[v]=0;
        for(int i=first[v];i;i=nxt[i]){
            if(dist[e[i].v]>dist[v]+e[i].w){
                dist[e[i].v]=dist[v]+e[i].w;
                if(!inq[e[i].v]){
                    inq[e[i].v]=1;
                    q.push(e[i].v);
                    cnt[e[i].v]++;
                }
            }
        }
    }
    return true;
}
bool bsearch(int l,int r,int &res){
    res=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        build(mid);
        if(spfa()){
            res=mid;
            r=mid-1;
        } //没有负环
        else l=mid+1;
    }
    return res!=-1;
}
int main()
{
   // freopen("C:\\Users\\marlin\\Desktop\\input.txt","r",stdin);
//    freopen("C:\\Users\\marlin\\Desktop\\output.txt","w",stdout);
    int n,i,j;cin>>n;
    while(n--){
        memset(T,0,sizeof(T));
        for(i=1;i<=24;i++)
            cin>>R[i];
        int t;cin>>t;
        for(i=0;i<t;i++){
            cin>>j;T[j+1]++;
        }
        int res;
        if(bsearch(0,t,res)) cout<<res<<endl;
        else cout<<"No Solution\n";
    }
    return 0;
}
