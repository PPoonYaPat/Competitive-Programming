#include "compatibility.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,m,sum[3001],rsum[3001];
vector<int> rev[3001],v[3001];

ll maximum_incompatibility(vector<vector<int>> A) {
    m=A.size();
    n=A[0].size();

    for (int i=0; i<m; ++i) {
        v[i].push_back(0);
        for (auto s : A[i]) {
            v[i].push_back(s);
            rev[i].push_back(-s);
        }
        rev[i].push_back(INT_MAX);
    }

    for (int i=0; i<m; ++i) reverse(rev[i].begin(),rev[i].end());

    for (int i=0; i<m; ++i) {
        sum[i]=-v[i][n]-v[i][1];
        rsum[i]=-rev[i][n]-rev[i][1];

        for (int j=1; j<=n; ++j) {
            sum[i]+=2*v[i][j];
            rsum[i]+=2*rev[i][j];
        }
    }

    ll mmax=-LLONG_MAX;
    for (int i=0; i<m; ++i) {
        for (int j=i+1; j<m; ++j) {
            int l=1,r=n;
            while (l<r) {
                int mid=(l+r+1)/2;
                if (v[i][mid]-rev[j][mid]>=v[i][mid-1]-rev[j][mid-1]) l=mid;
                else r=mid-1;
            }
            mmax=max(mmax,rsum[j]-sum[i]+2*(n-1)*(v[i][l]-rev[j][l]));
        }
    }
    return mmax;
}
/*
2 5
10 40 60 70 75
0 10 15 17 18
*/
