#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll const mod=1e9+7;
ll dp[505][505];
int n;
string c;

ll check(char a, char b) {
    if (a=='(' && b==')') return 1;
    else if (a=='[' && b==']') return 1;
    else if (a=='(' && b=='?') return 1;
    else if (a=='?' && b==')') return 1;
    else if (a=='[' && b=='?') return 1;
    else if (a=='?' && b==']') return 1;
    else if (a=='?' && b=='?') return 2;
    else return 0;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>c;

    for (int i=1; i<n; ++i) dp[i][i-1]=1;

    for (int i=1; i<n; ++i) {
        for (int j=0; j+i<n; ++j) {
            int l=j, r=i+j;

            dp[l][r]=(check(c[l],c[r])*dp[l+1][r-1])%mod;

            for (int k=l+1; k<=r-2; ++k) {
                dp[l][r]=(dp[l][r]+check(c[l],c[k])*dp[l+1][k-1]*dp[k+1][r])%mod;
            }

        }
    }

    cout<<dp[0][n-1];
}

