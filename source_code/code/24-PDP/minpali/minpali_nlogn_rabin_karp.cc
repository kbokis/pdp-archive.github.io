//https://pdp-archive.github.io/24-PDP/c-minpali-statement
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <map>
#include <cmath>
#include <cstring>

#ifndef CONTEST
	#define dprintf	printf	//allow debug printf
#else
	#define dprintf (void)//don't prode code for dprintf
	#define NDEBUG	//remove assert()
#endif
#include <cassert>

using namespace std;

const long 	MAXN = long(1e7);
long 		N;
char 		S[MAXN+1];
long 		C;	//factor for rabin karp poly. Has to be > number of chars

typedef unsigned long long hasht;
const hasht	MOD = hasht(1e9)+7;	//It is imperative that MOD*MOD fit hasht typedef
hasht right[MAXN/2+2];//right[i] = hash of substr that ends at [N-i] with length i	
	//typical memory usage for sizeof(hasht)==8 is less than 40Mbytes
	//so we are withing allowed limit provided that the only other array
	//is of 10Mbytes the S[] array

hasht powC(long n){	
	//O(log2N) calc power of C (not enough mem to store all values in array)
	//binary lifting to calc value of pow(C,n) in log2(n)
	static hasht _pow[32];
	static long sz = 0;
	if(sz == 0){//precompute powers of C array
		sz = ceil(log2(N/2));
		_pow[0] = C;
		for(long i=1; i<=sz; ++i)
			_pow[i] = (_pow[i-1] * _pow[i-1]) % MOD;
	}
	hasht z = 1;
	for(long i = sz; i>=0; --i)
		if(n & (1l<<i))
			z = (z * _pow[i]) % MOD;
	return z;
}

bool doublecheck(long leftend,long length){
	//check if collition in hashing occured. We have to check up to length chars.
	long left = leftend - length + 1;//where lest string starts(forward parsing)
	long right= N-1;//where right string starts (backward parsing)
	dprintf("dc: %ld[%d] with %ld[%d]\n",left,S[left],right,S[right]);
	while(left<right)
		if(S[left++]!=S[right--])
			return false;
	return true;
}

void readS(){//read and compress S[]
	scanf("%ld %s",&N,S);
	//compress input chars
	C = 1;
	int V[256];
	memset(V,0,sizeof(V));
	for(long i=0;i<N;++i){//compress values
		int& cv = V[S[i]];
		if(cv == 0)
			cv = C++;
		S[i] = cv;
	}
}

void calc_reverse_hashes(){
	//calc reverse hashes for every i in [1,N/2] for
	//substr starting from N-i and length i
	//This is the rightmost substr of palindrome.
	//The max powered element is the rightmost (Rabin Karp polynomial expr)
	//The min powered element is the leftmost (Rabin Karp polynomial expr)
	hasht val = 0;
	for(long i=1;i<=N/2;++i){
		val = (val * C) % MOD;//shift prev substr (create space)
		val = (val + S[N-i]) % MOD;//add newbie to space created
		right[i] = val;
	}
}
	
int main(){
#ifdef CONTEST
	freopen("minpali.in", "r",stdin);
	freopen("minpali.out","w",stdout);
#endif
	readS();
	
	//worst case: no part of string can be reused to build palindrome.
	//	We will need N-1 more chars.
	//best  case: entire string is a palindrome
	//	so no more chars are required
	//note:	if the ans is odd, then we have a central pivot char
	//	if the ans is even, we have two exact halfs without a pivot.
	//worstcase is 2*(N-1)+1 (with last char being pivot)
	
	long 	worstcase 	= (N-1)*2+1,
		bestcase 	= N,
		ans 		= worstcase;

	calc_reverse_hashes();

	long 	leftend  = N/2-1, length = N/2;
	hasht 	left 	 = 0, expC = powC(length-1);
	bool 	haspivot = (N&1);

	//calc the first subst of palindrome
	for(long i = 0; i<=leftend; ++i)
		left = ((left * C) % MOD + S[i]) % MOD;

	for(ans=bestcase; ans<=worstcase; ++ans){
		dprintf("ans=%ld, left=%lld, right[%ld]=%lld, length=%ld leftend=%ld haspivot=%d\n",
			ans,left,length,right[length],length,leftend,haspivot);
		
		if(left == right[length] /*&& doublecheck(leftend,length)*/)
			break;
			
		//left substr in [leftend - length + 1, leftend]
		//right substr starts in [leftend + 1 + haspivot] and has length chars
		
		if(haspivot){
			//roll left substr 1 to the right. length not changed
			//first step: remove maximum powered character
			left = (left - (expC * S[leftend-length+1])%MOD + MOD) % MOD;
			//shift remaining value and add newbie character
			left = ((left * C) % MOD + S[++leftend]) % MOD;
		} else {
			//shrink left edge of left substr by one
			left = (left - (expC * S[leftend-length+1])%MOD + MOD) % MOD;
			--length;
			expC = powC(length - 1);//length changed, recalc exponent of max element
		}
		haspivot = !haspivot;
	}
	
	printf("%ld\n",ans);
	return 0;
}

