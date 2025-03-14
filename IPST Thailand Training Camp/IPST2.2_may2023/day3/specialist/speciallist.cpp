#include "speciallist.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

struct NN {
    ll ans,sum,cnt;
} s[1<<18];

const ll mod=1e9+7;
const int sq=333,mx=100000;

NN merge(NN a, NN b) {
    NN res;
    res.sum=(a.sum+b.sum)%mod;
    res.cnt=a.cnt+b.cnt;
    res.ans=(a.ans+b.ans+b.sum*a.cnt-a.sum*b.cnt+mod*mod)%mod;
    return res;
}

void update(int l, int r, int idx, ll x, int val) {
    if (x>r || x<l) return;
    if (l==r) {
        s[idx].cnt+=val;
        s[idx].sum=(s[idx].cnt*x*x)%mod;
    } else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,val);
        update(mid+1,r,2*idx+1,x,val);
        s[idx]=merge(s[2*idx],s[2*idx+1]);
    }
}

int n,m,in[100001],out[100001],disc,val[100001];
vector<int> adj[100001];

void dfs(int x) {
    in[x]=++disc;
    for (auto s : adj[x]) dfs(s);
    out[x]=disc;
}

struct NNN {
    int idx,l,r;
    bool operator < (const NNN &o) {
        return pii(l/sq,r)<pii(o.l/sq,o.r);
    }
};

vector<NNN> v;
vector<int> Ans;

vector<int> compute_cost(int N, int M, vector<int> P, vector<int> X, vector<int> Z) {
    n=N; m=M;
    for (int i=1; i<n; ++i) adj[P[i]].push_back(i);
    dfs(0);
    for (int i=0; i<n; ++i) val[in[i]]=X[i], v.push_back({i,in[i],out[i]}), Ans.push_back(0);
    for (int i=0; i<m ; ++i) update(0,mx,1,Z[i],1);
    sort(v.begin(),v.end());

    int l=1,r=1;
    update(0,mx,1,val[1],1);

    for (auto h : v) {
        while (l>h.l) update(0,mx,1,val[--l],1);
        while (r<h.r) update(0,mx,1,val[++r],1);
        while (l<h.l) update(0,mx,1,val[l++],-1);
        while (r>h.r) update(0,mx,1,val[r--],-1);
        Ans[h.idx]=s[1].ans;
    }
    return Ans;
}
/*
5 2
0 1 0 1
1 5 3 1 2
3 4

214
98
14
30
24
*/
