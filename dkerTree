#include<cstdio>
using namespace std;
int n,root;
struct node{
	int fa,leftchild,rightchild;
	long long value;	
}map[1000010];
void insert(int x){
	int t=x-1;
	int v=map[x-1].value;
	while(map[x].value<v){
		t=map[t].fa;
		v=map[t].value;
	}
	map[x].fa=t;
	if(map[t].rightchild!=0){
		map[x].leftchild=map[t].rightchild;
		map[t].rightchild=x;
		map[map[x].leftchild].fa=x;
	}else{
		map[t].rightchild=x;
	}
}
void make_tree_and_init(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&map[i].value);
		insert(i);
		if(map[i].fa==0)root=i;
	}
}
int main(){
	make_tree_and_init();
}
