---
layout: solution
codename: loutraki
---

## Επεξήγηση εκφώνησης


Μας δίνεται μια συμβολοσειρά χαρακτήρων μήκους $$Ν$$ (το μήκος συμβολοσειρών χαρακτήρων γενικά συμβολίζεται $$\lvert N\rvert$$) και μας ζητείται να υπολογίσουμε το μικρότερο μήκος παλίνδρομου που μπορεί να παραχθεί από αυτό ενώ πρέπει οποσδήποτε η δοσμένη συμβολοσειρά να αποτελεί prefix του τελικού παλίνδρομου  
Προσέξτε ότι δεν δίνεται το σύνολο χαρακτήρων στο οποίο ανοίκουν οι χαρακτήρες. 
Ας υποθέσουμε ότι μας δίνεται η συμβολοσειρά **abcdefed**. Η brute force λύση είναι να δοκιμάσουμε όλους τους συνδιασμούς πιθανών παλίνδρομων άρα από μήκος $$N$$ έως $$2\cdot N-1$$. Λεπτομέρειες στο παρακάτω σχήμα.


![Παράδειγμα](/assets/24-pdp-c-minpali-example2.png){:width="640px"}

  
  	
  	
## Αργή λύση $$\mathcal{O}(N^2)$$ Brute Force

Γνώσεις που θα χρειαστούμε: Καμμία.

Παρακάτω δίνεται μία ενδεικτική υλοποίηση αυτής της λύσης.

```c++
#include <cstdio>
#include <algorithm>

using namespace std;

const long MAXN = long(1e7);
long N;
char S[MAXN+1];

bool accepted(long K){
	//check if a string of size Κ with S as prefix can a palindrome
	//[S[0],S[j/2-1]] should be equal to [S[j/2],S[S-1]]
	//but remember that not all of those chars exists
	//note:	if the ans is odd, then we have a central pivot char
	//	if the ans is even, we have two exact halfs without a pivot.
	long left = K/2, right = K/2;
	if((K%2)==0)
		left--;
	while(left>=0 && right<N)
		if(S[left--] != S[right++])
			return false;
	return true;
}

int main(){
#ifdef CONTEST
	freopen("minpali.in","r",stdin);
	freopen("minpali.out","w",stdout);
#endif
	scanf("%ld %s",&N,S);
	//worst case: no part of string can be reused to build palindrome.
	//	We will need N-1 more chars (1 pivot at the center)
	//best  case: entire string is a palindrome
	//	so no more chars are required
	long 	bestcase  = N, 
		worstcase = N * 2 - 1, 
		ans;
	for(ans=bestcase;ans<=worstcase && !accepted(ans);++ans)
		;
	printf("%ld\n",ans);
	return 0;
}
```


## Μέτρια Λύση - $$\mathcal{O}(N\cdot log{N})$$

