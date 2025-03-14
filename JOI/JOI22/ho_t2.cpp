#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,m,a[300005],b[300005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for (int i=1; i<=n; ++i) cin>>a[i];
    for (int i=1; i<=n; ++i) cin>>b[i], a[i]=max(a[i],b[i]);

    ll l=0,r=1e18;
    while (l<r) {
        ll mid=(l+r+1)/2;
        long double fre=0,want=0;
        for (int i=1; i<=n; ++i) {
            ll use=(mid+a[i]-1)/a[i];
            if (use<=m) fre+=(m-use);
            else want+=(mid-m*a[i]+b[i]-1)/b[i];
        }
        if (fre>=want) l=mid;
        else r=mid-1;
    }
    cout<<l;
}