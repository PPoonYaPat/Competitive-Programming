#include "wall.h"
#include "grader.cpp"

#include <bits/stdc++.h>
using namespace std;

struct A {
    int mmax,mmin;
} lz[1<<22];

int ans[2000001];

void pushlz(int l, int r, int idx) {
    if (l!=r) {
        int u=2*idx, v=2*idx+1;

        lz[u].mmax=min(lz[idx].mmax,lz[u].mmax);
        lz[u].mmin=min(lz[idx].mmax,lz[u].mmin);
        lz[v].mmax=min(lz[idx].mmax,lz[v].mmax);
        lz[v].mmin=min(lz[idx].mmax,lz[v].mmin);
        lz[idx].mmax=INT_MAX;

        lz[u].mmax=max(lz[idx].mmin,lz[u].mmax);
        lz[u].mmin=max(lz[idx].mmin,lz[u].mmin);
        lz[v].mmax=max(lz[idx].mmin,lz[v].mmax);
        lz[v].mmin=max(lz[idx].mmin,lz[v].mmin);
        lz[idx].mmin=0;
    }
}

void update(int l, int r, int idx, int x, int y, int val, int mode) {
    pushlz(l,r,idx);
    if (x>r || y<l) return;
    if (x<=l && r<=y) {
        if (mode==1) {
            lz[idx].mmin=max(lz[idx].mmin,val);
            lz[idx].mmax=max(lz[idx].mmax,val);
        } else {
            lz[idx].mmax=min(lz[idx].mmax,val);
            lz[idx].mmin=min(lz[idx].mmin,val);
        }
    } else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,y,val,mode);
        update(mid+1,r,2*idx+1,x,y,val,mode);
    }
}

void dfs(int l, int r, int idx) {
    pushlz(l,r,idx);
    if (l==r) {
        ans[l]=lz[idx].mmin;
    } else {
        int mid=(l+r)/2;
        dfs(l,mid,2*idx);
        dfs(mid+1,r,2*idx+1);
    }
}

void buildWall(int n, int k, int op[], int l[], int r[], int h[], int finalHeight[]){
    for (int i=1; i<=(1<<21); ++i) lz[i]={INT_MAX,0};
    for (int i=0; i<k; ++i) update(1,n,1,++l[i],++r[i],h[i],op[i]);
    dfs(1,n,1);
    for (int i=0; i<n; ++i) finalHeight[i]=ans[i+1];
}

/*
10 3
1 3 4 91220
1 5 9 48623
2 3 5 39412

0
0
0
39412
39412
39412
48623
48623
48623
48623

10 6
1 1 8 4
2 4 9 1
2 3 6 5
1 0 5 3
1 2 2 5
2 6 7 0

3
4
5
4
3
3
0
0
1
0
*/

