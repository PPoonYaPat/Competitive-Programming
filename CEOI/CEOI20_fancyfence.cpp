#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

const ll mod=1e9+7;
ll w[100005],h[100005],dp[100005],qs[100005];
int n;
stack<pii> st;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=1; i<=n; ++i) cin>>h[i];
    for (int i=1; i<=n; ++i) cin>>w[i], qs[i]=(qs[i-1]+w[i])%mod;

    ll ans=0;
    st.push(pii(0,0));
    for (int i=1; i<=n; ++i) {
        while (st.size() && h[st.top().first]>h[i]) st.pop();
        ll sum=(st.top().second + (h[i]*(h[i]+1)/2)%mod*(qs[i-1]-qs[st.top().first]+mod))%mod;
        dp[i]=( ((h[i]*(h[i]+1)/2)%mod) * ((w[i]*(w[i]+1)/2)%mod) + sum*w[i])%mod;
        st.push(pii(i,(sum+((h[i]*(h[i]+1)/2)%mod)*w[i])%mod));
        ans=(ans+dp[i])%mod;
    }
    cout<<ans<<"\n";
}