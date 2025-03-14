#include <bits/stdc++.h>
#include "grader.cpp"
#include "dual.h"
using namespace std;

ll ans;

long long dual_fuel(int n,int v,vector<int> &a, vector<int> &b) {

    int mmin=INT_MAX;
    for (int i=0; i<n; ++i) mmin=min(mmin,a[i]), ans+=mmin;
    mmin=INT_MAX;
    for (int i=0; i<n; ++i) mmin=min(mmin,b[i]), ans+=mmin;

    return ans;
}

