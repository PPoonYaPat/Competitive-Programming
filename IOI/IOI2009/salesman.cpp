#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<ll,ll,ll> tu;

struct seg {
    ll up,down;
} s[1<<21];

const int mx=500005;
const ll mn=-1e18;
ll n,u,d,st,best[500010],temp1[500010],temp2[500010];
vector<tu> v; //day, location, profit

void update(int l, int r, int idx, int x, ll val_up, ll val_down) {
    if (l>x || r<x) return;
    if (l==r) s[idx]={val_up,val_down};
    else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,val_up,val_down);
        update(mid+1,r,2*idx+1,x,val_up,val_down);
        s[idx].up=max(s[2*idx].up,s[2*idx+1].up);
        s[idx].down=max(s[2*idx].down,s[2*idx+1].down);
    }
}

seg query(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return {mn,mn};
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    seg L=query(l,mid,2*idx,x,y), R=query(mid+1,r,2*idx+1,x,y);
    return {max(L.up,R.up),max(L.down,R.down)};
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    for (int i=0; i<1<<21; ++i) s[i]={mn,mn};

    cin>>n>>u>>d>>st;
    for (int i=0; i<n; ++i) {
        ll a,b,c; cin>>a>>b>>c;
        v.push_back(tu(a,b,c));
    }
    v.push_back(tu(mx+2,st,0));
    sort(v.begin(),v.end());
    update(1,mx,1,st,(mx-st)*u,(st-1)*d);


    for (int i=0; i<=n; ) {
        int m=1;
        while (get<0>(v[i])==get<0>(v[i+m])) ++m;

        ll mmax_up=mn, mmax_down=mn;

        for (int j=i; j<i+m; ++j) {
            ll loc=get<1>(v[j]), profit=get<2>(v[j]);
            best[j]=max(query(1,mx,1,1,loc).down-(loc-1)*d, query(1,mx,1,loc+1,mx).up-(mx-loc)*u)+profit;
            temp1[j]=mmax_down-d*(loc-1)+profit;
            mmax_down=max(mmax_down, max(temp1[j],best[j])+d*(loc-1));
        }

        for (int j=i+m-1; j>=i; --j) {
            ll loc=get<1>(v[j]), profit=get<2>(v[j]);
            temp2[j]=mmax_up-u*(mx-loc)+profit;
            mmax_up=max(mmax_up, max(best[j],temp2[j])+u*(mx-loc));
        }

        for (int j=i; j<i+m; ++j) {
            best[j]=max({best[j],temp1[j],temp2[j]});
            ll loc=get<1>(v[j]);
            update(1,mx,1,loc,(mx-loc)*u+best[j],(loc-1)*d+best[j]);
        }

        i+=m;
    }

    cout<<best[n];
}