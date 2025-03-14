#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int ma[100005],mi[100005],n,m,k;
const int mx=100003;
vector<int> chma[100005][2],chmi[100005][2];
multiset<int> smi;
multiset<int,greater<int>> sma;

pii merge(pii a, pii b) {return {min(a.first,b.first),max(a.second,b.second)};}

pii s[1<<18][18];

void build(int l, int r, int idx, int tree) {
    if (l==r) {
        s[idx][tree]=pii(mi[l],ma[l]);
    } else {
        int mid=(l+r)/2;
        build(l,mid,2*idx,tree);
        build(mid+1,r,2*idx+1,tree);
        s[idx][tree]=merge(s[2*idx][tree],s[2*idx+1][tree]);
    }
}

void update(int l, int r, int idx, int x, int mmax, int mmin, int tree) {
    if (x>r || x<l) return;
    if (l==r) s[idx][tree]=merge(s[idx][tree],pii(mmin,mmax));
    else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,mmax,mmin,tree);
        update(mid+1,r,2*idx+1,x,mmax,mmin,tree);
        s[idx][tree]=merge(s[2*idx][tree],s[2*idx+1][tree]);
    }
}

pii query(int l, int r, int idx, int x, int y, int tree) {
    if (x>r || y<l) return pii(INT_MAX,-INT_MAX);
    if (x<=l && r<=y) return s[idx][tree];
    int mid=(l+r)/2;
    return merge(query(l,mid,2*idx,x,y,tree),query(mid+1,r,2*idx+1,x,y,tree));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    for (int i=0; i<=100003; ++i) for (int j=0; j<18; ++j) s[i][j]=pii(INT_MAX,-INT_MAX);
    cin>>n>>k>>m;
    for (int i=0; i<m; ++i) {
        int a,b; cin>>a>>b;
        if (a<b) {
            chma[a][0].push_back(b);
            chma[min(a+k-1,b)][1].push_back(b);
        } else {
            chmi[a][0].push_back(b);
            chmi[max(a-k+1,b)][1].push_back(b);
        }
    }

    for (int i=1; i<=n; ++i) {
        for (auto s : chma[i][0]) sma.insert(s);
        if (sma.empty()) ma[i]=i;
        else ma[i]=*(sma.begin());

        for (auto s : chma[i][1]) sma.erase(sma.find(s));
    }

    for (int i=n; i>=1; --i) {
        for (auto s : chmi[i][0]) smi.insert(s);
        if (smi.empty()) mi[i]=i;
        else mi[i]=*(smi.begin());
        for (auto s : chmi[i][1]) smi.erase(smi.find(s));
    }

    build(1,n,1,0);
    for (int tr=1; tr<18; ++tr) {
        for (int i=1; i<=n; ++i) {
            pii res=query(1,n,1,mi[i],ma[i],tr-1);

            mi[i]=res.first;
            ma[i]=res.second;
        }
        build(1,n,1,tr);
    }

    int q; cin>>q;
    while (q--) {
        int st,ed; cin>>st>>ed;
        if (ed<mi[st] || ma[st]<ed) cout<<-1<<"\n";
        else {
            int ans=0,L=st,R=st;

            for (int tr=17; tr>=0; --tr) {
                pii res=query(1,n,1,L,R,tr);
                if (res.first<=ed && ed<=res.second) continue;
                ans+=(1<<tr);
                L=res.first;
                R=res.second;
            }

            cout<<ans+1<<"\n";
        }
    }
}