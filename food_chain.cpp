#include <iostream>
#include <cstdio>
using namespace std;
#define MAXN 50010
int pre[MAXN],r[MAXN];
int findfa(int s){
    int fa=pre[s];
    if(pre[s]==s) return s;
    pre[s]=findfa(pre[s]);
    r[s]=(r[fa]+r[s])%3;
    return pre[s];
}
int main()
{
    //freopen("C:\\Users\\marlin\\Desktop\\input.txt","r",stdin);//debug
    for(int i=0;i<MAXN;i++){
        pre[i]=i;r[i]=0;
    }
    int n,k;cin>>n>>k;
    int ans=0;
    while(k--){
        int rs,x,y;
       // ans=0;
        scanf("%d%d%d",&rs,&x,&y);
        rs--;//adapt to 0 1 2
        int rx=findfa(x);
        int ry=findfa(y);
        if(x>n||y>n||(x==y&&rs==1))
            ans++;
        else if(rx==ry&&(r[x]-r[y]+3)%3!=rs)
            ans++;
        else if(rx!=ry){
            pre[rx]=ry;
            r[rx]=(rs-r[x]+r[y]+3)%3;
        }
    }
    cout<<ans<<endl;
    return 0;
}
