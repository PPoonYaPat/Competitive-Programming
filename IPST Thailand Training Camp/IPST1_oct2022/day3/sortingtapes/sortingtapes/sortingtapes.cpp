#include <bits/stdc++.h>
//#include "grader.cpp"
#include "sortingtapes.h"
using namespace std;
typedef pair<int,int> pii;

int A[100001],B[100001],piv=10,sq,N,r[200001];
vector<int> k;

struct nn {
    int a,b;
    bool operator<(nn o) const {

        if (a/sq != o.a/sq) return a/sq<o.a/sq;
        else {
            if (a/sq%2==0) return b<o.b;
            else return b>o.b;
        }
    }
};

vector<nn> P;
int sum;
vector<int> X;

void ins(int a1, int a2, int b1, int b2) {
    for (int i=a1; i<=a2; ++i) r[A[X[i]]]+=sum;

    for (int i=a1; i<=a2; ++i) {
        for (int j=b1; j<=b2; ++j) P.push_back({A[X[i]],B[j]});
    }

    sum+=(b2-b1+1);
}

void subsort(vector<int> pos) {
    if (pos.size()<piv) {
        for (auto s : pos) {
            for (int i=N; i<2*N; ++i) if (!compare(A[s],i)) ++r[A[s]];
        }
        return;
    }

    vector<int> temp;
    for (int i=piv-1; i<pos.size(); i+=piv) temp.push_back(pos[i]);
    subsort(temp);

    sum=0; P.clear(); X.clear();
    for (auto s : pos) X.push_back(s);

    ins(0,piv-2,0,r[A[pos[piv-1]]]-1);

    for (int i=piv-1; i<pos.size(); i+=piv) {
        if (i+piv<pos.size()) ins(i+1,min(i+piv-1,(int)(pos.size())-1),r[A[pos[i]]],r[A[pos[i+piv]]]-1);
        else ins(i+1,min(i+piv-1,(int)(pos.size())-1),r[A[pos[i]]],N-1);
    }

    sort(P.begin(),P.end());
    for (auto s : P) {
        if (!compare(s.a,s.b)) ++r[s.a];
    }
}

vector<int> sort_tapes(int n, vector<int> AA, vector<int> BB) {
    N=n;
    for (int i=0; i<n; ++i) A[i]=AA[i], B[i]=BB[i];

    sq=sqrt(n);

    vector<int> h;
    for (int i=0; i<n; ++i) h.push_back(i);
    subsort(h);

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
