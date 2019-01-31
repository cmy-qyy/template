#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<climits>
using namespace std;
typedef long long LL;
const int MaxN=10086,MaxM=1e5+10086;
const LL inf=LLONG_MAX/2;
int n,m,S,T,tot;
LL va[MaxM<<1],ans;
int fir[MaxN],to[MaxM<<1],nex[MaxM<<1],dis[MaxN];
int Q[MaxN<<1],h,t;
void addEdge(int x,int y,LL v){
    nex[tot]=fir[x];
    fir[x]=tot;
    to[tot]=y;
    va[tot]=v;
    tot++;
}
bool BFS(){
    memset(dis,0,sizeof dis);
    h=t=0;
    Q[++t]=S;
    dis[S]=1;
    do{
        int x=Q[++h];
        for(int i=fir[x];~i;i=nex[i]){
            if(va[i]==0)continue;
            int v=to[i];
            if(dis[v])continue;
            Q[++t]=v;
            dis[v]=dis[x]+1;
        }
    }while(h<t);
    return dis[T]!=0;
}
LL DFS(int x,LL MF){
    if(x==T||MF==0)return MF;
    int Mini=0,cost=0;
    for(int i=fir[x];~i;i=nex[i]){
        if(va[i]==0)continue;
        int v=to[i];
        if(dis[v]!=dis[x]+1)continue;
        cost=DFS(v,min(va[i],MF));
        va[i]-=cost;
        va[i^1]+=cost;
        Mini+=cost;
        MF-=cost;
        if(!MF)break;
    }
    return Mini;
}
int main(){
    memset(fir,-1,sizeof fir);
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for(int i=1;i<=m;i++){
        int x,y;LL v;
        scanf("%d%d%lld",&x,&y,&v);
        addEdge(x,y,v);
        addEdge(y,x,0);
    }
    while(BFS()){
        ans+=DFS(S,inf);
    }
    printf("%lld",ans);
}
