#include <iostream>
#include <cstdio>
#include <algorithm>
#define MAXN 20010
using namespace std;
int n;
struct cows{
    int x,v;
    bool operator<(const cows&c2) const{
        return v<c2.v;
    }
}cow[MAXN];

int xn[MAXN],xv[MAXN];
inline int lowbit(int x){return x&(-x);}
void addval(int x,int val,int c[MAXN]){
    for(int ind=x;ind<=MAXN;ind+=lowbit(ind)){
        c[ind]+=val;
    }
}
long long sum(int x,int c[MAXN]){
    long long s=0;
    for(int i=x;i;i-=lowbit(i)){
        s+=c[i];
    }
    return s;
}
int main()
{
//    freopen("C:\\Users\\marlin\\Desktop\\input.txt","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&cow[i].v,&cow[i].x);
    }
    sort(cow+1,cow+n+1);
    //debug
//    for(int i=1;i<=n;i++)
//        cout<<"coordinate x: "<<cow[i].x<<",volume v: "<<cow[i].v<<endl;
    long long ans=0;
    for(int i=1;i<=n;i++){
        long long less_num=sum(cow[i].x,xn);//小于x的牛的个数
        long long lv_sum =sum(cow[i].x,xv);//位于x号牛左边的牛x之和
        ans+= (less_num*cow[i].x-lv_sum)*cow[i].v;
    //debug
//        cout<<"i:"<<i<<",less_sum:"<<less_num<<",lv_sum:"<<lv_sum<<endl;
        long long big_num=sum(MAXN,xn)-less_num;
        long long rv_sum=sum(MAXN,xv)-lv_sum;
        ans+= (rv_sum-big_num*cow[i].x)*cow[i].v;
    //debug
//        cout<<"i:"<<i<<",big_sum:"<<big_num<<",rv_sum:"<<rv_sum<<endl;
        addval(cow[i].x,cow[i].x,xv);
        addval(cow[i].x,1,xn);
    }
    cout<<ans<<endl;
    return 0;
}
