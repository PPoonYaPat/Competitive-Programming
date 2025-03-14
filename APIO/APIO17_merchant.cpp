#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,m,h;
ll profit[101][101],dis[101][101],buy[101][1001],sell[101][1001],dist[101][101];

bool solve(ll s) {
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) {
            if (dis[i][j]!=1e15) {
                dist[i][j]=dis[i][j]*s-profit[i][j];
            } else dist[i][j]=1e15;
        }
    }
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) {
            for (int k=1; k<=n; ++k) {
                dist[j][k]=min(dist[j][k],dist[j][i]+dist[i][k]);
            }
        }
    }
    for (int i=1; i<=n; ++i) {
        if (dist[i][i]<=0) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m>>h;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=h; ++j) cin>>buy[i][j]>>sell[i][j];
    }

    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) {
            dis[i][j]=1e15;
            for (int k=1; k<=h; ++k) if (sell[j][k]!=-1 && buy[i][k]!=-1)
                profit[i][j]=max(profit[i][j],sell[j][k]-buy[i][k]);
        }
    }

    for (int i=0; i<m; ++i) {
        int a,b,w; cin>>a>>b>>w;
        dis[a][b]=w;
    }

    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) {
            for (int k=1; k<=n; ++k) {
                dis[j][k]=min(dis[j][k],dis[j][i]+dis[i][k]);
            }
        }
    }

    ll l=1, r=1e9, ans=0;
    while (l<=r) {
        int mid=(l+r)/2;
        if (solve(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<ans;
}
