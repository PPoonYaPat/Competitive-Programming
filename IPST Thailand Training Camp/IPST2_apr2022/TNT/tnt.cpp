#include "tnt.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int n,cnt;

pair<int,int> solve(int x, int mod, vector<int> pos) { //start speed
    if (mod>=n) {
        return {(pos[0]-cnt*x+30*n)%n,x};
    }

    vector<int> temp;
    for (int i=0; i<pos.size(); ++i) {
        if (i%2==0) {
            for (int j=0; j<mod; ++j) temp.push_back((pos[i]+j)%n);
        }
    }

    bool in_temp[1050];
    memset(in_temp,0,sizeof(in_temp));
    for (auto s : temp) in_temp[s]=true;

    bool a1=find_tnt(temp), a2=find_tnt(temp);
    cnt+=2;

    int ans=-1, mid1=mod/2, mid2=mid1+mod-1;

    if (mod==1) {
        if (a1!=a2) ans=1;
        else ans=0;
    } else {
        if (a1!=a2) {
            for (int i=mid1; i<=mid2; ++i) if (i%mod==x) ans=i;
        } else {
            for (int i=0; i<mid1; ++i) if (i%mod==x) ans=i;
            for (int i=mid2+1; i<2*mod; ++i) if (i%mod==x) ans=i;
        }
    }

    bool have[1050];
    memset(have,0,sizeof(have));

    for (int power=ans; power<n; power+=2*mod) {
        for (auto s : pos) {
            if (in_temp[(s+power)%n]==a1 && in_temp[(s+2*power)%n]==a2) {
                have[(s+2*power)%n]=true;
            }
        }
    }

    vector<int> v;
    for (int i=0; i<n; ++i) if (have[i]) v.push_back(i);

    return solve(ans,2*mod,v);
}

vector<int> find_truck(int N) {
    n=N;
    vector<int> v,ans;
    for (int i=0; i<n; ++i) v.push_back(i);
    pair<int,int> a=solve(0,1,v);
    ans.push_back(a.first);
    ans.push_back(a.second);
    return ans;
}
/*
32 10 0 3
1024 20 15 466
*/
