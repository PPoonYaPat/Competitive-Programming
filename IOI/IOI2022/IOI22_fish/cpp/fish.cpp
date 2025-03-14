#include "fish.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

vector<pii> fish[100001]; //row,value
vector<pii> pos; //find -> x,y
ll sum_in[600010],sum_left[600010],sum_right[600010],dp[600010][2],mmax[100001],pre1_low,pre2_low; //0-decreasing, 1-increasing
multiset<ll, greater<ll>> pre1_high,pre2_high; //high
int start_col[100001],end_col[100001];

ll max_weights(int n, int m, vector<int> X, vector<int> Y, vector<int> W) {

    memset(start_col,-1,sizeof(start_col));
    memset(end_col,-1,sizeof(end_col));

    for (int i=0; i<m; ++i) {
        fish[X[i]].push_back(pii(Y[i],W[i]));
        if (X[i]) pos.push_back(pii(X[i]-1,Y[i]));
        if (X[i]<n-1) pos.push_back(pii(X[i]+1,Y[i]));
    }

    for (int i=0; i<n; ++i) {
        sort(fish[i].begin(),fish[i].end());
        for (int j=1; j<fish[i].size(); ++j) fish[i][j].second=fish[i][j].second+fish[i][j-1].second;
    }

    sort(pos.begin(),pos.end());
    int k=pos.size(),pre_col=-1;
    for (int i=0; i<k; ++i) {
        if (pos[i].first!=pre_col) {
            start_col[pos[i].first]=i;
            pre_col=pos[i].first;
        }
        end_col[pos[i].first]=i;
    }

    for (int i=0; i<k; ++i) {
        int x=pos[i].first, y=pos[i].second;

        //sum_in
        auto it=upper_bound(fish[x].begin(),fish[x].end(),pii(y,LLONG_MAX));
        if (it==fish[x].begin()) sum_in[i]=0;
        else sum_in[i]=(*(--it)).second;

        //sum_left
        if (x) {
            it=upper_bound(fish[x-1].begin(),fish[x-1].end(),pii(y,LLONG_MAX));
            if (it==fish[x-1].begin()) sum_left[i]=0;
            else sum_left[i]=(*(--it)).second;
        } else sum_left[i]=0;

        //sum_right
        if (x<n-1) {
            it=upper_bound(fish[x+1].begin(),fish[x+1].end(),pii(y,LLONG_MAX));
            if (it==fish[x+1].begin()) sum_right[i]=0;
            else sum_right[i]=(*(--it)).second;
        } else sum_right[i]=0;
    }

    for (int i=0; i<n; ++i) {
        if (start_col[i]!=-1) {
            //reset
            pre1_high.clear();
            pre2_high.clear();
            pre1_low=0;
            pre2_low=0;

            int idx1,idx2;

            if (i>0 && start_col[i-1]!=-1) {
                for (int j=start_col[i-1]; j<=end_col[i-1]; ++j) {
                    pre1_high.insert(dp[j][0]);
                    pre1_high.insert(dp[j][1]);
                }
                idx1=start_col[i-1];
            } else idx1=INT_MAX;

            if (i>1 && start_col[i-2]!=-1) {
                for (int j=start_col[i-2]; j<=end_col[i-2]; ++j) {
                    pre2_high.insert(dp[j][0]);
                    pre2_high.insert(dp[j][1]);
                }
                idx2=start_col[i-2];
            } else idx2=INT_MAX;

            for (int idx=start_col[i]; idx<=end_col[i]; ++idx) {
                    //find dp[idx][0], dp[idx][1]
                if (i>=3) {
                    dp[idx][0]=sum_left[idx]+sum_right[idx]+mmax[i-3];
                    dp[idx][1]=sum_left[idx]+sum_right[idx]+mmax[i-3];
                } else {
                    dp[idx][0]=sum_left[idx]+sum_right[idx];
                    dp[idx][1]=sum_left[idx]+sum_right[idx];
                }

                while (idx1<=end_col[i-1] && pos[idx1].second<=pos[idx].second) { //go to lower
                    pre1_high.erase(pre1_high.find(dp[idx1][0]));
                    pre1_high.erase(pre1_high.find(dp[idx1][1]));
                    pre1_low=max(pre1_low,dp[idx1][1]-sum_in[idx1]-sum_right[idx1]);
                    ++idx1;
                }

                while (idx2<=end_col[i-2] && pos[idx2].second<=pos[idx].second) { //go to lower
                    pre2_high.erase(pre2_high.find(dp[idx2][0]));
                    pre2_high.erase(pre2_high.find(dp[idx2][1]));
                    pre2_low=max({pre2_low,dp[idx2][0]-sum_right[idx2],dp[idx2][1]-sum_right[idx2]});
                    ++idx2;
                }

                if (pre1_high.size()) {
                    dp[idx][0]=max(dp[idx][0],*(pre1_high.begin())-sum_in[idx]+sum_right[idx]);
                }

                dp[idx][1]=max(dp[idx][1],pre1_low+sum_left[idx]+sum_right[idx]);

                if (pre2_high.size()) {
                    ll h=*(pre2_high.begin());
                    dp[idx][0]=max(dp[idx][0],h+sum_right[idx]);
                    dp[idx][1]=max(dp[idx][1],h+sum_right[idx]);
                }

                dp[idx][0]=max(dp[idx][0],pre2_low+sum_left[idx]+sum_right[idx]);
                dp[idx][1]=max(dp[idx][1],pre2_low+sum_left[idx]+sum_right[idx]);

                mmax[i]=max({mmax[i],dp[idx][0],dp[idx][1]});

            }
        }
        mmax[i]=max(mmax[i],mmax[i-1]);
    }
    return mmax[n-1];
}
/*
5 4
0 2 5
1 1 2
4 4 1
3 3 3
*/
