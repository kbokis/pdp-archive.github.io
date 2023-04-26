#include <cstdio>
#include <vector>
#include <set>

using namespace std;

long N,K,ans;
vector<long> A;

int main(){
	freopen("chemicals.in","r",stdin);
	freopen("chemicals.out","w",stdout);
	scanf("%ld%ld",&N,&K);
	A.resize(N);
	for(long i=0;i<N;i++){
		scanf(" %d",&A[i]);
		A[i] %= K;
	}
	for(long L=0;L<N;L++){
		set<long> S;
		for(long R=L;R<N;R++){
			if(A[R]==0 && S.find(0)!=S.end())break;
			if(S.find(K-A[R])!=S.end())break;
			S.insert(A[R]);
			ans = max(ans, R-L+1);
		}
	}
	printf("%ld\n",ans);
	return 0;
}
