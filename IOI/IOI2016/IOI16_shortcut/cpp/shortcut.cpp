#include "shortcut.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

int n;
ll ans=LLONG_MAX;
vector<pii> adj[1005];

struct NN {
    ll ma1,ma2;
};


ll find_shortcut(int N, vector<int> l, vector<int> d, int c) {
    n=N;
    for (int i=0; i<n-1; ++i) {
        adj[i].push_back(pii(i+1,l[i]));
        adj[i+1].push_back(pii(i,l[i]));
    }

    vector<int> v;

    for (int i=0; i<n; ++i) {
        v.push_back(i);
        if (d[i]) {
            adj[i].push_back(pii(i+500,d[i]));
            adj[i+500].push_back(pii(i,d[i]));
            v.push_back(i+500);
        }
    }

    for (int l=0; l<n; ++l) {
        for (int r=l+1; r<n; ++r) {
            //consider express in (l,r)
            adj[l].push_back(pii(r,c));
            adj[r].push_back(pii(l,c));

            ll mmax=0;

            

            adj[l].pop_back();
            adj[r].pop_back();
        }
    }

    return ans;
}
