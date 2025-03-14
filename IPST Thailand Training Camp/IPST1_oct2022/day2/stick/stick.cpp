#include "stick.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int a[200001],n;
vector<int> s[1<<19]; //less to many

vector<int> merge(vector<int> x, vector<int> y) {
    vector<int> ans;

    int b=0, c=0;

    while (b<x.size() && c<y.size()) {
        if (x[b]>y[c]) {
            ans.push_back(y[c]);
            ++c;
        } else {
            ans.push_back(x[b]);
            ++b;
        }
    }

    while (b<x.size()) ans.push_back(x[b++]);
    while (c<y.size()) ans.push_back(y[c++]);

    return ans;
}

void build(int l, int r, int idx) {
    if (l>r) return;
    if (l==r) s[idx].push_back(a[l]);
    else {
        int mid=(l+r)/2;
        build(l,mid,2*idx);
        build(mid+1,r,2*idx+1);
        s[idx]=merge(s[2*idx],s[2*idx+1]);
    }
}

vector<int> query(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return {};
    if (x<=l && r<=y) return s[idx];

    int mid=(l+r)/2;
    return merge(query(l,mid,2*idx,x,y),query(mid+1,r,2*idx+1,x,y));
}

void init(int N, vector<int> X){
    n=N;
    for (int i=0; i<n; ++i) a[i]=X[i];
    build(0,n-1,1);
}

int max_length(int L,int R){
    vector<int> temp=query(0,n-1,1,L,R);

    for (int i=temp.size()-1; i>=2; --i) {
        if (temp[i]<temp[i-1]+temp[i-2]) return temp[i]+temp[i-1]+temp[i-2];
    }
    return -1;
}
/*
5 3
2 4 3 2 6
1 3
2 4
0 4

5 0
2 4 3 2 6
*/
