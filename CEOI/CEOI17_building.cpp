#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct line {
    ll slope,con;
} s[1<<22];

ll f(line a, ll x) {
    return a.slope*x+a.con;
}

int n,mx=1000000;
ll h[100001],w[100001],sum,dp[100001];

void add(line a, int l, int r, int idx) {
    int mid=(l+r)/2;
    bool m = f(a,mid) < f(s[idx],mid);
    bool lef = f(a,l) < f(s[idx],l);

    if (m) swap(s[idx],a);

    if (r-l==1) return;
    else if (lef!=m) add(a,l,mid,2*idx);
    else add(a,mid,r,2*idx+1);
}

ll query(int l, int r, int idx, int x) {
    int m=(l+r)/2;
    if (r-l==1) return f(s[idx],x);
    else if (x<m) return min(f(s[idx],x),query(l,m,2*idx,x));
    else return min(f(s[idx],x),query(m,r,2*idx+1,x));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=1; i<=n; ++i) cin>>h[i];
    for (int i=1; i<=n; ++i) cin>>w[i], sum+=w[i];

    dp[1]=-w[1];
    for (int i=0; i<(1<<22); ++i) s[i]={-2*h[1],dp[1]+h[1]*h[1]};
    for (int i=2; i<=n; ++i) {
        dp[i]=query(0,mx,1,h[i])+h[i]*h[i]-w[i];
        add({-2*h[i],dp[i]+h[i]*h[i]},0,mx,1);
    }
    cout<<dp[n]+sum;
}