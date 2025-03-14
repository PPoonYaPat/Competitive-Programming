#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,A,B,dp1[2001],dp2[101][101];
ll qs[2001];

bool check(ll x) { //is it able to be equal or less than x
    if (A==1) {
        for (int i=1; i<=n; ++i) {
            dp1[i]=1e9;

            for (int j=1; j<=i; ++j) { //consider sum j to i
                if ((x|(qs[i]-qs[j-1]))==x) dp1[i]=min(dp1[i],dp1[j-1]+1);
            }
        }

        if (dp1[n]<=B) return true;
        else return false;

    } else {

        dp2[0][0]=0;
        for (int i=1; i<=n; ++i) dp2[i][0]=dp2[0][i]=1e9;

        for (int i=1; i<=n; ++i) {
            for (int k=1; k<=B; ++k) {
                //consider dp2[i][k] -> from 1 to i with k ranges

                dp2[i][k]=1e9;
                if (k>i) continue;

                for (int j=1; j<=i; ++j) {
                    if ((x|(qs[i]-qs[j-1]))==x) dp2[i][k]=min(dp2[i][k],dp2[j-1][k-1]+1);
                }
            }
        }

        for (int i=A; i<=B; ++i) if (dp2[n][i]<=B) return true;
        return false;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>A>>B;
    for (int i=1; i<=n; ++i) cin>>qs[i], qs[i]+=qs[i-1];

    ll ans=0;
    for (int i=45; i>=0; --i) {
        if (!check(ans+(1ll<<i)-1)) ans|=(1ll<<i);
    }
    cout<<ans;
}