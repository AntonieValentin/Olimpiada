// Autor: Cătălin Frâncu
// Complexitate: O(n·k).
#include <stdio.h>
 
const int MAX_N = 2'000;
const long long MOD = 99'041;
 
int f[MAX_N + 1]; // f[i] = numărul de discuri cu diametrul i
int comb[MAX_N + 1][MAX_N + 1];
// d[i][j] = numărul de moduri de a așeza discurile de diametre i...n pe exact
// j tije.
int d[MAX_N + 2][MAX_N + 1];
int n, k;
 
void read_data() {
  FILE* fin = fopen("hanoi.in", "r");
  int phi;
 
  fscanf(fin, "%d %d", &n, &k);
  for (int i = 0; i < n; i++) {
    fscanf(fin, "%d", &phi);
    f[phi]++;
  }
  fclose(fin);
}
 
void precompute_comb() {
  for (int i = 0; i <= k; i++) {
    comb[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
    }
  }
}
 
void dyn_prog() {
  d[n + 1][0] = 1;
  for (int i = n; i >= 1; i--) {
    for (int j = f[i]; j <= k; j++) {
      // Ocupăm p dintre tijele deja ocupate și f[i] - p tije noi. Deoarece
      // ajungem la j tije ocupate, înseamnă că discurile de diametre i+1...n
      // stăteau pe exact j - f[i] + p tije.
      long long sum = 0;
      for (int p = 0; p <= f[i]; p++) {
        sum += (long long)d[i + 1][j - f[i] + p] * // discurile existente
          comb[j - f[i] + p][p] * // moduri de a alege tijele deja ocupate
          comb[k - j + f[i] - p][f[i] - p]; // moduri de a alege tijele noi
      }
      d[i][j] = sum % MOD;
    }
  }
}
 
void write_answer() {
  FILE* f = fopen("hanoi.out", "w");
  fprintf(f, "%d\n", d[1][k]);
  fclose(f);
}
 
int main() {
  read_data();
  precompute_comb();
  dyn_prog();
  write_answer();
 
  return 0;
}