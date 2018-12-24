#include <cstdio>
#include <iostream>
#define MAXN 1000000
//#define rmc(x,c) (~(1<<c)&x)
//#define addc(x,c) (x|(1<<c))
using namespace std;
struct node{
    int lv,rv,color;
}root[MAXN<<2];
int tag[MAXN<<2];
void build(int lv,int rv,int num){
    root[num].lv=lv;
    root[num].rv=rv;
    root[num].color=1;
    if(lv!=rv){
        int mid=(lv+rv)>>1;
        build(lv,mid,num<<1);
        build(mid+1,rv,num<<1|1);
    }
}
void pushdown(int num){
    if(root[num].lv==root[num].rv) return;
    tag[num<<1]=tag[num];root[num<<1].color=tag[num];
    tag[num<<1|1]=tag[num];root[num<<1|1].color=tag[num];
    tag[num]=0;
}
void update(int L,int R,int l,int r,int num,int c){
    if(tag[num]) pushdown(num);//°ÑnumµÄtagÏÂÑ¹
    if(L<=l&&r<=R) {
        root[num].color=1<<(c-1);
        tag[num]=1<<(c-1);
        return ;
    }
    int mid=(l+r)>>1;
    if(R<=mid) update(L,R,l,mid,num<<1,c);
    else if(L>mid) update(L,R,mid+1,r,num<<1|1,c);
    else {
        update(L,mid,l,mid,num<<1,c);
        update(mid+1,R,mid+1,r,num<<1|1,c);
    }
    root[num].color=root[num<<1].color|root[num<<1|1].color;
}
int query(int L,int R,int l,int r,int num){
    if(L<=l&&r<=R) return root[num].color;
    int mid=(l+r)>>1;
    if(tag[num]) pushdown(num);
    if(R<=mid) return query(L,R,l,mid,num<<1);
    else if(L>mid) return query(L,R,mid+1,r,num<<1|1);
    else return query(L,mid,l,mid,num<<1)|query(mid+1,R,mid+1,r,num<<1|1);
}
//void debug(int l,int r,int num){
//    cout<<"interval is "<<l<<" to "<<r<<"color is "<<root[num].color<<endl;
//    if(l!=r) debug(l,(l+r)>>1,num<<1),debug(((l+r)>>1)+1,r,num<<1|1);
//}
int bitnum(int n){
    int s=0;
    while(n){
        n-=n&(-n);
        s++;
    }
    return s;
}
int main()
{
   // freopen("C:\\Users\\marlin\\Desktop\\input.txt","r",stdin);
    int len,n;cin>>len>>n>>n;
    build(1,len,1);
    while(n--){
        char s[3];scanf("%s",s);
        int a,b,c;
        if(s[0]=='C'){
            scanf("%d%d%d",&a,&b,&c);
            update(a,b,1,len,1,c);
            //debug
//            cout<<"C "<<a<<" "<<b<<" "<<c<<endl;
//            debug(1,len,1);
        }
        else{
            scanf("%d%d",&a,&b);
            if(a>b) swap(a,b);
            printf("%d\n",bitnum(query(a,b,1,len,1)));
            //debug
//            cout<<"Q "<<a<<" "<<b<<endl;
//            debug(1,len,1);
        }
    }
    return 0;
}
