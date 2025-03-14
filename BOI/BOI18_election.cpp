#include <bits/stdc++.h>
using namespace std;

struct A {
    int L,R,sum,ans;
} s[1<<20];

int n;
char c[500001];

A merge(A a, A b) {
    A res;
    res.L=max(a.L,a.sum+b.L);
    res.R=max(b.R,b.sum+a.R);
    res.sum=a.sum+b.sum;
    res.ans=max({a.L+b.R,a.ans+b.sum,b.ans+a.sum});
    return res;
}

void build(int l, int r, int idx) {
    if (l==r) {
        if (c[l]=='T') s[idx]={1,1,1,1};
        else s[idx]={0,0,-1,0};
    } else {
        int mid=(l+r)/2;
        build(l,mid,2*idx);
        build(mid+1,r,2*idx+1);
        s[idx]=merge(s[2*idx],s[2*idx+1]);
    }
}

A query(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return {0,0,0,0};
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    return merge(query(l,mid,2*idx,x,y),query(mid+1,r,2*idx+1,x,y));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=1; i<=n; ++i) cin>>c[i];
    build(1,n,1);
    int q; cin>>q;
    while (q--) {
        int a,b; cin>>a>>b;
        cout<<query(1,n,1,a,b).ans<<"\n";
    }
}
