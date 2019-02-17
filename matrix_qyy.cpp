#include<bits/stdc++.h>
using namespace std;
const int N=100;
const int M=100;
template<class T,int N,int M>
class Matrix{
    private:
    char ch[10];
    public:
    T n,m,A[N][M];
    Matrix(int _n=0,int _m=0):n(_n),m(_m){memset(A,0,sizeof(A));}
    friend Matrix<T,N,M> operator * (Matrix<T,N,M> a ,Matrix<T,N,M> b){
	Matrix<T,N,M> ans(a.n,b.m);
	for(int i=0;i<a.n;i++)
	    for(int j=0;j<b.m;j++)
		for(int k=0;k<a.m;k++)
		    ans.A[i][j]+=a.A[i][k]*b.A[k][j];
	return ans;
    }
    void pre(){
        if(typeid(T).name()==typeid(int).name()) sprintf(ch,"%%d "); 
        if(typeid(T).name()==typeid(long long).name())sprintf(ch,"%%lld ");
    }
    void scan(){
    pre();
    for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	    scanf(ch,&A[i][j]);
    }
    void print(){
    pre();
    for(int i=0;i<n;i++,printf("\n"))
	for(int j=0;j<m;j++)
	    printf(ch,A[i][j]);
    }
};
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    Matrix<long long,N,M>a(n,m);
    Matrix<long long,M,N>b(m,n);
    a.scan();
    b.scan();
    a=a*b;
    a.print();
}
