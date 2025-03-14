#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

ll ans;
set<pii> s;
int n;
pii a[100001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=1; i<=n; ++i) cin>>a[i].first>>a[i].second;
    sort(a+1,a+n+1);
    s.insert(pii(0,0));

    for (int i=1; i<=n; ++i) {

        auto it=s.upper_bound(pii(a[i].first,-INT_MAX));
        if (it==s.end() || (*it).first!=a[i].first) s.insert(pii(a[i].first,0));

        it=s.upper_bound(pii(a[i].first-a[i].second,-INT_MAX));

        if ((*it).first!=a[i].first-a[i].second) {
            auto it2=it; --it2;
            if ((*it2).second!=-1) s.insert(pii((*it2).first,(*it2).second+1));
            s.insert(pii((*it2).first+a[i].second-a[i].first+(*it).first,-1));
            s.erase(it2);
        }

        if (it!=--s.end()) {
            if ((*it).second!=-1) s.insert(pii((*it).first,(*it).second+1));
            s.erase(it);

            auto it3=s.end(); --it3;
            s.insert(pii((*it3).first,(*it3).second-1));
            s.erase(it3);
        }

        it=s.end(); --it;
        if ((*it).second==0) s.erase(it);
    }

    auto it1=s.begin(), it2=it1++;
    ll h=(*it2).second;
    while (it1!=s.end()) {
        ans+=h*(h-1)*((*it1).first-(*it2).first)/2;
        h+=(*it1).second;
        ++it1; ++it2;
    }
    cout<<ans;
}