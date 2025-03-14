#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

int n,m,q,ans[250005],base[250005];
ll s[1<<20],lz[1<<20],fen[250050];

struct Gr {
    int val,idx,gr;
};

vector<pii> want[250005]; //number on queue and the index of ans
vector<Gr> p[250005]; //people, idx, group
vector<pii> qu[250005]; //queue, idx

ll find(int x) {
    ll sum=0;
    while (x) {
        sum+=fen[x];
        x-=x&-x;
    }
    return sum;
}

void upd(int x, ll val) {
    while (x<=q+5) {
        fen[x]+=val;
        x+=x&-x;
    }
}

void push(int l, int r, int idx) {
    s[idx]+=lz[idx];
    if (l!=r) {
        lz[2*idx]+=lz[idx];
        lz[2*idx+1]+=lz[idx];
    }
    lz[idx]=0;
}

void update(int l, int r, int idx, int x, int y, ll val) {
    push(l,r,idx);
    if (x>r || y<l) return;
    if (x<=l && r<=y) {
        lz[idx]+=val;
        push(l,r,idx);
    } else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,y,val);
        update(mid+1,r,2*idx+1,x,y,val);
        s[idx]=min(s[2*idx],s[2*idx+1]);
    }
}

ll query(int l, int r, int idx, int x, int y) {
    push(l,r,idx);
    if (x>r || y<l) return LLONG_MAX;
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    return min(query(l,mid,2*idx,x,y),query(mid+1,r,2*idx+1,x,y));
}

ll seg[1<<20]; //sum of people

void update2(int l, int r, int idx, int x, ll val) {
    if (x>r || x<l) return;
    if (l==r) seg[idx]+=val;
    else {
        int mid=(l+r)/2;
        update2(l,mid,2*idx,x,val);
        update2(mid+1,r,2*idx+1,x,val);
        seg[idx]=seg[2*idx]+seg[2*idx+1];
    }
}

int query2(int l, int r, int idx, ll want) {
    if (l==r) return l;
    int mid=(l+r)/2;
    if (seg[2*idx]>=want) return query2(l,mid,2*idx,want);
    else return query2(mid+1,r,2*idx+1,want-seg[2*idx]);
}

int f(ll want, int d) {
    if (seg[1]<want) return 0;
    int h=query2(1,q,1,want);
    if (h<=d) return h;
    else return 0;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    memset(ans,-1,sizeof(ans));
    memset(base,-1,sizeof(base));
    base[0]=0;

    cin>>n>>m>>q;
    for (int i=1; i<=q; ++i) {
        int mode; cin>>mode;
        if (mode==1) {
            int l,r,c,k; cin>>l>>r>>c>>k;
            p[l].push_back({k,i,c});
            p[r+1].push_back({-k,i,c});
        } else if (mode==2) {
            int l,r,k; cin>>l>>r>>k;
            qu[l].push_back(pii(k,i));
            qu[r+1].push_back(pii(-k,i));
        } else {
            ll a,b; cin>>a>>b;
            want[a].push_back(pii(b,i));
        }
    }

    for (int i=1; i<=n; ++i) {
        //add people
        for (auto s : p[i]) {
            update(1,q,1,s.idx,q,s.val);
            upd(s.idx,s.val);
            base[s.idx]=s.gr;
            update2(1,q,1,s.idx,s.val);
        }
        
        //add bound of queue
        for (auto s : qu[i]) update(1,q,1,s.second,q,-s.first);

        //find real queue
        for (auto s : want[i]) {
            ll want=s.first+(find(s.second)-(query(1,q,1,s.second,s.second)-min(0ll,query(1,q,1,1,s.second))));
            ans[s.second]=base[f(want,s.second)];
        }
    }

    for (int i=1; i<=q; ++i) {
        if (ans[i]!=-1) cout<<ans[i]<<"\n";
    }
}