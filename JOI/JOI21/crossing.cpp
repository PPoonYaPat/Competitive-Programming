#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

const ll mod=1e9+7,hs1=31,hs2=101;
pii s[1<<19];
ll lz[1<<19],pow1[200005],pow2[200005],sum1[200005],sum2[200005];
int n;
string sa,sb,sc;
map<pii,bool> have;

void push(int l, int r, int idx) {
    if (lz[idx]) {
        s[idx].first=(lz[idx]*sum1[r-l+1]*pow1[l])%mod;
        s[idx].second=(lz[idx]*sum2[r-l+1]*pow2[l])%mod;
        if (l!=r)  {
            lz[2*idx]=lz[idx];
            lz[2*idx+1]=lz[idx];
        }
        lz[idx]=0;
    }
}

void update(int l, int r, int idx, int x, int y, int val) {
    push(l,r,idx);
    if (x>r || y<l) return;
    if (x<=l && r<=y) {
        lz[idx]=val;
        push(l,r,idx);
    } else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,y,val);
        update(mid+1,r,2*idx+1,x,y,val);
        s[idx].first=(s[2*idx].first+s[2*idx+1].first)%mod;
        s[idx].second=(s[2*idx].second+s[2*idx+1].second)%mod;
    }
}

void check() {
    push(0,n-1,1);
    if (have[s[1]]) cout<<"Yes\n";
    else cout<<"No\n";
}

string merge(string a, string b) {
    string res="";
    for (int i=0; i<n; ++i) {
        if (a[i]==b[i]) res+=a[i];
        else {
            map<char,bool> have;
            have[a[i]]=true;
            have[b[i]]=true;
            if (!have['J']) res+='J';
            if (!have['O']) res+='O';
            if (!have['I']) res+='I';
        }
    }
    return res;
}

pii to_hash(string a) {
    ll res1=0,res2=0;
    for (int i=0; i<n; ++i) {
        if (a[i]=='J') {
            res1=(res1+pow1[i])%mod;
            res2=(res2+pow2[i])%mod;
        } else if (a[i]=='O') {
            res1=(res1+2*pow1[i])%mod;
            res2=(res2+2*pow2[i])%mod;
        } else {
            res1=(res1+3*pow1[i])%mod;
            res2=(res2+3*pow2[i])%mod;
        }
    }
    return pii(res1,res2);
}

void f(vector<string> v) {
    string res=v[0];
    for (int i=1; i<v.size(); ++i) res=merge(res,v[i]);
    have[to_hash(res)]=true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    pow1[0]=1; sum1[1]=1;
    pow2[0]=1; sum2[1]=1;
    for (int i=1; i<=200003; ++i) pow1[i]=(pow1[i-1]*hs1)%mod, pow2[i]=(pow2[i-1]*hs2)%mod;
    for (int i=2; i<=200003; ++i) sum1[i]=(sum1[i-1]+pow1[i-1])%mod, sum2[i]=(sum2[i-1]+pow2[i-1])%mod;
    cin>>n>>sa>>sb>>sc;

    f({sa}); f({sb}); f({sc});
    f({sa,sb}); f({sb,sc}); f({sc,sa});
    f({sa,sb,sc}); f({sb,sc,sa}); f({sc,sa,sb});
    
    int m; string st;
    cin>>m>>st;
    for (int i=0; i<n; ++i) {
        if (st[i]=='J') update(0,n-1,1,i,i,1);
        else if (st[i]=='O') update(0,n-1,1,i,i,2);
        else update(0,n-1,1,i,i,3);
    }
    check();

    while (m--) {
        int l,r; char c;
        cin>>l>>r>>c;
        --l; --r;
        if (c=='J') update(0,n-1,1,l,r,1);
        else if (c=='O') update(0,n-1,1,l,r,2);
        else update(0,n-1,1,l,r,3);
        check();
    }
}