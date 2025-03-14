#include "jumps.h"
#include "stub.cpp"
#include <bits/stdc++.h>
using namespace std;

int n,h[200001],s[1<<19];
int l[400001][20],r[400001][20],high[400001][20];

void build(int ll, int rr, int idx) {
    if (ll>rr) return;
    if (ll==rr) s[idx]=h[ll];
    else {
        int mid=(ll+rr)/2;
        build(ll,mid,2*idx);
        build(mid+1,rr,2*idx+1);
        s[idx]=max(s[2*idx],s[2*idx+1]);
    }
}

int query(int ll, int rr, int idx, int x, int y) {
    if (ll>y ||rr<x) return 0;
    if (x<=ll && rr<=y) return s[idx];
    int mid=(ll+rr)/2;
    return max(query(ll,mid,2*idx,x,y),query(mid+1,rr,2*idx+1,x,y));
}

void init(int N, vector<int> H) {
    n=N;
    for (int i=0; i<n; ++i) h[i+1]=H[i];
    build(1,n,1);

    for (int i=1; i<=n; ++i) {
        int idx=i-1;
        while (h[idx]<h[i] && idx!=0) idx=l[idx][0];
        l[i][0]=idx;
    }

    for (int i=n; i>=1; --i) {
        int idx=i+1;
        while (h[idx]<h[i] && idx!=n+1) idx=r[idx][0];
        r[i][0]=idx;
    }

    for (int i=1; i<=n; ++i) {
        if (h[r[i][0]]>h[l[i][0]]) high[i][0]=r[i][0];
        else high[i][0]=l[i][0];
    }

    for (int i=1; i<18; ++i) {
        for (int j=1; j<=n; ++j) {
            l[j][i]=l[l[j][i-1]][i-1];
            r[j][i]=r[r[j][i-1]][i-1];
            high[j][i]=high[high[j][i-1]][i-1];
        }
    }
}

int minimum_jumps(int A, int B, int C, int D) {
    int a=++A, b=++B, c=++C, d=++D;
    int mmax=query(1,n,1,c,d),now=b;

    if (query(1,n,1,b,c-1)>mmax) return -1;

    //free range, start with considering b
    for (int i=18; i>=0; --i) {
        if (l[now][i]>=a && h[l[now][i]]<mmax) now=l[now][i]; //go to left[now][i] (in free range)
    }
    if (r[now][0]>=c) return 1;

    int ans=0;
    for (int i=18; i>=0; --i) {
        if (r[high[now][i]][0]<c && high[now][i]!=0 && high[now][i]!=n+1) { //go to the highest point (with cost)
            ans+=(1<<i);
            now=high[now][i];
        }
    }

    if (h[l[now][0]]<mmax && l[now][0]!=0) return ans+2;

    for (int i=18; i>=0; --i) { //go from the highest point (lower than h[c]) to c
        if (r[now][i]<c && r[now][i]!=0 && r[now][i]!=n+1) {
            ans+=(1<<i);
            now=r[now][i];
        }
    }
    return ans+1;
}
/*
7 3
3 2 1 6 4 5 7
4 4 6 6
1 3 5 6
0 1 2 2

2
1
-1

7 1
3 2 1 6 4 5 7
4 4 6 6
1 3 5 6
0 1 2 2
*/
