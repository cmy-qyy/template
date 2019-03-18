#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,suma,sumb,x,a[1000000],mina,minb;
main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<n;i++){
	x=abs(a[i]-a[i+1]);
	if(i&1) suma+=x;
	else suma-=x;
	ans=max(ans,suma-mina);
	ans=max(ans,maxa-suma);
	if(i&1==0) mina=min(mina,suma);
	else maxa=max(maxa,suma);
    }
    printf("%lld",ans);
    return 0;
}