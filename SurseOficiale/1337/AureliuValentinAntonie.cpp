// Antonie Aureliu Valentin, Facultatea de Automatica si Calculatoare, UNSTPB
/*

	Solutie oficiala 1337 O(N*logN) cu rmq si cautare binara

*/

#include <bits/stdc++.h>
using namespace std;
ifstream fin("1337.in");
ofstream fout("1337.out");
const int logg = 16;
long long rmq[100001][17],p,put=1,putv[100001],k,v[100001];
unordered_map<long long, vector<long long>> m;
int n, lungime, st = -1,dr, fi,fj, Min=100000, expv[100001];

int main()
{
fin>>n>>k>>p;
putv[1] = 1;
for(int i = 1; i <= n; i++){
    fin>>rmq[i][0];
    v[i] = rmq[i][0];
    if (i != 1){
        expv[i] = expv[i/2] + 1;
        if (expv[i] != expv[i-1])
            put *= 2;
        putv[i] = put;
    }
}
long long Max2 = v[1];
put = 1;
for(int k = 1; k <= logg; k++){
    for(int i = 1; i <= n; i++){
        if(i + put <= n){
        	rmq[i][k] = max(rmq[i][k-1],rmq[i+put][k-1]);
        }
    }
    put <<= 1;
}

long long sum = 0;

m[0].push_back(1);

for (int j = 1; j <= n; j++){
    sum += v[j] % k;
    sum = (sum + k)% k;
    m[sum].push_back(j + 1);
    if (m[(sum - p + k) % k].size()){
        st = m[(sum - p + k) % k][0];
        dr = j;
        lungime = dr - st + 1;
        Max2 = max(Max2, max(rmq[st][expv[lungime]],rmq[dr-putv[lungime] +1][expv[lungime]]));
    }
}
if (st == -1)
    fout << "Nu exista";
else {
    fout << Max2 << "\n";
    long long sum = 0;
    for (int j = 1; j <= n; j++){
        sum += v[j] % k;
        sum = (sum + k)% k;
        // caut binar
        int st = 0;
        int dr = m[(sum - p + k) % k].size() - 1;
        while (st <= dr){
            int mij = (st + dr) >> 1;
            if (m[(sum - p + k) % k][mij] > j)
                dr = mij - 1;
            else{
                int st2 = m[(sum - p + k) % k][mij];
                int dr2 = j;
                lungime = dr2 - st2 + 1;
                if (max(rmq[st2][expv[lungime]],rmq[dr2-putv[lungime] +1][expv[lungime]]) == Max2){
                    if (lungime < Min){
                        Min = lungime;
                        fi = st2;
                        fj = dr2;
                    }
                    st = mij + 1;
                }
                else
                    dr = mij - 1;
            }
        }
    }
    fout << fi << " " << fj << endl;
}
    return 0;
}