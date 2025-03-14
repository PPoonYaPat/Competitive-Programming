#include "traffic.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,ans_node;
ll sum,ans=4e18,p[1000001];
vector<int> adj[1000001];

ll dfs(int x, int par) {
    ll cnt=p[x],mmax=0;

    for (auto s : adj[x]) {
        if (s==par) continue;
        ll cnt_child=dfs(s,x);
        cnt+=cnt_child;
        mmax=max(mmax,cnt_child);
    }
    mmax=max(mmax,sum-cnt);
    if (mmax<ans) {
        ans=mmax;
        ans_node=x;
    }
    return cnt;
}

int LocateCentre(int N, int P[], int S[], int D[]) {
    n=N;
    for (int i=0; i<n-1; ++i) {
        adj[S[i]].push_back(D[i]);
        adj[D[i]].push_back(S[i]);
    }
    for (int i=0; i<n; ++i) sum+=P[i],p[i]=P[i];
    dfs(0,0);
    return ans_node;
}