#include <algorithm>
#include <cstdio>
#include <unordered_set>

const size_t MAXN = 1'000'000;
long A[MAXN];

int main() {
   FILE *fi = fopen("chemicals.in", "r");
   long N, K;
   fscanf(fi, "%ld%ld", &N, &K);
   for (long i = 0; i < N; ++i) {
      fscanf(fi, "%ld", &A[i]);
   }
   fclose(fi);
   
   long max_range = 0;
   // Δοκιμάζουμε όλα τα δυνατά διαστήματα [i, j].
   for (long i = 0; i < N; ++i) {
      std::unordered_set<long> modula;
      bool found_pair = false;
      long k;
      for (k = i; k < N; ++k) {
         if (modula.find( (K - (A[k] % K) ) % K ) != modula.end()) {
            found_pair = true;
            break;
         }
         modula.insert(A[k] % K);
      }
      max_range = std::max(max_range, k - i);
   }
   
   FILE *fo = fopen("chemicals.out", "w");
   fprintf(fo, "%ld\n", max_range);
   fclose(fo);
   
   return 0;
}
