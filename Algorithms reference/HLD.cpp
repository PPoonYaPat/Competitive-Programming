#include <bits/stdc++.h>
using namespace std;

int n,m,c[200001],child[200001],idx[200001],cnt,p[200001],par_group[200001];
vector<int> adj[200001];

void dfs_sum(int x, int par) {
    child[x]=1;
    for (auto s : adj[x]) {
        if (s==par) continue;
        dfs_sum(s,x);
        child[x]+=child[s];
    }
}

void hld(int x, int par, int pg) {
    int mnode=0,mmax=0;
 
    idx[x]=++cnt;
    par_group[x]=pg;
    p[x]=par;
 
    for (auto s : adj[x]) {
        if (s!=par && mmax<child[s]) {
            mmax=child[s];
            mnode=s;
        }
    }
 
    if (mnode) hld(mnode,x,pg);
    for (auto s : adj[x]) {
        if (s==par || s==mnode) continue;
        hld(s,x,s);
    }
}

void solve() {
    int st;
    while (st!=0) {
        //do something on the range par_group[x] to idx[x]+1
        st=p[par_group[st]];
    }
}