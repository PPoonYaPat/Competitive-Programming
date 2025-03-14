#include "ricehub.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

multiset<int> rsq,lsq;
int median=INT_MAX,ans;
ll rsum,lsum;

void med() {
    if (lsq.size()<rsq.size()) {
        auto it=rsq.begin();
        rsum-=*it;
        lsum+=*it;
        lsq.insert(*it);
        rsq.erase(it);
    }

    if (lsq.size()>rsq.size()+1) {
        auto it=lsq.end(); --it;
        rsum+=*it;
        lsum-=*it;
        rsq.insert(*it);
        lsq.erase(it);
    }

    auto it=lsq.end();
    median=*(--it);
}

void add(int x) {
    if (x<=median) lsum+=x, lsq.insert(x);
    else rsum+=x, rsq.insert(x);
    med();
}

void del(int x) {
    if (x<=median) {
        auto it=lsq.find(x);
        lsum-=x;
        lsq.erase(it);
    } else {
        auto it=rsq.find(x);
        rsum-=x;
        rsq.erase(it);
    }
    med();
}


int besthub(int n, int l, int c[], long long b) {
    int i=0, j=0;
    ll x=0;

    while (i<n) {
        add(c[i++]);

        if (lsq.size()==rsq.size()) x=rsum-lsum;
        else x=rsum-lsum+median;

        while (x>b && j<n) {
            del(c[j++]);
            if (lsq.size()==rsq.size()) x=rsum-lsum;
            else x=rsum-lsum+median;
        }

        ans=max(ans,i-j);
    }
    return ans;
}
/*
5 20 6
1 2 10 12 14
3
*/
