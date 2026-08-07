// Antonie Aureliu Valentin, Facultatea de Automatica si Calculatoare, UNSTPB
#include <bits/stdc++.h>   
#define nmax 2000000   
using namespace std;   
      
ifstream fin("pinball.in");   
ofstream fout("pinball.out");   
      
int ciur[nmax+1];   
int n, x, total; 
int prim[148934];   
int nrprimes;  
int c;   
int main(){   
for(int i = 2; i * i <= nmax; i++)   
{   
    if(ciur[i] == 0)   
    {   
        prim[nrprimes++] = i;   
        for (int j = i; j <= nmax; j += i)   
        {   
            ciur[j] = i;   
        }   
    }   
}   
fin>>c>>n>>total;   
int sum = 0;   
for (int i = 1; i <= n; i++){   
    fin>>x;   
    int nrdiv = 1;   
    while(ciur[x]){   
        int d = ciur[x];   
        int p = 0;   
        while(x % d == 0){   
            x /= d;   
            p++;   
        }   
        nrdiv *= (p + 1);   
      
    }   
    if (x != 1)   
        nrdiv *= 2;   
    sum += nrdiv;   
}   
x = total - sum;  
if (c == 1)   
    fout << x << "\n";   
int index = 0;   
long long val = 1;   
while(ciur[x]){   
    int d = ciur[x];   
    int p = 0;   
    while(x % d == 0){   
        x /= d;   
        p++;   
        val *= pow(prim[index], d - 1);   
        index++;   
    }   
      
}   
if (x != 1){   
    val *= pow(prim[index], x - 1);   
}  
if (c == 2)   
    fout << val << "\n";   
    return 0;   
}