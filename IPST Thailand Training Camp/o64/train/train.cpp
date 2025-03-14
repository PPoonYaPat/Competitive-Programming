#include "train.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int> tu;

int s[1<<19],lz[1<<19];
const int inf=2e9;

void push(int l, int r, int idx) {
    if (lz[idx]!=inf) {
        s[idx]=min(s[idx],lz[idx]);
        if (l!=r) {
            lz[2*idx]=min(lz[2*idx],lz[idx]);
            lz[2*idx+1]=min(lz[2*idx+1],lz[idx]);
        }
        lz[idx]=inf;
    }
}

void update(int l, int r, int idx, int x, int y, int val) {
    push(l,r,idx);
    if (x>r || y<l) return;
    if (x<=l && r<=y) {
        lz[idx]=min(val,lz[idx]);
        push(l,r,idx);
    } else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,y,val);
        update(mid+1,r,2*idx+1,x,y,val);
        s[idx]=min(s[2*idx],s[2*idx+1]);
    }
}

int query(int l, int r, int idx, int x, int y) {
    push(l,r,idx);
    if (x>r || y<l) return inf;
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    return min(query(l,mid,2*idx,x,y),query(mid+1,r,2*idx+1,x,y));
}

int find_min_cost(int n, int m, vector<int>& S, vector<int>& T, vector<int>& C) {
    for (int i=0; i<(1<<19); ++i) s[i]=inf, lz[i]=inf;
    update(0,n-1,1,0,0,0);

    for (int i=0; i<m; ++i) update(0,n-1,1,S[i],T[i],query(0,n-1,1,S[i],T[i])+C[i]);

    int k=query(0,n-1,1,n-1,n-1);
    if (k==inf) return -1;
    else return k;
}
/*
7 7
0 2 10
1 3 50
2 6 200
2 4 30
4 6 200
3 6 10
0 6 1000

7 2
0 0 20
0 6 40
*/
