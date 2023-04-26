#include <cstdio>
#include <map>
#include <vector>

using namespace std;

long N,K,ans;
vector<long> A;
map<long,long> M;


int main(){
	freopen("chemicals.in","r",stdin);
	freopen("chemicals.out","w",stdout);
	scanf("%ld%ld",&N,&K);
	A.resize(N);
	for(long i=0;i<N;i++){
		scanf(" %ld",&A[i]);
		A[i] %= K;
	}
	for(long L=0,R=0;R<N;R++){
		long incompatible = (A[R]==0) ? 0 : K - A[R];
		map<long,long>::iterator it = M.find(incompatible);
		if(it!=M.end()){
			while(M[incompatible] > 0)
				M[A[L++]]--;
		}
		M[A[R]]++;//τώρα είναι ασφαλές να προσθέσουμε το A[R] στα στοιχεία μας
		ans = max(ans,R-L+1);
		
	}
	printf("%ld\n",ans);
	return 0;
}
