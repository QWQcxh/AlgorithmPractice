#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
#define LL long long
map<LL,LL>pre,r;
LL findfa(LL s){
    if(pre.count(s)==0){
        pre[s]=s;r[s]=0;
        return s;
    }
    else if(pre[s]==s) return s;
    int fa=pre[s];
    pre[s]=findfa(fa);
    r[s]=(r[fa]+r[s])%2;
    return pre[s];
}
int main()
{
    LL n;cin>>n>>n;
    int ans=0;
    for(int i=0;i<n;i++){
        LL x,y,w;char s[20];
        scanf("%lld%lld%s",&x,&y,s);
        x--;w=s[0]=='e'?0:1;
        LL rx=findfa(x);
        LL ry=findfa(y);
        if(rx==ry){
            if((r[y]-r[x]+2)%2!=w) break;
        }
        else {
            pre[ry]=rx;r[ry]=(2-r[y]+w+r[x])%2;
        }
        ans++;
    }
    cout<<ans<<endl;
    return 0;
}
