#include "aliens.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int n,m,k;
int dp[505][505]; //n,k
vector<pii> v;
set<pii> h;

long long take_photos(int N, int M, int K, vector<int> y, vector<int> x) {
    n=N; m=M; k=K;
    for (int i=0; i<n; ++i) h.insert(pii(x[i],y[i]));
    for (auto u : h) v.push_back(u);
    sort(v.begin(),v.end());

    for (int i=0; i<n; ++i) for (int j=0; j<=k; ++j) dp[i][j]=1e9;
    for (int j=1; j<=k; ++j) dp[0][j]=1;

    for (int i=1; i<v.size(); ++i) {
        for (int j=1; j<=k; ++j) {

            //find dp[i][j]
            if (j==1) {
                dp[i][j]=min(dp[i][j],(v[i].first-v[0].first+1)*(v[i].first-v[0].first+1));
            } else {
                for (int x=1; x<=i; ++x) { //capture i to x
                    dp[i][j]=min(dp[i][j],dp[x-1][j-1]+(v[i].first-v[x].first+1)*(v[i].first-v[x].first+1));
                }
            }

        }
    }

    return dp[v.size()-1][k];
}
