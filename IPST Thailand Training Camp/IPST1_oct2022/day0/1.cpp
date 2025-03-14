#include <bits/stdc++.h>
using namespace std;

const int sq=500;
int n,m,q,l[120001],money[120001],c[120001]; //money : money from shop, c : money of customer
vector<int> shop[120001], customer[120001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m>>q;
    for (int i=1; i<=m; ++i) {
        cin>>l[i];
        if (l[i]>=sq) {
            for (int j=0; j<l[i]; ++j) {
                int x; cin>>x;
                customer[x].push_back(i);
            }
        } else {
            for (int j=0; j<l[i]; ++j) {
                int x; cin>>x;
                shop[i].push_back(x);
            }
        }
    }

    while (q--) {
        int mode; cin>>mode;
        if (mode==1) {
            int x,y; cin>>x>>y; //shop x change money to y
            if (l[x]<sq) {
                for (auto s : shop[x]) {
                    c[s]=c[s]-money[x]+y;
                }
            }
            money[x]=y;
        } else {
            int x; cin>>x;
            int ans=c[x];
            for (auto s : customer[x]) ans+=money[s];
            cout<<ans<<"\n";
        }

    }
}
