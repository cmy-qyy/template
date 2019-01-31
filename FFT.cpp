#include<bits/stdc++.h>
using namespace std;
typedef double db;
const int MaxSize=2e6+10086;
const db PI=3.1415926535897;
struct Complex{
    db x,i;
    Complex (db x_=0,db i_=0){x=x_;i=i_;}
    friend Complex operator *(Complex a,Complex b){
        return Complex(a.x*b.x-a.i*b.i,a.x*b.i+a.i*b.x);
    } 
    friend Complex operator +(Complex a,Complex b){
        return Complex(a.x+b.x,a.i+b.i);
    }
    friend Complex operator -(Complex a,Complex b){
        return Complex(a.x-b.x,a.i-b.i);
    }
}A[MaxSize],B[MaxSize];
int n,lim;
inline db read(){
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    return int(ch-48);
}
void Reverse(Complex *A,int lim){
    for(int i=0;i<(lim>>1);i++)swap(A[i],A[lim-i-1]);
}
void fft(int len,Complex *A,int flag){
    if(len==1)return;
    Complex A0[len>>1],A1[len>>1];
    for(int i=0;i<=len;i+=2)
       A0[i>>1]=A[i],A1[i>>1]=A[i+1];
    fft(len>>1,A0,flag),fft(len>>1,A1,flag);
    Complex Base=Complex(cos(2.0*PI/len),flag*sin(2.0*PI/len)),w=Complex(1,0);
    for(int i=0;i<(len>>1);i++,w=w*Base){
        A[i]=A0[i]+w*A1[i];
        A[i+(len>>1)]=A0[i]-w*A1[i];
    }
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)A[i].x=read();
    for(int i=0;i<n;i++)B[i].x=read();
    lim=1;while(lim<n*2)lim<<=1;
    Reverse(A,n);Reverse(B,n);
    fft(lim,A,1);fft(lim,B,1);
    for(int i=0;i<lim;i++)A[i]=A[i]*B[i];
    fft(lim,A,-1);
    for(int i=0;i<lim;i++)A[i].x=A[i].x/lim;
    for(int i=0;i<lim;i++){
        int t=round(A[i].x);
        A[i].x=t%10;A[i+1].x+=t/10;
    }
    while(int(A[lim].x+0.5)==0)lim--;
    for(int i=lim;i>=0;i--)printf("%d",int(A[i].x+0.5));
}
