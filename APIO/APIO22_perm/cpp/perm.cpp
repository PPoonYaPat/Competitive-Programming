#include "perm.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int mmax,mmin;
vector<int> ans;

void create(ll x) {
    if (x==1) return;
    if (x==2) {
        ans.push_back(mmax+1);
        mmax+=1;
    } else if (x==3) {
        ans.push_back(mmax+2);
        ans.push_back(mmax+1);
        mmax+=2;
    } else if (x==5) {
        ans.push_back(mmax+2);
        ans.push_back(mmax+3);
        ans.push_back(mmax+1);
        mmax+=3;
    } else if (x==7) {
        ans.push_back(mmax+4);
        ans.push_back(mmax+1);
        ans.push_back(mmax+3);
        ans.push_back(mmax+2);
        mmax+=4;
    } else {
        if (x%2==0) create(x/2), create(2);
        else if (x%3==0) create(x/3), create(3);
        else if (x%5==0) create(x/5), create(5);
        else if (x%7==0) create(x/7), create(7);
        else {
            create(x/2);
            ans.push_back(++mmax);
            ans.push_back(--mmin);
        }
    }
}

vector<int> construct_permutation(long long k) {
    mmax=-1; mmin=0;
    ans.clear();
    create(k);
    for (int i=0; i<ans.size(); ++i) ans[i]-=mmin;
    return ans;
}
