#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,x,y;
ll bn,bs,be,bw;
int cnt;

bool examine(ll x, ll y) {
    if (x<1 || y<1 || x>n || y>n) return false;
    cout<<"examine "<<x<<" "<<y<<endl;
    string s;
    cin>>s;
    if (s=="true") return true;
    else return false;
}

ll find(ll a, ll b) {
    ll idx=0;
    while (examine(x+(a<<idx),y+(b<<idx))) ++idx;
    ll l=0, r=1<<idx;
    if (idx) l=1<<(idx-1);

    while (l+1<r) {
        ll mid=(l+r)/2;
        if (examine(x+mid*a,y+mid*b)) l=mid;
        else r=mid;
    }
    return l;
}

int main() {
    cin>>n>>x>>y;

    ll be=x+find(1,0), bw=x-find(-1,0), bn=y-find(0,-1), bs=y+find(0,1);

    ll cx=(be+bw)/2, cy=(bn+bs)/2, sz=(be-bw+1)*2;
    ll E,W,N,S;

    ll x=cx, y=cy;
    while (examine(x,y)) x+=sz;
    E=x-sz; x=cx; y=cy;
    while (examine(x,y)) x-=sz;
    W=x+sz; x=cx; y=cy;
    while (examine(x,y)) y+=sz;
    S=y-sz; x=cx; y=cy;
    while (examine(x,y)) y-=sz;
    N=y+sz; x=cx; y=cy;

    cout<<"solution "<<(E+W)/2<<" "<<(N+S)/2<<flush;
}