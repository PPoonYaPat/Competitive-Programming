#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

int n,k;
pii a[250005];
vector<ll> ans;

bool check(ll want, int mode) {
    vector<ll> res;
    set<pii> s;

    for (int l=1, r=1; r<=n; ++r) {
        while (a[l].first<a[r].first-want) {
            s.erase(s.find({a[l].second,a[l].first}));
            ++l;
        }

        auto it=s.upper_bound({a[r].second-want,-1e15});
        while (it!=s.end() && (*it).first<=a[r].second+want) {
            res.push_back(max(abs((*it).second-a[r].first),abs((*it).first-a[r].second)));
            if (res.size()==k) return true;
            ++it;
        }

        s.insert(pii(a[r].second,a[r].first));
    }

    if (mode) swap(ans,res);
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>k;
    for (int i=1; i<=n; ++i) {
        ll x,y; cin>>x>>y;
        a[i].first=x+y;
        a[i].second=x-y;
    }
    sort(a+1,a+n+1);

    ll l=1, r=4e9+5;
    while (l<r) {
        ll mid=(l+r)/2;
        if (check(mid,0)) r=mid;
        else l=mid+1;
    }
    check(l-1,1);
    while (ans.size()<k) ans.push_back(l);
    sort(ans.begin(),ans.end());
    for (auto s : ans) cout<<s<<"\n";
}