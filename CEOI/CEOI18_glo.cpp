#include <bits/stdc++.h>
using namespace std;

int n,d,a[200005],change[200005];
stack<int> st[200005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>d;
    for (int i=1; i<=n; ++i) cin>>a[i];

    vector<int> v1,v2;
    for (int i=n; i>=1; --i) {
        auto it=lower_bound(v1.begin(),v1.end(),-a[i]-d);
        if (it==v1.end()) v1.push_back(-a[i]-d), st[v1.size()].push(a[i]+d), change[i]=v1.size();
        else if (*it==-a[i]-d) change[i]=-1;
        else {
            *it=-a[i]-d;
            change[i]=it-v1.begin()+1;
            st[it-v1.begin()+1].push(a[i]+d);
        }
    }
    for (int i=0; i<v1.size(); ++i) v1[i]=-v1[i];
    reverse(v1.begin(),v1.end());

    int ans=0;
    for (int i=1; i<=n; ++i) {
        if (change[i]!=-1) {
            st[change[i]].pop();
            if (st[change[i]].size()) v1[v1.size()-change[i]]=st[change[i]].top();
            else v1[v1.size()-change[i]]=0;
        }

        auto it=lower_bound(v2.begin(),v2.end(),a[i]);
        if (it==v2.end()) {
            v2.push_back(a[i]);
            ans=max(ans,(int)(v2.size())+(int)(v1.end()-upper_bound(v1.begin(),v1.end(),a[i])));
        } else if (*it!=a[i]) {
            *it=a[i];
            ans=max(ans,(int)(it-v2.begin()+1)+(int)(v1.end()-upper_bound(v1.begin(),v1.end(),a[i])));
        }
    }
    cout<<ans;
}