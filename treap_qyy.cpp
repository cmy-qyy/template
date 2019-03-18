#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e9+10;
class Node{
    public:
	Node *l,*r,*fa;int siz,sum,rnd,val;
	Node(int _val):val(_val){siz=1;sum=1;rnd=rand();l=r=fa=NULL;}
	void asksiz(){siz=sum;if(l!=NULL) siz+=l->siz;if(r!=NULL) siz+=r->siz;}
};

class Treap{
    public:
	Node *root,*pre,*pos;
	Treap(){root=new Node(-MAXN);root->rnd=-1;}
	void swp(Node *son){
	    Node *faa=son->fa;
	    if(faa->val > son->val){faa->l=son->r;if(son->r!=NULL) son->r->fa=faa;son->r=faa;}
	    else{faa->r=son->l;if(son->l!=NULL) son->l->fa=faa;son->l=faa;}
	    son->fa=son->fa->fa; faa->fa=son;
	    if(son->fa->val > son->val) son->fa->l=son;else son->fa->r=son;
	    faa->asksiz();son->asksiz();
	}
	void add(int x){
	    pos=root;
	    while(pos!=NULL){
		if(pos->val==x){pos->sum++;while(pos!=root) pos->asksiz(),pos=pos->fa;return;}
		pre=pos;
		if(pos->val > x) pos=pos->l;else pos=pos->r;
	    }
	    if(pre->val >x) pos=pre->l=new Node(x),pos->fa=pre;       else pos=pre->r=new Node(x),pos->fa=pre;
	    while(pos->rnd < pos->fa->rnd) swp(pos);
	    while(pos!=root) pos->asksiz(),pos=pos->fa;
	}
	void del(int x){
	    pos=root;
	    while(pos->val != x){
		if(pos->val>x) pos=pos->l;else pos=pos->r;
	    }
	    if(pos->sum>1){
		pos->sum--;
		while(pos!=root) pos->asksiz(),pos=pos->fa;
		return;
	    }
	    while((pos->l!=NULL)&&(pos->r!=NULL)){if(pos->l->rnd <pos->r->rnd) swp(pos->l);else swp(pos->r);}
	    pre=pos;
	    if(pre->l!=NULL) pos=pos->l;
	    if(pre->r!=NULL) pos=pos->r;
	    if(pos!=pre){
		pos->fa=pos->fa->fa;
		if(pos->fa->val > pos->val) pos->fa->l=pos;else pos->fa->r=pos;
	    }else{
		if(pos->fa->val > pos->val) pos->fa->l=NULL;else pos->fa->r=NULL;
	    }
	    pos=pos->fa;delete pre;
	    while(pos!=root) pos->asksiz(),pos=pos->fa;
	}
	int rating(int x){
	    pos=root->r;int ans=0;
	    while(pos->val!=x){
		if(x<pos->val){pos=pos->l;continue;}
		if(pos->l!=NULL) ans+=pos->l->siz;
		ans+=pos->sum;
		pos=pos->r;
	    }
	    if(pos->l!=NULL) ans+=pos->l->siz;
	    return ans+1;
	}
	int asknum(int x){
	    pos=root->r;
	    while(x){
		if((pos->l!=NULL)&&(pos->l->siz >= x)){pos=pos->l;continue;}
		if(pos->l!=NULL) x-=pos->l->siz;
		if(x<=pos->sum) return pos->val;
		x-=pos->sum; pos=pos->r;
	    }
	    return 0;
	}
	int asklnum(int x){
	    pos=root->r; int ans=-MAXN;
	    while(pos!=NULL){
		if(pos->val >= x){pos=pos->l;continue;}
		ans=max(ans,pos->val);pos=pos->r;
	    }
	    return ans;
	}
	int askrnum(int x){
	    pos=root->r; int ans=MAXN;
	    while(pos!=NULL){
		if(pos->val <= x){pos=pos->r;continue;}
		ans=min(ans,pos->val);pos=pos->l;
	    }
	    return ans;
	}
	void print(Node *x){
	    printf("x=%d siz=%d ",x->val,x->siz);
	    if(x->l!=NULL) printf("l=%d ",x->l->val);if(x->r!=NULL) printf("r=%d ",x->r->val);
	    printf("\n");
	    if(x->l!=NULL) print(x->l);if(x->r!=NULL) print(x->r);
	}
}T;

int main(){
    srand(time(NULL));
    int t,x,y;
    scanf("%d",&t);
    while(t--){
	scanf("%d%d",&x,&y);
	switch(x){
	    case 1:T.add(y);break;
	    case 2:T.del(y);break;
	    case 3:printf("%d\n",T.rating(y));break;
	    case 4:printf("%d\n",T.asknum(y));break;
	    case 5:printf("%d\n",T.asklnum(y)); break;
	    case 6:printf("%d\n",T.askrnum(y)); break;
	}
	//printf("\nt=%d\n",t);
	//T.print(T.root);
    }
    return 0;
}
