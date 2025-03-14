#include "celeb.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct line {
    ll m,c;
};

deque<line> dq;

double ins(line a, line b) {
    return (double)(b.c-a.c)/(a.m-b.m);
}

vector<ll> max_revenue(int n, int k, vector<long long> X, vector<int> M) {
    for (int i=0; i<n; ++i) {
        line nw={-i,X[i]};
        if (dq.size() && dq.back().c>=nw.c) continue;

        while (dq.size()>=2) {
            line a1=dq.back(); dq.pop_back();
            line a2=dq.back(); dq.push_back(a1);

            if (ins(nw,a2)>=ins(a1,a2)) dq.pop_back();
            else break;
        }

        dq.push_back(nw);
    }

    vector<ll> ans;
    for (int i=0; i<k; ++i) {
        while (dq.size()>=2) {
            line a1=dq.back(); dq.pop_back();
            line a2=dq.back(); dq.push_back(a1);

            if (ins(a1,a2)<=M[i]) dq.pop_back();
            else break;
        }
        ans.push_back(dq.back().m*M[i]+dq.back().c);
    }
    return ans;
}
/*
5 3
3 35 40 12 100
1 10 30
*/
