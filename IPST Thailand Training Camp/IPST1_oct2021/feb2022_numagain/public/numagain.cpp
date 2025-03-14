#include "numagain.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cnt[2001],val[2001],a[2001],qs[2001];
ll b[2001],dp[2001][2001];
const ll mod=1e9+7;

ll power(ll a, ll k) {
    ll ans=1;
    while (k) {
        if (k%2==1) ans=(ans*a)%mod;
        a=(a*a)%mod;
        k/=2;
    }
    return ans;
}

int find_ans(vector<int> number) {
    for (auto s : number) ++cnt[s];
    int idx=0;
    for (int i=1; i<=2000; ++i) {
        if (cnt[i]) {
            ++idx;
            a[idx]=cnt[i];
            val[idx]=i;
        }
    }

    for (int i=1; i<=idx; ++i) qs[i]=qs[i-1]+a[i], b[i]=power(2,a[i])-1;

    for (int i=1; i<idx; ++i) {
        dp[i][i+1]=2;
        for (int j=i+1; j<idx; ++j) { //find dp[i][j+1]
            dp[i][j+1] = (dp[i][j] + b[j]*(dp[i][j] + power(2,qs[j-1]-qs[i]))%mod)%mod;
        }
    }

    ll ans=0;
    for (int i=1; i<idx; ++i) {
        for (int j=i+1; j<=idx; ++j) ans=(ans + b[i] * b[j]%mod * (val[j]-val[i])%mod *dp[i][j]%mod) %mod;
    }
    return ans%mod;
}
