#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=1e5+10;
const int maxnode=2e6+10;
int Map[maxn],lg[maxn];
int n,m;
inline int read(){
    int ans=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')ans=(ans<<3)+(ans<<1)+ch-'0',ch=getchar();
    return ans;
}

class Tree{
    public:
        void init(){
            memset(fir,0,sizeof(fir));
            memset(fa,0,sizeof(fa));
            tot=0;
        }
        int lca(int x,int y){
            if(depth[x]<depth[y])swap(x,y);
            while(depth[x]>depth[y])x=fa[x][lg[depth[x]-depth[y]]-1];
            if(x==y)return x;
            for(int i=lg[depth[x]];i>=0;i--){
                if(fa[x][i]!=fa[y][i]){
                    x=fa[x][i];
                    y=fa[y][i];
                }
            }
            return fa[x][0];
        }
        void add(int x,int y){
            nex[++tot]=fir[x];
            fir[x]=tot;
            to[tot]=y;
            nex[++tot]=fir[y];
            fir[y]=tot;
            to[tot]=x;
        }
    protected:
        static int fir[maxn],nex[maxn<<1],to[maxn<<1];
        int tot;
        static int fa[maxn][18],depth[maxn];
};
int Tree::fir[maxn],Tree::nex[maxn<<1],Tree::to[maxn<<1];
int Tree::fa[maxn][18],Tree::depth[maxn];
Tree RT;

class MTrie{
    public:
        void init(){
            memset(node,0,sizeof(node));
            memset(root,0,sizeof(root));
            tot=0;
        }
        void insert(int x,int f,int v){
            root[x]=++tot;
            int rtx=root[x],rtf=root[f];
            int t;
            for(int i=15;i>=0;i--){
                t=(v>>i)&1;
                if(!node[rtx].son[t]){
                    node[rtx].son[t]=++tot;
                    node[rtx].son[!t]=node[rtf].son[!t];
                    node[node[rtx].son[t]].size=node[node[rtf].son[t]].size;
                }
                rtx=node[rtx].son[t];
                rtf=node[rtf].son[t];
                node[rtx].size++;
            }
        }
        int search(int v,int y,int x){
            int f=RT.lca(x,y);
            int res=Map[f]^v,ans=0;
            int rtx=root[x],rty=root[y],rtf=root[f];
            int t;
            for(int i=15;i>=0;i--){
                t=(v>>i)&1;
                if(node[node[rtx].son[!t]].size+node[node[rty].son[!t]].size-2*node[node[rtf].son[!t]].size>0){
                    ans+=1<<i;
                    t=!t;
                }
                rtx=node[rtx].son[t];
                rty=node[rty].son[t];
                rtf=node[rtf].son[t];
            }
            return max(ans,res);
        }
    private:
        struct Node{
            int son[2];
            int size;
        }node[maxnode];
        int tot,root[maxn];
};MTrie MT;

class d:public Tree{
    public:
        void build(int x,int f){
            depth[x]=depth[f]+1;
            fa[x][0]=f;
            MT.insert(x,f,Map[x]);
            for(int i=1;i<=lg[depth[x]];i++)
                fa[x][i]=fa[fa[x][i-1]][i-1];
            for(int i=fir[x],v=to[i];i;i=nex[i],v=to[i]){
                if(v==f)continue;
                build(v,x);
            }
        }
};d D;

int main(){
    for(int i=1;i<=maxn-10;i++)
        lg[i]=lg[i-1]+(1<<lg[i-1]==i);
    while(~scanf("%d%d",&n,&m)){
        RT.init();
        MT.init();
        for(int i=1;i<=n;i++)Map[i]=read();
        for(int i=1;i<n;i++)RT.add(read(),read());
        D.build(1,0);
        for(int i=1;i<=m;i++){
            printf("%d\n",MT.search(read(),read(),read()));
        }
    }
}
