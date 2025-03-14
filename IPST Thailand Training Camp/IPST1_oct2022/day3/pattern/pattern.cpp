#include <bits/stdc++.h>
#include "pattern.h"
using namespace std;
typedef long long ll;

vector<int> adj[200001];
ll dp[200001][3];
const ll mod=1e9+7;
int c[200001];

int dfs(int x, int par) {
    if (c[x]!=-1)
}

int total_pattern(int N, int M, vector<vector<int> >Path, vector<vector<int> >P) {
    memset(c,-1,sizeof(c));

    for (auto s : Path) {
        adj[s[0]].push_back(s[1]);
        adj[s[1]].push_back(s[0]);
    }

    for (auto s : P) c[s[0]]=s[1];

    if (adj[0].size()==1) { //mmin is 1

        if (P.size()==0) return M;
        else {
            int col=P[0];
            bool can=true;
            for (auto s : P) {
                if (s!=col) can=false;
            }

            if (can) return 1;
            else return 0;
        }


    } else {

        if (P.size()==0) {
            if (M==1) return 1;
            else return (2*M*(M-1)+M)%mod;
        }

        else {



        }
    }
}

