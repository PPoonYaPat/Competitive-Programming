#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,q;
ll s,t,c[200010],fen[200010],ans;

void update(int x, int val) {
    while (x<=n+5) {
        fen[x]+=val;
        x+=(x&-x);
    }
}

ll find(int x) {
    ll sum=c[x];
    while (x) {
        sum+=fen[x];
        x-=(x&-x);
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>q>>s>>t;
    for (int i=1; i<=n+1; ++i) {
        cin>>c[i];
        if (i>1) {
            if (c[i]>c[i-1]) ans-=(s*(c[i]-c[i-1]));
            else ans+=(t*(c[i-1]-c[i]));
        }
    }

    while (q--) {
        int a,b; ll val;
        cin>>a>>b>>val;
        ++a; ++b;

        if (a!=1) {
            ll pa=find(a-1), ha=find(a);
            if (pa<ha) ans+=s*(ha-pa);
            else ans-=t*(pa-ha);
            ha+=val;
            if (pa<ha) ans-=s*(ha-pa);
            else ans+=t*(pa-ha);
        }

        if (b!=n+1) {
            ll pb=find(b+1), hb=find(b);
            if (hb<pb) ans+=s*(pb-hb);
            else ans-=t*(hb-pb);
            hb+=val;
            if (hb<pb) ans-=s*(pb-hb);
            else ans+=t*(hb-pb);
        }

        update(a,val);
        update(b+1,-val);
        cout<<ans<<"\n";
    }
}