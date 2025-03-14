#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

int n;
vector<pii> v;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=0; i<n; ++i) {
        ll a; cin>>a;
        ll cnt=1;
        while (a%2==0) a/=2, cnt*=2;
        v.push_back(pii(cnt,a));
    }
    for (int i=1; i<n; ++i) v[i].first+=v[i-1].first;
    int q; cin>>q;
    while (q--) {
        ll x; cin>>x;
        cout<<(*upper_bound(v.begin(),v.end(),pii(x,-INT_MAX))).second<<"\n";
    }
}