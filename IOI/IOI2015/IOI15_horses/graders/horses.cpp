#include "horses.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

int n;
const ll mod=1e9+7;
pll ms[1<<21]; //-1,mod
ll x[500001],y[500001];

void build_ms(int l, int r, int idx) {
    if (l>r) return;
    if (l==r) ms[idx]={x[l],x[l]};
    else {
        int mid=(l+r)/2;
        build_ms(l,mid,2*idx);
        build_ms(mid+1,r,2*idx+1);

        if (ms[2*idx].first==-1 || ms[2*idx+1].first==-1) ms[idx].first=-1;
        else {
            if (ms[2*idx].first*ms[2*idx+1].first>1e9) ms[idx].first=-1;
            else ms[idx].first=ms[2*idx].first*ms[2*idx+1].first;
        }
        ms[idx].second=(ms[2*idx].second*ms[2*idx+1].second)%mod;
    }
}

void update_ms(int l, int r, int idx, int k, ll val) {
    if (l>k || k>r) return;
    if (l==r) ms[idx]={val,val};
    else {
        int mid=(l+r)/2;
        update_ms(l,mid,2*idx,k,val);
        update_ms(mid+1,r,2*idx+1,k,val);

        if (ms[2*idx].first==-1 || ms[2*idx+1].first==-1) ms[idx].first=-1;
        else {
            if (ms[2*idx].first*ms[2*idx+1].first>1e9) ms[idx].first=-1;
            else ms[idx].first=ms[2*idx].first*ms[2*idx+1].first;
        }
        ms[idx].second=(ms[2*idx].second*ms[2*idx+1].second)%mod;
    }
}

ll query_ms(int l, int r, int idx, int x, int y) {
    if (l>y || r<x) return 1;
    if (x<=l && r<=y) return ms[idx].first;

    int mid=(l+r)/2;
    ll ml=query_ms(l,mid,2*idx,x,y), mr=query_ms(mid+1,r,2*idx+1,x,y);

    if (ml==-1 || mr==-1) return -1;
    else {
        if (ml*mr>1e9) return -1;
        else return ml*mr;
    }
}

ll query_ms2(int l, int r, int idx, int x, int y) {
    if (l>y || r<x) return 1;
    if (x<=l && r<=y) return ms[idx].second;

    int mid=(l+r)/2;
    return (query_ms2(l,mid,2*idx,x,y)*query_ms2(mid+1,r,2*idx+1,x,y))%mod;
}

ll h;
int check(int a, int b) { //whether who is bigger between s[a] and a[b]
    h=query_ms(0,n-1,1,a+1,b);
    if (h==-1) return b;
    if (y[a]>y[b]*h) return a;
    else return b;
}

ll s[1<<21];

void update(int l, int r, int idx) {
    if (l>r) return;
    if (l==r) s[idx]=l;
    else {
        int mid=(l+r)/2;
        update(l,mid,2*idx);
        update(mid+1,r,2*idx+1);
        s[idx]=check(s[2*idx],s[2*idx+1]);
    }
}

void update2(int l, int r, int idx, int x, int y) {
    if (l>y || r<x) return;
    if (x<=l && r<=y) return;
    else {
        int mid=(l+r)/2;
        update2(l,mid,2*idx,x,y);
        update2(mid+1,r,2*idx+1,x,y);
        s[idx]=check(s[2*idx],s[2*idx+1]);
    }
}

void update3(int l, int r, int idx, int x) {
    if (l>x || x>r) return;
    if (l==r) return;
    else {
        int mid=(l+r)/2;
        update3(l,mid,2*idx,x);
        update3(mid+1,r,2*idx+1,x);
        s[idx]=check(s[2*idx],s[2*idx+1]);
    }
}

int init(int N, int X[], int Y[]) {
    n=N;
    for (int i=0; i<n; ++i) x[i]=X[i], y[i]=Y[i];
    build_ms(0,n-1,1);

    update(0,n-1,1);
    return (query_ms2(0,n-1,1,0,s[1])*y[s[1]])%mod;

}

int updateX(int pos, int val) {
    x[pos]=val;
    update_ms(0,n-1,1,pos,val);
    update2(0,n-1,1,pos,n-1);

    return (query_ms2(0,n-1,1,0,s[1])*y[s[1]])%mod;
}

int updateY(int pos, int val) {
    y[pos]=val;
    update3(0,n-1,1,pos);

    return (query_ms2(0,n-1,1,0,s[1])*y[s[1]])%mod;
}
