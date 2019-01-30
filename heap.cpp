#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1000005;
int read(){
	int res=0,b=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')b=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){res=(res<<3)+(res<<1)+ch-'0';ch=getchar();}
	return b*res;
}
class Heap{
	public:
		void setN(int N){
			n=N;
		}
		void setAry(int i,int v){
			ary[i]=v;
		}
		void add(int v){
			ary[++n]=v;
			push(n);
		}
		void init(){
			memset(heap,0,sizeof heap);
			si=0;
		}
		void push(int x){
			heap[++si]=x;
			Map[x]=si;
			up(si);
		}
		void pop(){
			swap(1,si--);
			down(1);
		}
		int topValue(){
			return ary[heap[1]];
		}
		int topPosition(){
			return heap[1];
		}
		int size(){
			return si;
		}
		void modify(int v,int i){
			ary[i]=v;
			up(Map[i]);
			down(Map[i]);
		}
		void extraOP();
	private:
		int si,n;
		int heap[maxn],ary[maxn],Map[maxn];
		void swap(int x,int y){
			int t=heap[x];
			heap[x]=heap[y];
			heap[y]=t;
			t=Map[heap[x]];
			Map[heap[x]]=Map[heap[y]];
			Map[heap[y]]=t;
		}
		bool cmp(int x,int y){
			return ary[heap[x]]<ary[heap[y]];
		}
		void up(int x){
			if(x==1)return;
			if(cmp(x,x>>1)){
				swap(x,x>>1);
				up(x>>1);
			}
		}
		void down(int x){
			if((x<<1)>si)return;
			if(cmp(x<<1,x)){
				if(si==(x<<1)||cmp(x<<1,x<<1|1)){
					swap(x,x<<1);
					down(x<<1);
					return;
				}
			}
			if((x<<1|1)<=si&&cmp(x<<1|1,x)){
				swap(x,x<<1|1);
				down(x<<1|1);
			}
		}
};Heap H;
int main(){
	int n=read();H.setN(n);
	for(int i=1;i<=n;i++)H.setAry(i,read());
	for(int i=1;i<=n;i++)H.push(i);
	H.extraOP();
	for(int i=1;i<=n;i++)printf("%d ",H.topValue()),H.pop();
}
void Heap::extraOP(){
	
}
