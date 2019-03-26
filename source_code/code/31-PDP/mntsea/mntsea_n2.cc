#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005
typedef long long ll;
long N;
char str[MAXN];

long validWithFixedRight(long right) {
	long ans=0, countM=0, countS=0;
	for(long left=right; left>0; --left) {
		if ( str[left] == 'm' ) ++countM;
		else ++countS;

		if(countM==countS) ++ans;
	}

	return ans;
}

int main() {
	#ifdef CONTEST
	freopen("mntsea.in","r",stdin);
	freopen("mntsea.out","w",stdout);
	#endif

	scanf("%ld %s", &N, str+1);
	ll ans = 0;
	for(long right=1; right<=N; ++right)
		ans += validWithFixedRight(right);
	printf("%lld\n", ans);
	
	return 0;
}
