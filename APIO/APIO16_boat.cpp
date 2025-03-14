#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod=1e9+7;
ll n,c[1001],st[501],ed[501],cnt,comb[501];
ll dp[501][1001];
set<int> ss;

ll power(ll a, ll m) { //a^m;
    ll ans=1;
    while (m) {
        if (m%2==1) ans=(ans*a)%mod;
        a=(a*a)%mod;
        m/=2;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=1; i<=n; ++i) {
        cin>>st[i]>>ed[i]; --st[i];
        ss.insert(st[i]);
        ss.insert(ed[i]);
    }

    for (int i=1; i<=n; ++i) comb[i]=power(i,mod-2)%mod;

    cnt=ss.size()-1;
    int id=0;
    for (auto it=ss.begin(); it!=ss.end(); ++it) c[id++]=*it;

    for (int i=0; i<=cnt; ++i) dp[0][i]=1;

    for (int i=1; i<=n; ++i) {
        dp[i][0]=1; //don't send any boat

        for (int j=1; j<=cnt; ++j) { //consider from the range from c[j-1]+1 to c[j]
            dp[i][j]=dp[i][j-1];

            ll idx=1,com=1;
            for (auto k=i; k>0; --k) {
                if (st[k]<c[j] && c[j]<=ed[k]) {
                    com=((com*(c[j]-c[j-1]+idx-1)%mod)*comb[idx])%mod;
                    dp[i][j]=(dp[i][j]+dp[k-1][j-1]*com)%mod;
                    ++idx;
                }
            }
        }
    }
    cout<<(dp[n][cnt]-1+mod)%mod;
}