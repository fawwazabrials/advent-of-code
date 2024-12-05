#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v1, v2;
    int nv1, nv2;
    while (cin >> nv1 >> nv2) {
        v1.push_back(nv1);
        v2.push_back(nv2);
    }

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    int ans = 0;
    for (int i=0; i<v1.size(); i++) {
        ans += abs(v1[i] - v2[i]);
    }

    cout << ans << '\n';

    return 0;
}