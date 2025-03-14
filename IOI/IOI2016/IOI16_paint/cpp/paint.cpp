#include "paint.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

struct node {
    int n,k,mode;
};

int n,m,bef[200005],mark[200010];
bool dp[200010][105][2],canX[200010],canY[200010];
string ans;
bool vis[200005][105][2], type[200005][105][2];

string solve_puzzle(string s, vector<int> c) {
    n=s.size();
    m=c.size();
    int before=0;
    s=" "+s;

    for (int i=1; i<=n; ++i) {
        if (s[i]=='_') before=i;
        bef[i]=before;
    }

    dp[0][0][0]=true;
    for (int i=1; i<=n; ++i) {
        for (int j=0; j<=m; ++j) {
            if (s[i]!='X') {
                if (dp[i-1][j][0]) {
                    dp[i][j][0]=true;
                    type[i][j][0]=true;
                }

                if (j && dp[i-1][j-1][1]) {
                    dp[i][j][0]=true;
                    type[i][j][1]=true;
                }
            }
            if (s[i]!='_') {
                if (i-bef[i]>=c[j] && i>=c[j] && dp[i-c[j]][j][0] && j<m) {
                    dp[i][j][1]=true;
                }
            }
        }
    }

    queue<node> q;
    if (dp[n][m][0]) q.push({n,m,0});
    if (dp[n][m-1][1]) q.push({n,m-1,1});

    while (!q.empty()) {
        int a=q.front().n, b=q.front().k, mode=q.front().mode;
        q.pop();

        if (vis[a][b][mode]) continue;
        vis[a][b][mode]=true;

        if (mode==0) {
            canY[a]=true;
            if (type[a][b][0]) q.push({a-1,b,0});
            if (type[a][b][1]) q.push({a-1,b-1,1});
        }

        if (mode==1) {
            ++mark[a-c[b]+1];
            --mark[a+1];
            q.push({a-c[b],b,0});
        }
        
    }

    for (int i=1; i<=n; ++i) {
        mark[i]+=mark[i-1];
        if (mark[i]) canX[i]=true;
    }

    for (int i=1; i<=n; ++i) {
        if (s[i]=='X') ans+='X';
        else if (s[i]=='Y') ans+='Y';
        else {
            if (canX[i] && canY[i]) ans+='?';
            else if (canX[i]) ans+='X';
            else if (canY[i]) ans+='_';
        }
    }
    return ans;
}
