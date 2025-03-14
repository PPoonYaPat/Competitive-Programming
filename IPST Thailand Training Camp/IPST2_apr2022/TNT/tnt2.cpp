#include "tnt.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int ss,n;

vector<int> solve(vector<pii> v) { //position, power
    if (v.size()==1) {
        return {(v[0].first+30*n-ss*v[0].second)%n,v[0].second};
    }

    for (int i=0; i<v.size(); ++i) v[i].first=(v[i].first+v[i].second)%n;

    int cnt[1050];
    memset(cnt,0,sizeof(cnt));
    for (auto s : v) ++cnt[s.first];

    int mmin=INT_MAX;
    pii ans;
    for (int i=0; i<n; ++i) {
        int idx=i, sum=0;
        while (sum<(int)(v.size())/2) sum+=cnt[idx++];

        if (abs((int)(v.size())-2*sum)<mmin) {
            mmin=abs((int)(v.size())-2*sum);
            ans={i,idx-1};
        }
    }

    vector<int> temp;
    for (int i=ans.first; i<=ans.second; ++i) temp.push_back(i);

    ++ss;
    vector<pii> nnew;

    if (find_tnt(temp)) {
        for (auto s : v) if (ans.first<=s.first && s.first<=ans.second) nnew.push_back(s);
    } else {
        for (auto s : v) if (ans.first>s.first || s.first>ans.second) nnew.push_back(s);
    }

    return solve(nnew);
}

vector<int> find_truck(int N) {
    n=N;
    vector<pii> temp;
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) temp.push_back(pii(i,j));
    }
    return solve(temp);
}
/*
1024 20 45 355
1024 20 15 466
*/
