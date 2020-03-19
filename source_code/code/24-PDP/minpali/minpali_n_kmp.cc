//https://pdp-archive.github.io/24-PDP/c-minpali-statement
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const long MAXN = long(1e7);
long N;
char S[MAXN+1];

bool accepted(long K){
	//check if a string of size j with S as prefix can a palindrome
	//[S[0],S[j/2-1]] should be equal to [S[j/2],S[S-1]]
	//but remember that not all of those chars exists
	long left = K/2, right = K/2;
	if((K%2)==0)
		left--;
	while(left>=0 && right<N)
		if(S[left--] != S[right++])
			return false;
	return true;
}

int main(){
	freopen("minpali.in","r",stdin);
#ifdef CONTEST
	freopen("minpali.out","w",stdout);
#endif
	scanf("%ld %s",&N,S);
	//worst case: no part of string can be reused to build palindrome.
	//	We will need N-1 more chars.
	//best  case: entire string is a palindrome
	//	so no more chars are required
	//note:	if the ans is odd, then we have a central pivot char
	//	if the ans is even, we have two exact halfs without a pivot.
	//worstcase is either 2*(N-1)+1 if N is odd, or 2*N if N is even
	long worstcase = N * 2 - (N%2);
	long bestcase  = N;
	for(long i=bestcase;i<=worstcase;i++){
		if(accepted(i)){
			printf("%ld\n",i);
			break;
		}
	}
	return 0;
}

