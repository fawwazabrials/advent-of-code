#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v;
    unordered_map<int, int> m;

    int nv1, nv2;
    while (cin >> nv1 >> nv2) {
        v.push_back(nv1);
        m[nv2]++;
    }

    int ans = 0;
    for (int i=0; i<v.size(); i++) {
        ans += v[i] * m[v[i]];
    }

    cout << ans << '\n';

    return 0;
}