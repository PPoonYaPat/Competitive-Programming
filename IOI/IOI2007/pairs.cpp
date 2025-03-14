#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

struct A {
    int a1,a2,a3,a4;
} s[100001];

bool cmp(A m, A n) {
    return m.a1<n.a1;
}

int t,n,d,m,a[100001],fen[200001],f[250][250][250];
pii p[100001];
ll ans=0;

void solve1() {
    for (int i=0; i<n; ++i) cin>>a[i];
    sort(a,a+n);

    int i=0,j=0;
    while (i<n) {
        while (a[j]<=a[i]+d && j<n) ++j;
        ans+=(j-i-1);
        ++i;
    }
    cout<<ans;
}

void update2(int x, int val) {
    while (x<=2*m) {
        fen[x]+=val;
        x+=(x&-x);
    }
}

int query2(int x) {
    int sum=0;
    while (x) {
        sum+=fen[x];
        x-=(x&-x);
    }
    return sum;
}

void solve2() {
    for (int i=0; i<n; ++i) {
        int x,y;
        cin>>x>>y;
        p[i]={x+y,x-y+m};
    }
    sort(p,p+n);

    for (int i=0, j=0; i<n; ++i) {
        while (p[j].first+d<p[i].first && j<n) update2(p[j++].second,-1);
        ans+=(query2(min(p[i].second+d,2*m))-query2(max(0,p[i].second-d-1)));
        update2(p[i].second,1);
    }
    cout<<ans;
}

int query3(int x, int y, int z) {
    int sum=0;
    int tx=x,ty=y,tz=z;
    while (tx) {
        while (ty) {
            while (tz) {
                sum+=f[tx][ty][tz];
                tz-=(tz&-tz);
            }
            ty-=(ty&-ty);
            tz=z;
        }
        tx-=(tx&-tx);
        ty=y;
    }
    return sum;
}

void update3(int x, int y, int z, int val) {
    int tx=x,ty=y,tz=z;
    while (tx<=3*m) {
        while (ty<=3*m) {
            while (tz<=3*m) {
                f[tx][ty][tz]+=val;
                tz+=(tz&-tz);
            }
            ty+=(ty&-ty);
            tz=z;
        }
        tx+=(tx&-tx);
        ty=y;
    }
}

void solve3() {
    for (int i=0; i<n; ++i) {
        int x,y,z;
        cin>>x>>y>>z;
        s[i]={x+y+z,-x+y+z+m,x-y+z+m,x+y-z+m};
    }
    sort(s,s+n,cmp);
    for (int i=0, j=0; i<n; ++i) {
        while (s[j].a1+d<s[i].a1 && j<n) {
            update3(s[j].a2,s[j].a3,s[j].a4,-1);
            ++j;
        }
        int lx=max(1,s[i].a2-d), rx=min(3*m,s[i].a2+d);
        int ly=max(1,s[i].a3-d), ry=min(3*m,s[i].a3+d);
        int lz=max(1,s[i].a4-d), rz=min(3*m,s[i].a4+d);
        ans+=(query3(rx,ry,rz)-query3(rx,ry,lz-1)-query3(rx,ly-1,rz)-query3(lx-1,ry,rz));
        ans+=(query3(rx,ly-1,lz-1)+query3(lx-1,ry,lz-1)+query3(lx-1,ly-1,rz)-query3(lx-1,ly-1,lz-1));
        update3(s[i].a2,s[i].a3,s[i].a4,1);
    }
    cout<<ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>t>>n>>d>>m;
    if (t==1) solve1();
    else if (t==2) solve2();
    else solve3();
}