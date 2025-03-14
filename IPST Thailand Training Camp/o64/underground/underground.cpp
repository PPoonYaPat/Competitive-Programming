#include "underground.h"
#include <bits/stdc++.h>
#include "grader.cpp"
using namespace std;

struct node {
    int dis,R,C;
    bool operator < (const node &o) const {
        return dis>o.dis;
    }
};

int r,c,dp[17][501][501],a[501][501];

void dij(int mask) {
    bool vis[501][501];
    priority_queue<node> q;

    for (int i=0; i<r; ++i) {
        for (int j=0; j<c; ++j) {
            vis[i][j]=false;

            if (dp[mask][i][j]==1e9+10) continue;
            node k={mask,i,j};
            if (k.R!=0 && dp[mask][k.R-1][k.C]+a[k.R][k.C]<dp[mask][k.R][k.C]) continue;
            if (k.R!=r-1 && dp[mask][k.R+1][k.C]+a[k.R][k.C]<dp[mask][k.R][k.C]) continue;
            if (k.C!=0 && dp[mask][k.R][k.C-1]+a[k.R][k.C]<dp[mask][k.R][k.C]) continue;
            if (k.C!=c-1 && dp[mask][k.R][k.C+1]+a[k.R][k.C]<dp[mask][k.R][k.C]) continue;

            q.push({dp[mask][i][j],i,j});
        }
    }

    while (!q.empty()) {
        node k=q.top();
        q.pop();

        if (vis[k.R][k.C]) continue;
        vis[k.R][k.C]=true;


        if (k.R!=0 && dp[mask][k.R-1][k.C]>dp[mask][k.R][k.C]+a[k.R-1][k.C]) {
            dp[mask][k.R-1][k.C]=dp[mask][k.R][k.C]+a[k.R-1][k.C];
            q.push({dp[mask][k.R-1][k.C],k.R-1,k.C});
        }

        if (k.R!=r-1 && dp[mask][k.R+1][k.C]>dp[mask][k.R][k.C]+a[k.R+1][k.C]) {
            dp[mask][k.R+1][k.C]=dp[mask][k.R][k.C]+a[k.R+1][k.C];
            q.push({dp[mask][k.R+1][k.C],k.R+1,k.C});
        }

        if (k.C!=0 && dp[mask][k.R][k.C-1]>dp[mask][k.R][k.C]+a[k.R][k.C-1]) {
            dp[mask][k.R][k.C-1]=dp[mask][k.R][k.C]+a[k.R][k.C-1];
            q.push({dp[mask][k.R][k.C-1],k.R,k.C-1});
        }

        if (k.C!=c-1 && dp[mask][k.R][k.C+1]>dp[mask][k.R][k.C]+a[k.R][k.C+1]) {
            dp[mask][k.R][k.C+1]=dp[mask][k.R][k.C]+a[k.R][k.C+1];
            q.push({dp[mask][k.R][k.C+1],k.R,k.C+1});
        }
    }
}

int dig_paths(int R, int C, std::vector<std::vector<int>> &A) {
    r=R; c=C;
    for (int mask=0; mask<16; ++mask) for (int i=0; i<r; ++i) for (int j=0; j<c; ++j) dp[mask][i][j]=1e9+10, a[i][j]=A[i][j];
    dp[1<<0][0][0]=a[0][0];
    dp[1<<1][0][c-1]=a[0][c-1];
    dp[1<<2][r-1][0]=a[r-1][0];
    dp[1<<3][r-1][c-1]=a[r-1][c-1];


    for (int mask=1; mask<16; ++mask) {
        for (int i=0; i<4; ++i) {
            if (!mask&(1<<i)) continue;

            for (int j=0; j<r; ++j) {
                for (int k=0; k<c; ++k) {
                    dp[mask][j][k]=min(dp[mask][j][k],dp[(1<<i)][j][k]+dp[mask^(1<<i)][j][k]-a[j][k]);
                }
            }
        }
        dij(mask);
    }

    int ans=INT_MAX;
    for (int i=0; i<r; ++i) for (int j=0; j<c; ++j) ans=min(ans,dp[15][i][j]);
    return ans;
}
/*
5 6
1 20 20 25 50 1
2 1 45 4 1 1
65 1 67 2 50 1
3 1 2 1 52 3
1 95 85 25 57 1
*/
