#include "reach.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int s[1<<18],n;

void update(int l, int r, int idx, int x, int val) {
    if (x>r || x<l) return;
    if (l==r) s[idx]=min(s[idx],val);
    else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,val);
        update(mid+1,r,2*idx+1,x,val);
        s[idx]=min(s[2*idx],s[2*idx+1]);
    }
}

int query(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return INT_MAX;
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    return min(query(l,mid,2*idx,x,y),query(mid+1,r,2*idx+1,x,y));
}


void initialize(int N) {
    n=N;
    memset(s,0x3f,sizeof(s));
    update(0,n-1,1,0,0);
    for (int i=0; i<N-1; ++i) update(0,n-1,1,i+1,i);
}

void add_arc(int u, int v) {
    update(0,n-1,1,v,u);
}

bool is_reachable(int u, int v, int t) {
    if (u==0 || (u<=t && t<=v)) return false;
    if (t<u) return true;
    if (query(0,n-1,1,v+1,t)<u) return true;
    else return false;
}
