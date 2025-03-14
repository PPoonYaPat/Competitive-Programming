#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

pii s[1<<20];

pii merge(pii a, pii b) {return pii(min(a.first,b.first),min(a.second,b.second));};

void update(int l, int r, int idx, int x, ll val, int mode) { //0 - to left-most, 1 - right-most
    if (x>r || x<l) return;
    if (l==r) {
        if (mode==0) s[idx].first=min(s[idx].first,val);
        else s[idx].second=min(s[idx].second,val);
    } else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,val,mode);
        update(mid+1,r,2*idx+1,x,val,mode);
        s[idx]=merge(s[2*idx],s[2*idx+1]);
    }
}

pii query(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return pii(LLONG_MAX,LLONG_MAX);
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    return merge(query(l,mid,2*idx,x,y),query(mid+1,r,2*idx+1,x,y));
}

int mx,n,a[100001],b[100001],c[100001];
ll w[100001];
set<int> ss;
map<int,int> pos;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    for (int i=0; i<(1<<20); ++i) s[i]=pii(LLONG_MAX,LLONG_MAX);

    cin>>n>>mx;
    ss.insert(1);
    ss.insert(mx);
    for (int i=0; i<n; ++i) {
        cin>>a[i]>>b[i]>>c[i]>>w[i];
        ss.insert(a[i]);
        ss.insert(b[i]);
        ss.insert(c[i]);
    }

    int cnt=0;
    for (auto h : ss) pos[h]=++cnt;

    ll ans=LLONG_MAX;
    for (int i=0; i<n; ++i) {
        int l=pos[a[i]], r=pos[b[i]], hole=pos[c[i]];
        pii res=query(1,cnt,1,l,r);

        ll Ans=w[i], toL=w[i], toR=w[i];
        bool haveL=true, haveR=true;

        if (r!=cnt) {
            if (res.second==LLONG_MAX) haveR=false;
            else Ans+=res.second, toR+=res.second;
        }

        if (l!=1) {
            if (res.first==LLONG_MAX) haveL=false;
            else Ans+=res.first, toL+=res.first;
        }

        if (haveL && haveR) ans=min(ans,Ans);
        if (haveL) update(1,cnt,1,hole,toL,0);
        if (haveR) update(1,cnt,1,hole,toR,1);
    }

    if (ans==LLONG_MAX) cout<<-1;
    else cout<<ans;
}
