#include "symbols.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int n;
const ll mod=20232566;
ll s[1<<18];
set<pii> v; //start,end

void update(int l, int r, int idx, int x, int val) {
    if (l>x || x>r) return;
    if (l==r) s[idx]=val;
    else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,val);
        update(mid+1,r,2*idx+1,x,val);
        s[idx]=(s[2*idx]*s[2*idx+1])%mod;
    }
}

void explore_site(int N, int Q) {
    n=N;
    for (int i=0; i<n; ++i) update(0,n-1,1,i,26);
}


int retrieve_notes(int L, int R) {
    int mmax=R, mmin=L, st=L;

    auto itt=v.lower_bound(pii(L,-INT_MAX));
    if (itt==v.begin()) {

    } else {
        --itt;
        if ((*itt).second>=L) st=(*itt).second+1, mmin=(*itt).first;

        if ((*itt).second>R) return s[1];
    }

    int lef=26;
    for (int i=L; i<=R; ++i) {
        if (i>=st) update(0,n-1,1,i,lef);
        --lef;
    }

    v.insert(pii(mmin,mmax));
    return s[1];
}
/*
10 3
2 4
3 5
2 5

4 2
1 2
0 3

4 3
0 1
2 3
1 2

10 4
0 2
4 5
6 9
2 7
*/
