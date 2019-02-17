#include<cstdio>
#include<algorithm>
#include<cstring>
#include<climits>
#define I inline
using namespace std;
typedef long long LL;
const int Mx=1e5+10086;
int n,root,q;
template<typename FST>
I FST read(){
    FST ans=0,b=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')b=-1;else b=1;ch=getchar();}
    while(ch>='0'&&ch<='9'){ans=ans*10+ch-48;ch=getchar();}
    return ans*b;
}
template<class T>T swp(T &a,T &b){a=a^b;b=a^b;a=a^b;}
template<class T>
class Tree{
public:
    I void addEdge(int x,int y){
        nex[++tot]=fir[x];fir[x]=tot;to[tot]=y;
        nex[++tot]=fir[y];fir[y]=tot;to[tot]=x;
    }
    I void addValue(int x,T v){
        node[x].v=v;
    }
    I void buildTree(int x,int f){
        int MaxSon=-1;
        node[x].depth=node[f].depth+1;
        node[x].fa=f;
        node[x].size=1;
        for(int i=fir[x];i;i=nex[i]){
            int v=to[i];
            if(v==f)continue;
            buildTree(v,x);
            node[x].size+=node[v].size;
            if(node[v].size>MaxSon)node[x].son=v,MaxSon=node[v].size;
        }
    }
protected:
    struct Node{
        int fa,son,depth,id,size,top;
        T v;
    }node[Mx];
    int fir[Mx],nex[Mx<<1],to[Mx<<1],tot;
};
template<class T>
class CutTree:public Tree<T>{
public:
    using Tree<T>::node;
    using Tree<T>::fir;
    using Tree<T>::nex;
    using Tree<T>::to;
    I void buildCutTree(int x,int top){
        node[x].id=++si;
        node[x].top=top;
        van[si]=node[x].v;
        if(!node[x].son)return;
        buildCutTree(node[x].son,top);
        for(int i=fir[x];i;i=nex[i]){
            int v=to[i];
            if(v==node[x].fa||v==node[x].son)continue;
            buildCutTree(v,v);
        }
    }
protected:
    T van[Mx];int si;
};
template<class T>
class SegTree:public CutTree<T>{
public:
    #define s segnode
    #define _P lazyTag_p
    #define _T lazyTag_t
    #define ls (k<<1)
    #define rs (k<<1|1)
    using Tree<T>::node;
    using Tree<T>::fir;
    using Tree<T>::nex;
    using Tree<T>::to;
    using CutTree<T>::van;
    I void buildSegTree(int k,int l,int r){
        s[k]=(SegNode){(T)0,(T)1,(T)0,l,r};
        if(l==r){s[k].v=van[l];return;}
        int mid=(l+r)>>1;
        if(l<=mid)buildSegTree(ls,l,mid);
        if(r>mid)buildSegTree(rs,mid+1,r);
        pushUp(k);
    }
    I T query(int k,int l,int r){
        int sl=s[k].l,sr=s[k].r;
        if(l<=sl&&r>=sr)return s[k].v;
        T ans=0;
        pushDown(k);
        int mid=(sl+sr)>>1;
        if(l<=mid)ans+=query(k<<1,l,r);
        if(r>mid)ans+=query(k<<1|1,l,r);
        return ans;
    }
    I void update(int k,int l,int r,T _p,T _t){
        int sl=s[k].l,sr=s[k].r;
        if(l<=sl&&r>=sr){
            goAdd(k,sr-sl+1,_p,_t);
            return;
        }
        pushDown(k);
        int mid=(sl+sr)>>1;
        if(l<=mid)update(ls,l,r,_p,_t);
        if(r>mid)update(rs,l,r,_p,_t);
        pushUp(k);
    }
    I T queryRange(int x,int y){
        T ans=0;
        while(node[x].top!=node[y].top){
            if(node[node[x].top].depth<node[node[y].top].depth)swp(x,y);
            ans+=query(1,node[node[x].top].id,node[x].id);
            x=node[node[x].top].fa;
        }
        if(node[x].depth>node[y].depth)swp(x,y);
        ans+=query(1,node[x].id,node[y].id);
        return ans;
    }
    I T querySon(int x){
        return query(1,node[x].id,node[x].id+node[x].size-1);
    }
    I void updRange(int x,int y,T _p,T _t){
        while(node[x].top!=node[y].top){
            if(node[node[x].top].depth<node[node[y].top].depth)swp(x,y);
            update(1,node[node[x].top].id,node[x].id,_p,_t);
            x=node[node[x].top].fa;
        }
        if(node[x].depth>node[y].depth)swp(x,y);
        update(1,node[x].id,node[y].id,_p,_t);
    }
    I void updSon(int x,T _p,T _t){
        update(1,node[x].id,node[x].id+node[x].size-1,_p,_t);
    }
private:
    struct SegNode{
        T lazyTag_p,lazyTag_t,v;int l,r;
    }segnode[Mx<<2];
    I void pushUp(int k){
        s[k].v=s[ls].v+s[rs].v;
    }
    I void pushDown(int k){
        int l=s[k].l,r=s[k].r,mid=(l+r)>>1;
        goAdd(ls,mid-l+1,s[k]._P,segnode[k]._T);
        goAdd(rs,r-mid,s[k]._P,segnode[k]._T);
        s[k]._P=0;s[k]._T=1;
    }
    I void goAdd(int k,T range,T _p,T _t){
        s[k]._T*=_t;s[k]._P*=_t;
        s[k]._P+=_p;s[k].v*=_t;
        s[k].v+=_p*range;
    }
};SegTree<LL> T;

void init(){
    n=read<int>();q=read<int>();
    for(int i=1;i<=n;i++)T.addValue(i,read<int>());
    for(int i=1;i<n;i++)T.addEdge(read<int>(),read<int>());
    T.buildTree(1,0);
    T.buildCutTree(1,1);
    T.buildSegTree(1,1,n);
}
template<class T1>
void work(){
    int op,x,y;T1 v;
    while(q--){
        op=read<int>();
        switch(op){
            case 1:x=read<int>();v=read<T1>();T.updRange(x,x,v,1);break;
            case 2:x=read<int>();v=read<T1>();T.updSon(x,v,1);break;
            case 3:x=read<int>();printf("%lld\n",T.queryRange(x,1));
        }
    }
}
int main(int argv,char* argc[]){
    init();
    work<LL>();
}
