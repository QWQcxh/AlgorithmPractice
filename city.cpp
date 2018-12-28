#include <cstdio>
#include <iostream>
#include <algorithm>
#define MAXN 40010
typedef long long ll;
using namespace std;
ll n;
struct XL{
    ll x1,h,in;
    bool operator<(const XL &line) const{
        return x1<line.x1;
    }
}X[MAXN<<2];
ll Y[MAXN<<2],xn=1,yn=2,yend;
ll getrank(ll y){
    ll h=1,t=yend;
    while(h<=t){
        ll mid=(h+t)>>1;
        if(Y[mid]==y) return mid;
        else if(Y[mid]<y) h=mid+1;
        else t=mid-1;
    }
    return -1;//
}

struct node{
    ll cov,covl,len;
}root[MAXN<<2];

void pushup(ll l,ll r,ll num){
    if(root[num].cov) root[num].covl=Y[r+1]-Y[l];
    else if(l==r) root[num].covl=0;
    else root[num].covl=root[num<<1].covl+root[num<<1|1].covl;
}
void cover(ll L,ll R,ll val,ll l,ll r,ll num){
    if(L<=l&&r<=R){
        root[num].cov+=val;
        pushup(l,r,num);
        return;
    }
    ll mid=(l+r)>>1;
    if(L<=mid) cover(L,R,val,l,mid,num<<1);
    if(R>mid)  cover(L,R,val,mid+1,r,num<<1|1);
    pushup(l,r,num);
}
int main()
{
    cin>>n;
    ll i=n;
    while(i--){
        ll a,b,h;
        scanf("%I64d%I64d%I64d",&a,&b,&h);
        X[xn].x1=a;X[xn].h=h;X[xn++].in=1;
        X[xn].x1=b;X[xn].h=h;X[xn++].in=-1;
        Y[yn++]=h;
    }
    sort(X+1,X+2*n+1);//x取值是[1,xn)
    sort(Y+1,Y+2*n+2);
    yend=unique(Y+1,Y+2*n+2)-Y-1;//离散后y方向的取值为[1,yend];
    ll ans=0;ll prel=0,prex=0;
    for(i=1;i<xn;i++){
        ans+=(X[i].x1-prex)*prel;
        prex=X[i].x1;
        cover(1,getrank(X[i].h)-1,X[i].in,1,yend-1,1);
        prel=root[1].covl;
    }
    cout<<ans<<endl;
    return 0;
}
