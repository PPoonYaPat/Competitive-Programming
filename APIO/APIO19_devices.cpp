#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

ll n,A,B,mod,ans;
vector<pll> v;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>A>>B;
    A=A/__gcd(A,B+1);

    if (A>2e18/B || A>2e18/B) mod=2e18;
    else mod=A*B;

    while (n--) {
        ll l,r;
        cin>>l>>r;
        if (r-l+1>=mod) {
            cout<<mod;
            return 0;
        }
        l%=mod;
        r%=mod;

        if (l<=r) v.push_back(pll(l,r));
        else v.push_back(pll(l,mod-1)), v.push_back(pll(0,r));
    }

    sort(v.begin(),v.end());
    ll mmax=-1;
    for (auto s : v) {
        if (mmax<s.first) {
            ans+=(s.second-s.first+1);
            mmax=s.second;
        } else if (s.first<=mmax && mmax<s.second) {
            ans+=(s.second-mmax);
            mmax=s.second;
        }
    }
    cout<<ans;
}