Γνώσεις που θα χρειαστούμε: **Rabin-Karp Algorithm** ([wikipedia](https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm)) και **Rolling hash** ([wikipedia](https://en.wikipedia.org/wiki/Rolling_hash))

Το πρόβλημα με την προηγούμενη λύση είναι ότι ενώ θέλουμε να δοκιμάσουμε έναν χαρακτηρα επιπλέον στο αριστερό μισό τμήμα του υποψήφιου παλίνδρομου και να ολισθήσουμε το δεξιό, ελέγχουμε από την αρχή τα $$\frac{N}{2}$$ στοιχεία. Η μέθοδος που θα χρησιμοποιήσουμε θα κάνει κυλιόμενη σύγκριση στην αριστερή και δεξιά συμβολοσειρά ώστε να έχουμε γραμμική πολυπλοκότητα.  

Στον αλγόριθμο Rabin Karp κατασκευάζουμε ένα πολυώνυμο με δυνάμεις ενός σταθερού αριθμού $$C$$ ο οποίος πρέπει να είναι σχετικά πρώτος ως προς κάποιο αριθμό $$\mathit{MOD}$$ που θα χρησιμοποιήσουμε για να αποφύγουμε τα overflow στους ακεραίους που θα χρησιμοποιήσουμε. Ο αριθμός $$C$$ πρέπει να είναι μεγαλύτερος από τον αριθμό των χαρακτήρων που έχουμε στο σύνολο εισόδου. Δηλαδή αν η μέγιστη τιμή ενός χαρακτήρα είναι ο ASCII χαρκτήρας $$z$$ τότε θα πρέπει το C να είναι μεγαλύτερο απο την τιμή αυτή.  

Προσοχή στην εκφώνηση που δεν καθορίζει το σύνολο χαρακτήρων στην είσοδο μας. Δεν μπορούμε να υποθέσουμε ότι υπάρχουν μόνο πεζά γράμματα. Θα πρέπει ή να προβλέψουμε τη χρήση όλων των εκτυπώσιμων χαρακτήρων (σύμβολα, γράμματα, αριθμούς) ή να κάνουμε compress και να αντιστοιχίσουμε κάθε διακριτό χαρακτήρα σε ένα δικό μας αριθμό μεγαλύτερο του μηδενός.  
  
Ο αλγόριθμος Rabin Karp έχει δυνατότητα να "σπρώχνει" (ολισθαίνει) ένα string προς πιο μεγάλες δυνάμεις στο πολυώνυμο, αφήνοντας κενή την θέση που έχει εκθέτη $$C^0$$. Αν δοκιμάσουμε να κάνουμε ολίσθηση προς την ανάποδη κατεύθυνση, θα χρειαστεί να διαιρέσουμε με τον αριθμό $$C$$ με καταστροφικά αποτελέσματα για τον υπολογισμό των τιμών **hashing** που χρησιμοποιούμε. Η λύση σε αυτό είναι να προϋπολογίσουμε τα hash values από τη μια κατεύθυνση και κατόπιν να σαρώσουμε με ένα βρόγχο τη συμβολοσειρά μας από την άλλη κατεύθυνση για να δούμε αν θα ταυτιστούν το αριστερό με το δεξιό hash value. Τα hash values που έχουμε να αποθηκεύσουμε είναι $$\frac{N}{2}$$ οπότε θα καταλάβουν μνήμη εντός ορίων αν χρησιμοποιήσουμε για hash values **long long** ή καλύτερα **__int64** ώστε να έχουμε 8 bytes ανά τιμή.  
  
Δεν τελειώσαμε όμως με τη μνήμη, χρειαζόμαστε και έναν πίνακα με τις δυνάμεις του $$C$$ ώστε να μπορούμε καθώς μειώνεται συνεχώς το μήκος του υπο εξέταση πολυωνύμου να έχουμε τον μέγιστο εκθέτη του ώστε να αφαιρέσουμε τον μέγιστο όρο όταν χρειάζεται. Η λύση που θα δόσουμε είναι με **binary lifting** δηλαδή θα έχουμε έναν πίνακα $$\mathit{pow}$$ με $$log_2(\frac{N}{2})$$ στοιχεία όπου κάθε θέση του $$i$$ θα έχει το $$C^{2^i}$$ αποθηκευμένο, οπότε θα χρειαζόμαστε $$log{k}$$ βήματα για να βρούμε τον όρο $$C^k$$ του πολυωνύμου.  


Μία ενδεικτική υλοποίηση παρουσιάζεται παρακάτω:
```c++
//https://pdp-archive.github.io/24-PDP/c-minpali-statement
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <map>
#include <cmath>

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
map<char,int> 	CO;	//compress input chars

typedef unsigned long long hasht;
const hasht	MOD = hasht(1e9)+7;	//It is imperative that MOD*MOD fit hasht typedef

long 		C = 0;	//factor for rabin karp poly. Has to be > number of chars

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

hasht right[MAXN/2+2];//right[i] = hash of substr that ends at [N-i] with length i	
	//typical memory usage for sizeof(hasht)==8 is less than 40Mbytes
	//so we are withing allowed limit provided that the only other array
	//is of 10Mbytes the S[] array
	
int main(){
#ifdef CONTEST
	freopen("minpali.in", "r",stdin);
	freopen("minpali.out","w",stdout);
#endif
	scanf("%ld %s",&N,S);
	for(long i=0;i<N;++i){//compress values
		int& cv = CO[S[i]];
		if(cv == 0)
			cv = CO.size() + 1;
		S[i] = cv;
	}
	C = long(CO.size()+1);
	
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

	hasht 	left 	 = 0;
	long 	leftend  = N/2-1, length = N/2;
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
		//right substr starts in [leftend + 1 + haspivot] and has length
		
		if(haspivot){
			//roll left substr 1 to the right. length not changed
			//first step: remove maximum powered character
			assert(N-1-length+1 == leftend+2);//right substr starts right after pivot
			left = (left - (powC(length-1) * S[leftend-length+1])%MOD + MOD) % MOD;
			//shift remaining value and add newbie character
			left = ((left * C) % MOD + S[++leftend]) % MOD;
		} else {
			//shrink left edge of left substr by one
			assert(N-1-length+1 == leftend+1);//right substr starts right after leftend
			left = (left - (powC(length-1) * S[leftend-length+1])%MOD + MOD) % MOD;
			length--;
		}
		haspivot = !haspivot;
	}
	
	printf("%ld\n",ans);
	return 0;
}

```

Αντί για υπόλοιπα διαιρέσεων μπορούμε να χρησιμοποιήσουμε δυαδική λογική και να χρησιμοποιήσουμε για $$\mathit{MOD\_VAL}$$ δύναμη του $$2$$ οπότε το υπόλοιπο βρίσκεται αν κάνουμε δυαδικό $$AND$$ με τα bits των $$\mathit{MOD\_VAL}-1$$ και του $$\mathit{hash}$$ value που θέλουμε να βρούμε το υπόλοιπό του. Στο παρακάτω πρόγραμμα εμφανίζεται η λύση με $$\mathit{MOD} = \mathit{MOD\_VAL}-1$$ όπου $$\mathit{MOD\_VAL}$$ είναι το $$2^{32}$$. Προσοχή ο $$C$$ πρέπει να είναι σχετικά πρώτος με το $$\mathit{MOD\_VAL}$$ άρα ο $$C$$ δεν μπορεί να  είναι άρτιος.  
Μία ενδεικτική υλοποίηση παρουσιάζεται παρακάτω:

```c++
//https://pdp-archive.github.io/24-PDP/c-minpali-statement
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <map>
#include <cmath>

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
map<char,int> 	CO;	//compress input chars

typedef unsigned long long hasht;
const hasht	MOD_VAL = hasht(1)<<32;
const hasht	MOD = hasht(0xffffffff);	//It is imperative that MOD*MOD fit hasht typedef

long 		C = 0;	//factor for rabin karp poly. Has to be > number of chars

hasht powC(long n){	
	//O(log2N) calc power of C (not enough mem to store all values in array)
	//binary lifting to calc value of pow(C,n) in log2(n)
	static hasht _pow[32];
	static long sz = 0;
	if(sz == 0){//precompute powers of C array
		sz = ceil(log2(N/2));
		_pow[0] = C;
		for(long i=1; i<=sz; ++i)
			_pow[i] = (_pow[i-1] * _pow[i-1]) & MOD;
	}
	hasht z = 1;
	for(long i = sz; i>=0; --i)
		if(n & (1l<<i))
			z = (z * _pow[i]) & MOD;
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

hasht right[MAXN/2+2];//right[i] = hash of substr that ends at [N-i] with length i	
	//typical memory usage for sizeof(hasht)==8 is less than 40Mbytes
	//so we are withing allowed limit provided that the only other array
	//is of 10Mbytes the S[] array
	
int main(){
#ifdef CONTEST
	freopen("minpali.in", "r",stdin);
	freopen("minpali.out","w",stdout);
#endif
	scanf("%ld %s",&N,S);
	for(long i=0;i<N;++i){//compress values
		int& cv = CO[S[i]];
		if(cv == 0)
			cv = CO.size() + 1;
		S[i] = cv;
	}
	C = long(CO.size()+1) | 1;
	if(!(C&1))C++;//need to be odd at least
	
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

	//calc reverse hashes for every i in [1,N/2] for
	//substr starting from N-i and length i
	//This is the rightmost substr of palindrome.
	//The max powered element is the rightmost (Rabin Karp polynomial expr)
	//The min powered element is the leftmost (Rabin Karp polynomial expr)
	hasht val = 0;
	for(long i=1;i<=N/2;++i){
		val = (val * C) & MOD;//shift prev substr (create space)
		val = (val + S[N-i]) & MOD;//add newbie to space created
		right[i] = val;
	}

	hasht 	left 	 = 0;
	long 	leftend  = N/2-1, length = N/2;
	bool 	haspivot = (N&1);

	//calc the first subst of palindrome
	for(long i = 0; i<=leftend; ++i)
		left = (((left * C) & MOD) + S[i]) & MOD;

	for(ans=bestcase; ans<=worstcase; ++ans){
		dprintf("ans=%ld, left=%lld, right[%ld]=%lld, length=%ld leftend=%ld haspivot=%d\n",
			ans,left,length,right[length],length,leftend,haspivot);
		
		if(left == right[length] /*&& doublecheck(leftend,length)*/)
			break;
			
		//left substr in [leftend - length + 1, leftend]
		//right substr starts in [leftend + 1 + haspivot] and has length
		
		if(haspivot){
			//roll left substr 1 to the right. length not changed
			//first step: remove maximum powered character
			assert(N-1-length+1 == leftend+2);//right substr starts right after pivot
			left = (left - ((powC(length-1) * S[leftend-length+1])&MOD) + MOD_VAL) & MOD;
			//shift remaining value and add newbie character
			left = (((left * C) & MOD) + S[++leftend]) & MOD;
		} else {
			//shrink left edge of left substr by one
			assert(N-1-length+1 == leftend+1);//right substr starts right after leftend
			left = (left - ((powC(length-1) * S[leftend-length+1])&MOD) + MOD_VAL) & MOD;
			length--;
		}
		haspivot = !haspivot;
	}
	
	printf("%ld\n",ans);
	return 0;
}

```

  
## Βέλτιστη λύση - $$\mathcal{O}(N)$$

Γνώσεις που θα χρειαστούμε: **Knuth–Morris–Pratt algorithm** ([wikipedia](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm))


Μία ενδεικτική υλοποίηση παρουσιάζεται παρακάτω:

```c++
```


## Κώδικας διαγωνιζομένων   
Ο παρακάτω κώδικας ανοίκει στον Κηπουρίδη Ευάγγελο του 11ου ΓΕΛ Θεσσαλονίκης και πέρασε όλα τα test case:

```c++
/*
USED : pdp24u11
TASK : minpali
LANG : C++
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
using namespace std;
#define MAXC 10000005
#define mp make_pair
#define INF 0x3f3f3f3f
#define X first
#define Y second
typedef long long llint;
typedef pair<int,int> pii;
int N, F[MAXC];
char str[MAXC], rev[MAXC];

void Read() {
	int i;
	scanf ("%d %s\n", &N, str);
	for ( i=0; i<N; ++i ) {
		rev[i] = str[N-i-1];
	}
}

void Prefix () {
	int i, j;
	F[0] = F[1] = 0;
	for ( i=2; i<=N; ++i ) {
		j = F[i-1];
		while ( 1 ) {
			if ( rev[i-1] == rev[j] ) {
				F[i] = j+1;
				break;
			}
			else if ( j==0 ) {
				F[i] = j;
				break;
			}
			else {
				j = F[j];
			}
		}
	}
}
void KMP () {
	int i=0, j=0;
	while ( 1 ) {
		if ( i==N ) {
			break;
		}
		if ( str[i] == rev[j] ) {
			++i;
			++j;
		}
		else if ( j==0 ) {
			++i;
		}
		else {
			j = F[j];
		}
	}
	printf ("%d\n", 2*N - j );
}

int main ( void ) {
	#ifdef D
		freopen ("input","r",stdin);
	#endif
	freopen ("minpali.in","r",stdin);
	freopen ("minpali.out", "w", stdout );
	Read();
	Prefix();
	KMP();
	return 0;
}
```
