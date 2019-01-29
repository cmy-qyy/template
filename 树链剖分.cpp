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
int swp(int &a,int &b){a=a^b;b=a^b;a=a^b;}
int Max(int a,int b){return a>b?a:b;}
int Min(int a,int b){return a>b?b:a;}
int Sum(int a,int b){return a+b;}
class Tree{
public:
    I void addEdge(int x,int y){
        nex[++tot]=fir[x];fir[x]=tot;to[tot]=y;
        nex[++tot]=fir[y];fir[y]=tot;to[tot]=x;
    }
    I void addValue(int x,int v){
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
    struct node{
        int fa,son,depth,id,size,top,v;
    }node[Mx];
    int fir[Mx],nex[Mx<<1],to[Mx<<1],tot;
};
class CutTree:public Tree{
public:
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
    I int queryRange(int x,int y,int (*Do)(int,int),int op);
    I int querySon(int x,int op);
    I void updRange(int x,int y,int _p,int _t);
    I void updSon(int x,int _p,int _t);
protected:
    int van[Mx],si;
};
class SegTree:public CutTree{
public:
    #define s segnode
    #define _P lazyTag_p
    #define _T lazyTag_t
    #define _S _sum
    #define _mi _min
    #define _ma _max
    #define ls k<<1
    #define rs k<<1|1
    I void buildSegTree(int k,int l,int r){
        s[k]=(SegNode){0,1,0,0,0,l,r};
        if(l==r){s[k]._S=s[k]._mi=s[k]._ma=van[l];return;}
        int mid=(l+r)>>1;
        if(l<=mid)buildSegTree(ls,l,mid);
        if(r>mid)buildSegTree(rs,mid+1,r);
        pushUp(k);
    }
    I int query(int k,int l,int r,int op){
        int sl=s[k].l,sr=s[k].r;
        if(l<=sl&&r>=sr)return ck(s[k],op);
        int ans=0;
        pushDown(k);
        int mid=(sl+sr)>>1;
        if(l<=mid)CK(ans,query(k<<1,l,r,op),op);
        if(r>mid)CK(ans,query(k<<1|1,l,r,op),op);
        return ans;
    }
    I void update(int k,int l,int r,int _p,int _t){
        int sl=s[k].l,sr=s[k].r;
        if(l<=sl&&r>=sr){
            goAdd(k,sr-sl+1,_p,_t);
            return;
        }
        pushDown(k);
        int mid=(sl+sr)>>1;
        if(l<=mid)update(k<<1,l,r,_p,_t);
        if(r>mid)update(k<<1|1,l,r,_p,_t);
        pushUp(k);
    }
private:
    struct SegNode{
        int lazyTag_p,lazyTag_t,_sum,_min,_max,l,r;
    }segnode[Mx<<2];
    I int ck(SegNode &a,int op){
        switch(op){
            case 1: return a._S; break;
            case 2: return a._ma;break;
            case 3: return a._mi;break;
        }
    }
    I void CK(int &ans,int v,int op){
        switch(op){
            case 1: ans=ans+v;     break;
            case 2: ans=max(ans,v);break;
            case 3: ans=min(ans,v);break;
        }
    }
    I void pushUp(int k){
        s[k]._ma=max(s[ls]._ma,s[rs]._ma);
        s[k]._mi=min(s[ls]._mi,s[rs]._mi);
        s[k]._S=s[ls]._S+s[rs]._S;
    }
    I void pushDown(int k){
        int l=s[k].l,r=s[k].r,mid=(l+r)>>1;
        goAdd(ls,mid-l+1,s[k]._P,segnode[k]._T);
        goAdd(rs,r-mid,s[k]._P,segnode[k]._T);
        s[k]._P=0;s[k]._T=1;
    }
    I void goAdd(int k,int range,int _p,int _t){
        s[k]._T*=_t;s[k]._P*=_t;
        s[k]._P+=_p;s[k]._S*=_t;
        s[k]._S+=_p*range;
    }
    I void goMod(int k){

    }
};SegTree T;
I int CutTree::queryRange(int x,int y,int (*Do)(int,int),int op){
    int ans=0;
    while(node[x].top!=node[y].top){
        if(node[node[x].top].depth<node[node[y].top].depth)swp(x,y);
        ans=Do(ans,T.query(1,node[node[x].top].id,node[x].id,op));
        x=node[node[x].top].fa;
    }
    if(node[x].depth>node[y].depth)swp(x,y);
    ans=Do(ans,T.query(1,node[x].id,node[y].id,op));
    return ans;
}
I int CutTree::querySon(int x,int op){
    return T.query(1,node[x].id,node[x].id+node[x].size-1,op);
}
I void CutTree::updRange(int x,int y,int _p,int _t){
    while(node[x].top!=node[y].top){
        if(node[node[x].top].depth<node[node[y].top].depth)swp(x,y);
        T.update(1,node[node[x].top].id,node[x].id,_p,_t);
        x=node[node[x].top].fa;
    }
    if(node[x].depth>node[y].depth)swp(x,y);
    T.update(1,node[x].id,node[y].id,_p,_t);
}
I void CutTree::updSon(int x,int _p,int _t){
    T.update(1,node[x].id,node[x].id+node[x].size-1,_p,_t);
}
void init(){
    n=read<int>();q=read<int>();
    for(int i=1;i<=n;i++)T.addValue(i,read<int>());
    for(int i=1;i<n;i++)T.addEdge(read<int>(),read<int>());
    T.buildTree(1,0);
    T.buildCutTree(1,1);
    T.buildSegTree(1,1,n);
}
void work(){
    int op,x,y,v;
    while(q--){
        op=read<int>();
        switch(op){
            case 1:
                x=read<int>();v=read<int>();
                T.updRange(x,x,v,1);
                break;
            case 2:
                x=read<int>();v=read<int>();
                T.updSon(x,v,1);
                break;
            case 3:
                x=read<int>();
                printf("%d\n",T.queryRange(x,1,Sum,1));
                break;
        }
    }
}
int main(int argv,char* argc[]){
    int t=read<int>();
    while(t--){
        init();
        work();
    }
}
