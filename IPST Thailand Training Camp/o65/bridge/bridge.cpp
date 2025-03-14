#include "bridge.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mx=1e9+1, mn=-1e9-1;

struct Line {
    ll m,c;
};

ll f(Line a, ll x) {
    return a.m*x+a.c;
}

struct node {
    Line line;
    node *l, *r;

    node(Line li) : l(NULL), r(NULL), line(li) {}
};

void add(Line nw, int l, int r, node *pnode) {
    int mid=(l+r)/2;
    bool lef= f(nw,l)<f(pnode->line,l);
    bool m= f(nw,mid)<f(pnode->line,mid);

    if (m) swap(nw,pnode->line);

    if (r-l==1) return;
    else if (m!=lef) {
        if (pnode->l) add(nw,l,mid,pnode->l);
        else pnode->l=new node(nw);
    } else {
        if (pnode->r) add(nw,mid,r,pnode->r);
        else pnode->r=new node(nw);
    }
}

ll get(int l, int r, int x, node *pnode) {
    int mid=(l+r)/2;
    if (r-l==1) return f(pnode->line,x);
    else if (x<mid) {
        if (pnode->l) return min(f(pnode->line,x),get(l,mid,x,pnode->l));
        else return f(pnode->line,x);
    } else {
        if (pnode->r) return min(f(pnode->line,x),get(mid,r,x,pnode->r));
        else return f(pnode->line,x);
    }
}

int n;
ll qs[100010],Qs[100010],dp[100010];

ll destroy_bridge(int N, vector<int> W) {
    vector<int> w;
    w.push_back(0);
    for (int i=0; i<W.size(); ++i) w.push_back(W[i]);
    n=w.size()-1;

    for (int i=1; i<=n; ++i) qs[i]=qs[i-1]+w[i];
    for (int i=1; i<=n; ++i) Qs[i]=Qs[i-1]+w[i]*qs[i-1];

    node *LCT1=new node({0,0});
    for (int i=2; i<=n; ++i) {
        dp[i]=get(mn,mx,qs[i],LCT1)+Qs[i];
        add({-qs[i-1],qs[i-1]*qs[i]-Qs[i]},mn,mx,LCT1);
    }
    for (int i=3; i<=n; ++i) dp[i]=min(dp[i],dp[i-1]);

    node *LCT2=new node({-qs[3],qs[3]*qs[4]-Qs[4]+dp[2]});
    ll ans=LLONG_MAX;
    for (int i=5; i<=n; ++i) {
        ans=min(ans,get(mn,mx,qs[i],LCT2)+Qs[i]);
        add({-qs[i-1],qs[i-1]*qs[i]-Qs[i]+dp[i-2]},mn,mx,LCT2);
    }
    return ans;
}
/*
11
5 10 -3 8 4 5 -2 -9 12 11 4
5
1 0 3 0 5
*/
