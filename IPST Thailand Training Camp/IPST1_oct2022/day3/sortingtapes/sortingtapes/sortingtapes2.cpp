#include <bits/stdc++.h>
//#include "grader.cpp"
#include "sortingtapes.h"
using namespace std;
typedef pair<int,int> pii;

int A[100001],B[100001],piv,sq,N,r[200001];
vector<int> k;

vector<pii> P,group[350];
int sum;

void ins(int a1, int a2, int b1, int b2) {
    for (int i=a1; i<=a2; ++i) r[A[i]]+=sum;

    for (int i=a1; i<=a2; ++i) {
        for (int j=b1; j<=b2; ++j) group[A[i]/sq].push_back({B[j],A[i]});
    }

    sum+=(b2-b1+1);
}

vector<int> sort_tapes(int n, vector<int> AA, vector<int> BB) {
    N=n;
    for (int i=0; i<n; ++i) A[i]=AA[i], B[i]=BB[i];

    for (int i=1; i<=10; ++i) if (i*i*i*i*i<=n) piv=i;
    sq=sqrt(n);

    vector<int> h;
    for (int i=piv-1; i<n; i+=piv) h.push_back(A[i]);
    sort(h.begin(),h.end());

    bool sw=false;
    for (auto s : h) {
        if (sw) {
            for (int j=n; j<2*n; ++j) if (!compare(s,j)) ++r[s];
            sw=false;
        } else {
            for (int j=2*n-1; j>=n; --j) if (!compare(s,j)) ++r[s];
            sw=true;
        }
    }

    ins(0,piv-2,0,r[A[piv-1]]-1);

    for (int i=piv-1; i<n; i+=piv) {
        if (i+piv<n) ins(i+1,min(i+piv-1,n-1),r[A[i]],min(r[A[i+piv]]-1,n-1));
        else ins(i+1,min(i+piv-1,n-1),r[A[i]],n-1);
    }

    for (int i=0; i<350; ++i) {
        if (i%2==0) sort(group[i].begin(),group[i].end());
        else sort(group[i].begin(),group[i].end(),greater<pii>());

        for (auto s : group[i]) P.push_back(pii(s.second,s.first));
    }


    for (auto s : P) {
        if (compare(s.first,s.second)) ++r[s.second];
        else ++r[s.first];
    }

    vector<pii> G;
    for (int i=0; i<n; ++i) if (i%piv != piv-1) G.push_back(pii(r[i],i));
    for (int i=n; i<2*n; ++i) G.push_back(pii(r[i],i));
    sort(G.begin(),G.end());

    int idx=0;
    for (int i=0; i<n; ++i) {
        while (idx<r[A[i]]) k.push_back(B[idx++]);
        k.push_back(A[i]);
    }
    while (idx<n) k.push_back(B[idx++]);

    return k;
}
/*
4
3 1 18 10 4 12 20 5
*/

