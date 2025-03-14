#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<vector<ll>,ll> pii;

int n;
string s;
ll dp[2505][2505],nxt[2505],a,b,c,qs[4][2505],mod=1e9+7,hs[4],inv[4],mul[4][2505];

ll power(ll a, ll n) {
    ll ans=1;
    while (n) {
        if (n%2==1) ans=(ans*a)%mod;
        a=(a*a)%mod;
        n/=2;
    }
    return ans;
}

vector<ll> hsh(int l, int r) {
    vector<ll> res;
    for (int x=0; x<2; ++x) res.push_back(((qs[x][r]-qs[x][l-1]+mod)%mod * power(inv[x],l-1))%mod);
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    for (int i=1; i<=2500; ++i) for (int j=1; j<=2500; ++j) dp[i][j]=1e18;
    cin>>n>>s>>a>>b>>c;
    s=" "+s;

    hs[0]=911;
    hs[1]=5e6+11;

    for (int x=0; x<2; ++x) {
        mul[x][0]=1;
        inv[x]=power(hs[x],mod-2);
        for (int i=1; i<n; ++i) mul[x][i]=(mul[x][i-1]*hs[x])%mod;
        for (int i=1; i<=n; ++i) qs[x][i]=(qs[x][i-1]+mul[x][i-1]*(s[i]-'a'))%mod;
    }

    for (ll siz=1; siz<=n;  ++siz) {

        //find next
        map<vector<ll>,int> bef;
        queue<pii> q;
        memset(nxt,0,sizeof(nxt));

        for (int l=n-siz+1; l>=1; --l) {
            int r=l+siz-1;
            while (q.size()>=siz)  {
                bef[q.front().first]=q.front().second;
                q.pop();
            }
            nxt[l]=bef[hsh(l,r)];
            q.push(pii(hsh(l,r),l));
        }

        //find dp
        for (ll l=1; l+siz-1<=n; ++l) {
            ll r=l+siz-1;
            if (siz==1) dp[l][r]=a;
            else dp[l][r]=min({dp[l][r],dp[l][r-1]+a,dp[l+1][r]+a});

            ll nl=l,nr=r,cnt=0;
            while (nl) {
                ++cnt;
                dp[l][nr]=min(dp[l][nr],dp[l][r]+ ((nr-l+1)-siz*cnt)*a+b+c*cnt);
                nl=nxt[nl];
                nr=nl+siz-1;
            }
        }
    }
    cout<<dp[1][n];
}