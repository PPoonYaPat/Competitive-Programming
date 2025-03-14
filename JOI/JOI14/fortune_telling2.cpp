#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,k,s[1<<19],q[200001],fen[600010];
long long ans;
map<int,int> mp;
priority_queue<pii> pq;
vector<int> v[200010];

struct node {
    int a,b;
    bool operator < (const node &o) {
        return max(a,b)>max(o.a,o.b);
    }
} c[200001];

void update(int l, int r, int idx, int x, int val) {
    if (x>r || x<l) return;
    if (l==r) s[idx]=val;
    else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,val);
        update(mid+1,r,2*idx+1,x,val);
        s[idx]=max(s[2*idx],s[2*idx+1]);
    }
}


int query(int l, int r, int idx, int val) { //find the first element from left that's more than val
    if (l==r) return l;
    else {
        int mid=(l+r)/2;
        if (s[2*idx+1]>=val) return query(mid+1,r,2*idx+1,val);
        else return query(l,mid,2*idx,val);
    }
}

int f(int x) {
    if (s[1]<x) return 0;
    else return query(1,k,1,x);
}

int find(int x) {
    int sum=0;
    while (x) {
        sum+=fen[x];
        x-=x&-x;
    }
    return sum;
}

void upd(int x) {
    while (x<=600005) {
        ++fen[x];
        x+=x&-x;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>k;
    for (int i=1; i<=n; ++i) {
        cin>>c[i].a>>c[i].b;
        mp[c[i].a]=0; mp[c[i].b]=0;
    }
    sort(c+1,c+n+1);

    for (int i=1; i<=k; ++i) {
        cin>>q[i];
        pq.push(pii(q[i],i));
        update(1,k,1,i,q[i]);
        mp[q[i]]=0;
    }
    int idx=0;
    for (auto it=mp.begin(); it!=mp.end(); ++it) (*it).second=++idx;

    for (int i=1; i<=n; ++i) {
        while (!pq.empty() && pq.top().first>=max(c[i].a,c[i].b)) {
            update(1,k,1,pq.top().second,0);
            pq.pop();
        }
        v[f(min(c[i].a,c[i].b))].push_back(i);
    }

    int cnt=0;
    for (int i=k; i>0; --i) {
        for (auto x : v[i]) {
            if ((cnt-find(mp[max(c[x].a,c[x].b)]-1))%2==0) ans+=max(c[x].a,c[x].b);
            else ans+=min(c[x].a,c[x].b);
        }
        upd(mp[q[i]]); ++cnt;
    }

    for (auto x : v[0]) {
        if ((cnt-find(mp[max(c[x].a,c[x].b)]-1))%2==0) ans+=c[x].a;
        else ans+=c[x].b;
    }
    cout<<ans;
}
