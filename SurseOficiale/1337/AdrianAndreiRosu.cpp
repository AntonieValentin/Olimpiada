// Rosu Adrian Andrei, Facultatea de Automatica si Calculatoare, UNSTPB
/*

	Solutie oficiala 1337 O(N*logN) feat. smenul lui Mars si doua cautari binare

*/

#include <bits/stdc++.h>
#define int long long
#define DIM 100001
#define right iuehfur
#define left eifuherf

using namespace std;

ifstream fin("1337.in");
ofstream fout("1337.out");

unordered_map < int, vector <int> > f;

vector <int> indicies;

vector < vector <int> > nf;

int v[DIM], mars[DIM];
int n, k, p, sum, target, maximum, left, right, ret, idx;

void solve(int target, int pos)
{
    int aux = pos;
    int l = 0, r = indicies.size() - 1;
    int limit = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (indicies[mid] <= pos) {
            limit = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    if (limit < 0) {
        return ;
    }
    pos = indicies[limit];
    l = 0, r = f[target].size() - 1;
    limit = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (f[target][mid] <= pos) {
            limit = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    if (limit < 0) {
        return ;
    }
    limit = f[target][limit];
    pos = aux;
    if(pos - limit + 1 < right - left + 1) {
        right = pos;
        left = limit;
    }

}

int32_t main(void)
{
    fin >> n >> k >> p;
    for (int i = 1; i <= n; i++) {
        fin >> v[i];
    }
    ret = -1e18;
    f[0].push_back(1);
    for (int i = 1; i <= n; i++) {
        sum = (sum + v[i]) % k;
        sum = (sum + k) % k;
        target = (sum - p + k) % k;
        if (!f[target].size()) {
            f[sum].push_back(i + 1);
            continue;
        }
        mars[i + 1]--;
        mars[f[target][0]]++;
        f[sum].push_back(i + 1);

    }
    for (int i = 1; i <= n; i++) {
        mars[i] += mars[i - 1];
        if (mars[i]) {
            if (v[i] > ret) {
                ret = v[i];
                indicies.clear();
                indicies.push_back(i);
            } else if (v[i] == ret) {
                indicies.push_back(i);
            }
        }
    }
    if (!indicies.size()) {
        fout << "Nu exista\n";
        return 0;
    }
    right = 1e9;
    sum = 0;
    for (int i = 1; i <= n; i++) {
        sum = (sum + v[i]) % k;
        sum = (sum + k) % k;
        target = (sum - p + k) % k;
        solve(target, i);
    }
    fout << ret << "\n" << left << " " << right << "\n";
    return 0;
}