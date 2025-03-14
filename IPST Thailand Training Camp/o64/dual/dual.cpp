#include <bits/stdc++.h>
#include "grader.cpp"
#include "dual.h"
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

ll ans;
deque<pii> dq; //pos,cost

long long dual_fuel(int n,int v,vector<int> &a, vector<int> &b) {

    for (int i=0; i<n; ++i) {
        while (!dq.empty() && dq.front().first<i-v) dq.pop_front();
        while (!dq.empty() && dq.back().second>=a[i]) dq.pop_back();
        dq.push_back(pii(i,a[i]));
        ans+=dq.front().second;
    }

    while (!dq.empty()) dq.pop_back();

    for (int i=0; i<n; ++i) {
        while (!dq.empty() && dq.front().first<i-v) dq.pop_front();
        while (!dq.empty() && dq.back().second>=b[i]) dq.pop_back();
        dq.push_back(pii(i,b[i]));
        ans+=dq.front().second;
    }

    return ans;
}
/*
1 10
1
3
*/
