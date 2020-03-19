//https://pdp-archive.github.io/24-PDP/c-minpali-statement
#include <cstdio>
#include <algorithm>
#include <cassert>

using namespace std;

const long MAXN = long(1e7);
long N;
char S[MAXN+1];

typedef long long hash;
const hash C 	= 17;//just a prime for hash calcs
const hash MOD	= hash(1e18)+7;//for modulos to prevent overflows
hash  pows[MAXN/2+1] = {1};//memoisation of C powers

#ifndef CONTEST
	#define dprintf	printf
#else
	#define dprintf (void)
#endif

hash calc_hash(long l1,long l2,long step){
	long j = 1;
	hash h = 0;
	l2 += step;
	while(l1!=l2){
		if(step>0){//calc powers of C. Once only
			pows[j] = ( (pows[j-1] * C) % MOD );
			j++;
		}
		
		//advance hash value by one more letter
		h *= C;
		h += S[l1];
		l1 += step;
		h %= MOD;
		
		dprintf("l1=%ld, l2=%ld, S[]=%c=%d, h=%lld\n",l1-step,l2-step,S[l1-step],S[l1-step],h);
	}
	return h;
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
	long 	worstcase = N * 2 - 1,
		bestcase = N,
		ans;
		
	long 	left1 = 0, 
		left2 = N/2 - (!(N%2)), //left2 = (N is odd) ? (N/2) : (N/2-1);
		right1 = N/2,
		right2 = N-1;//substrings positions [left1,left2] and [right1,right2]
		//left1 < left2 <= right1 < right2
		
	//initial calculation
	hash 	left  = calc_hash(left1, left2,  1), 
		right = calc_hash(right2,right1,-1);
			
	for(ans=bestcase; ans<=worstcase && left!=right; ans++){
		dprintf("\n%ld\n",ans);
		dprintf("left [%ld,%ld] hash = %lld\n",left1, left2, left);
		dprintf("right[%ld,%ld] hash = %lld\n",right1,right2,right);
		assert(left2-left1 == right2-right1);
		//do rolling
		if(left2 == right1){//there was a pivot in the center
			//left1 shrinks substr ro the right
			left -= ((S[left1]*pows[left2-left1])%MOD);
			left = (left + MOD) % MOD;
			++left1;
			//right1 shrinks to the right
			//in order to avoid divisions and modulos, we can multiply left by C
			right = (right - S[right1] + MOD) % MOD;
			++right1;
			//we should divide right by C but this is dangerous. We better multiply left with C
			//left = (left * C) % MOD;
			right /= C;
		} else {//no pivot in the center
			//[left1,left2] substr rolls to the right
			left -= ((S[left1]*pows[left2-left1])%MOD);
			left = (left + MOD) % MOD;
			left = (left * C) % MOD;
			++left2;
			left += S[left2];
			++left1;
		}
	}
	
	printf("%ld\n",ans);
	return 0;
}

