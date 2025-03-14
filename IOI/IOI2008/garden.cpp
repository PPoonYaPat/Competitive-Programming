#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,mod,ans;
string s;

ll power(ll a, ll n) {
    ll res=1;
    while (n) {
        if (n%2==1) res=(res*a)%mod;
        a=(a*a)%mod;
        n/=2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>mod>>s;

    int dif=2,mmax=2,mmin=2;

    for (int i=0; i<n; ++i) {
        if (s[i]=='P' && dif<=mmin+1) { //consider if P change to L

            int ma=max(mmax,dif+1), mi=mmin;

            if (ma-mi==2) {
                if (dif==mi) ans=(ans+power(2,(n-i)/2))%mod; //dif+1 is on the center of the strip
                else ans=(ans+power(2,(n-i-1)/2))%mod;

            } else {
                ans=(ans+power(2,(n-i)/2)+power(2,(n-i-1)/2)-1)%mod;
            }
        }

        if (s[i]=='L') ++dif;
        else --dif;
        mmax=max(mmax,dif);
        mmin=min(mmin,dif);
    }
    cout<<(ans+1)%mod;
}