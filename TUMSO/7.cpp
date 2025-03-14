#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct A {
    ll L[3],R[3],ans,sum;
} s[1<<18];

int n,q;
string st;

A merge(A a, A b) {
    A res;
    res.sum=(a.sum+b.sum)%3;
    res.ans=a.ans+b.ans+(a.R[2]*b.L[1])+(a.R[1]*b.L[2])+(a.R[0]*b.L[0]);
    for (int i=0; i<3; ++i) {
        res.L[(a.sum+i)%3]=a.L[(a.sum+i)%3]+b.L[i];
        res.R[(b.sum+i)%3]=b.R[(b.sum+i)%3]+a.R[i];
    }
    return res;
}

void create(int idx, int val) {
    s[idx]={{0,0,0},{0,0,0},0,0};
    s[idx].sum=val%3;
    s[idx].L[val%3]=1;
    s[idx].R[val%3]=1;
    if (val%3==0) s[idx].ans=1;
}

void build(int l, int r, int idx) {
    if (l==r) create(idx,(int)(st[l-1]-'0'));
    else {
        int mid=(l+r)/2;
        build(l,mid,2*idx);
        build(mid+1,r,2*idx+1);
        s[idx]=merge(s[2*idx],s[2*idx+1]);
    }
}

void update(int l, int r, int idx, int x, int val) {
    if (x>r || x<l) return;
    if (l==r) create(idx,val);
    else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,val);
        update(mid+1,r,2*idx+1,x,val);
        s[idx]=merge(s[2*idx],s[2*idx+1]);
    }
}

A query(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return {{0,0,0},{0,0,0},0,0};
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    return merge(query(l,mid,2*idx,x,y),query(mid+1,r,2*idx+1,x,y));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>q>>st;
    build(1,n,1);
    while (q--) {
        int mode,a,b; cin>>mode>>a>>b;
        if (mode==2) cout<<query(1,n,1,a,b).ans<<"\n";
        else update(1,n,1,a,b);
    }
}
