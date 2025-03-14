#include <bits/stdc++.h>
using namespace std;

ll power(ll a, ll m) { //a^m;
    ll ans=1;
    while (m) {
        if (m%2==1) ans=(ans*a)%mod;
        a=(a*a)%mod;
        m/=2;
    }
    return ans;
}

void build(int l, int r, int idx) {
    if (l==r) {

    } else {
        int mid=(l+r)/2;
        build(l,mid,2*idx);
        build(mid+1,r,2*idx+1);

    }
}



int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
}
