#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<climits>
#define LL long long
using namespace std;
const LL maxn=1e5+5;
const LL maxm=1e5*3+5;

struct line{
	int aside,bside;
	LL value;
}link[maxm];
int ltop,m;
int ufa[maxn];
LL MSTsum;

bool isMST[maxm];

vector<int> edge[maxn];
int n;

int lfa[maxn][40],lg[maxn],depth[maxn];

struct maxlist{
	LL Max,seMax;
}dp[maxn][40];

LL ans;

void add(int x,int y,int z){
	link[++ltop].aside=x;
	link[ltop].bside=y;
	link[ltop].value=z;	
}

int ask(int x){
	if(ufa[x]==x)return x;
	return ufa[x]=ask(ufa[x]);
}

void unite(int x,int y){
	ufa[x]=y;
}

bool cmp(line a,line b){
	return a.value<b.value;
}
void kruskal(){
	int sum=0;
	sort(link+1,link+1+m,cmp);
	for(int i=1;i<=m&&sum<n-1;i++){
		int xx=ask(link[i].aside);
		int yy=ask(link[i].bside);
		if(xx!=yy){
			isMST[i]=1;
			unite(xx,yy);
			sum++;
			MSTsum+=link[i].value;
		}
	}
}

void dfs(int x,int f){
	lfa[x][0]=f;
	depth[x]=depth[f]+1;
	for(int i=1;i<=lg[depth[x]];i++){
		lfa[x][i]=lfa[lfa[x][i-1]][i-1];
		
		dp[x][i].Max=max(dp[lfa[x][i-1]][i-1].Max,dp[x][i-1].Max);
		dp[x][i].seMax=max(dp[lfa[x][i-1]][i-1].seMax,dp[x][i-1].seMax);
		if(dp[lfa[x][i-1]][i-1].Max!=dp[x][i-1].Max){
			dp[x][i].seMax=max(dp[x][i].seMax,min(dp[lfa[x][i-1]][i-1].Max,dp[x][i-1].Max));
		}
	}
	
	for(int i=0;i<edge[x].size();i++){
		int p=edge[x][i];
		int to=link[p].aside+link[p].bside-x;
		if(to==f)continue;
		dp[to][0].Max=link[p].value;
		dp[to][0].seMax=-1;
		dfs(to,x);
	}
}

int lca(int x,int y){
	if(depth[x]<depth[y])swap(x,y);
	while(depth[x]>depth[y])x=lfa[x][lg[depth[x]-depth[y]]-1];
	if(x==y)return x;
	for(int k=lg[depth[x]];k>=0;k--){
		if(lfa[x][k]!=lfa[y][k]){
			x=lfa[x][k];
			y=lfa[y][k];
		}
	}
	return lfa[x][0];
}
void beat(LL &m1,LL &m2,LL beater){
	if(beater>m1){
		m2=m1;
		m1=beater;
		return;
	}
	if(beater>m2&&beater!=m1){
		m2=beater;
		return;
	}
	return;
}

LL donate(int x,int y,int c){
	int fa=lca(x,y);
	LL m1=-1,m2=-1;
	while(depth[x]>depth[fa]){
		beat(m1,m2,dp[x][lg[depth[x]-depth[fa]]-1].Max);
		x=lfa[x][lg[depth[x]-depth[y]]-1];
	}
	
	while(depth[y]>depth[fa]){
		beat(m1,m2,dp[y][lg[depth[y]-depth[fa]]-1].Max);
		y=lfa[y][lg[depth[y]-depth[fa]]-1];
	}
	if(m1!=c){
		return c-m1;
	}
	if(m2!=-1){
		return c-m2;
	}
	return 0;
}

void init(){
	int x,y,z;
	scanf("%d%d",&n,&m);
	memset(edge,0,sizeof(edge));
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);

	}
	for(int i=1;i<=n;i++){
		ufa[i]=i;
	}
	for(int i=1;i<=n;i++){
		lg[i]=lg[i-1]+((1<<lg[i-1])==i);
	}
}

void work(){
	kruskal();
	for(int i=1;i<=m;i++){
		if(isMST[i]){
			edge[link[i].aside].push_back(i);
			edge[link[i].bside].push_back(i);
		}
	}
	dfs(1,0);
	ans=INT_MAX;
	for(int i=1;i<=m;i++){
		if(!isMST[i]){
			LL t=donate(link[i].aside,link[i].bside,link[i].value);
			if(t!=0)ans=min(ans,t);
		}	
	}
}

void print(){
	printf("%lld",MSTsum+ans);
}

int main(){
	init();
	work();
	print();
}
