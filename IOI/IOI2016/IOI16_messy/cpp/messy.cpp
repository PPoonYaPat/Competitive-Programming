#include "messy.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int ni,a[130];

void build(int l, int r) {
    if (l==r) return;
    string st,ed;
    for (int i=0; i<l; ++i) st+="1";
    for (int i=r+1; i<ni; ++i) ed+="1";

    int mid=(l+r)/2;
    for (int i=l; i<=mid; ++i) {
        string h;
        for (int j=l; j<=r; ++j) {
            if (j==i) h+="1";
            else h+="0";
        }
        add_element(st+h+ed);
    }
    build(l,mid);
    build(mid+1,r);
}

void check(int l, int r, vector<int> v) { //in range l to r, what can it change to
    if (l==r) {
        a[v[0]]=l;
        return;
    }
    vector<int> left,right;
    string test;
    for (int i=0; i<ni; ++i) test+="1";
    for (auto s : v) test[s]='0';
    for (int i=0; i<ni; ++i) {
        if (test[i]=='0') {
            test[i]='1';
            if (check_element(test)) left.push_back(i);
            else right.push_back(i);
            test[i]='0';
        }
    }
    int mid=(l+r)/2;
    check(l,mid,left);
    check(mid+1,r,right);
}

vector<int> restore_permutation(int N, int w, int r) {
    ni=N;
    build(0,ni-1);
    compile_set();
    vector<int> v;
    for (int i=0; i<ni; ++i) v.push_back(i);
    check(0,ni-1,v);
    vector<int> ans;
    for (int i=0; i<ni; ++i) ans.push_back(a[i]);
    return ans;
}

