// Antonie Aureliu Valentin, Facultatea de Automatica si Calculatoare, UNSTPB
// Complexitate: O(n*k).
#include <bits/stdc++.h>   
#define mod 99041   
using namespace std;   
      
ifstream fin("hanoi.in");   
ofstream fout("hanoi.out");   
        
int n, K, x, c[2001][2001], fr[2001];   
long long total;   
long long prodi;

// precalculez toate combinarile folosind triunghiul lui Pascal   
void combinari(){   
    for (int i = 1; i <= K; i++){   
        c[i][i] = 1;   
        c[i][0] = 1;   
    }   
    for (int i = 1; i <= K; i++){   
        for (int j = 1; j < i; j++){   
            c[i][j] = c[i-1][j-1] + c[i-1][j];   
            if (c[i][j] >= mod)     
                c[i][j] -= mod;   
        }   
    }   
}   

int main(){   
    fin>>n>>K;
    // fr[x] = frecventa de aparitie a unui disc de diametru x   
    for (int i = 1; i <= n; i++){   
        fin>>x;   
        fr[x]++;   
    }
    combinari();   
    for (int i = K; i >= 1; i--){
        // calculez pentru fiecare i prodi = numarul de moduri de a aseza discurile pe cel mult i tije
        // => K - i tije nu pot fi folosite   
        prodi = 1; 
        for (int j = 1; j <= n; j++){   
            if (fr[j]){
                // discurile trebuie sa fie ordonate strict crescator dupa diametru pe fiecare tija
                // prin urmare, discurile de acelasi diametru trebuie puse pe tije diferite   
                prodi *= c[i][fr[j]];   
                prodi %= mod;
            }   
        }
        // pentru un i arbitrar exista c[K][K-i] moduri de a fixa cele K - i tije libere
        prodi *= c[K][K-i]; 
        // principiul includerii si excluderii
        total += prodi * ((K - i) % 2 == 0 ? 1 : -1);  
        total = (total % mod + mod) % mod;   
    }
    fout << total;   
       
    return 0;   
}