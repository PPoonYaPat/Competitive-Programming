#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mod=1e9+7;

void solve() {
    ll x; cin>>x;
    if (x==1 || x==2) cout<<"NO\n";
    else cout<<(x-3)%mod<<"\n";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t;
    while (t--) solve();
}
