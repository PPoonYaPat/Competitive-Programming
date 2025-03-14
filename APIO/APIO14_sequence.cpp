#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,k,ans[100001][201];
ll qs[100001],dp[100001][2];

struct line {
    int ord;
    ll con,slope;
};

deque<line> dq;

double ins(line a, line b) {
    return (double)(b.con-a.con)/(a.slope-b.slope);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>k;
    for (int i=1; i<=n; ++i) {
        cin>>qs[i];
        qs[i]+=qs[i-1];
    }

    for (int i=1; i<n; ++i) dp[i][1]=qs[i]*(qs[n]-qs[i]), ans[i][1]=i;

    for (int j=2; j<=k; ++j) {
        int now=j%2, pre=1-now;

        for (int i=j-1; i<n; ++i) {
            //find dp[i][j]

            while (dq.size()>=2) {
                line l1=dq.front(); dq.pop_front();
                line l2=dq.front(); dq.push_front(l1);

                if (ins(l1,l2)<=qs[i]) dq.pop_front();
                else break;
            }

            if (i>=j) {
                dp[i][now]=dq.front().con+dq.front().slope*qs[i]+qs[i]*(qs[n]-qs[i]);
                ans[i][j]=dq.front().ord;
            }

            line l={i,dp[i][pre]-qs[i]*qs[n],qs[i]};

            while (dq.size()>=2) {
                line l1=dq.back(); dq.pop_back();
                line l2=dq.back(); dq.push_back(l1);

                if (ins(l1,l2)>=ins(l,l2)) dq.pop_back();
                else break;
            }

            if (dq.size()) {
                if (dq.back().slope!=l.slope) dq.push_back(l);
            } else dq.push_back(l);
        }

        while (!dq.empty()) dq.pop_back();
    }

    ll mmax=-1,mnode;
    for (int i=1; i<n; ++i) {
        if (mmax<dp[i][k%2]) {
            mmax=dp[i][k%2];
            mnode=i;
        }
    }
    cout<<mmax<<"\n";

    vector<int> v;
    while (k) {
        v.push_back(mnode);
        mnode=ans[mnode][k];
        --k;
    }
    reverse(v.begin(),v.end());

    for (auto s : v) cout<<s<<" ";
}
