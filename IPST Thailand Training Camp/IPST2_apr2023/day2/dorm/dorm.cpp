#include <bits/stdc++.h>
//#include "grader.cpp"
using namespace std;
typedef long long ll;

ll n,c[3001],ss,sss;

struct A {
    ll dec,cnt,sum;
    bool operator < (const A &o) {
        return o.dec<dec;
    }
};

vector<A> v;

ll f(ll x, ll k) {
    ++k;
    return (x/k)*(x/k)*(k-(x%k)) + (x/k+1)*(x/k+1)*(x%k);
}

void init(int N,vector<vector<int>> Req) {
    n=N;
    for (int i=0; i<Req.size(); ++i) {
        ++c[Req[i][0]];
        --c[Req[i][1]+1];
    }

    for (int i=1; i<n; ++i) c[i]+=c[i-1];
    for (int i=0; i<n; ++i) ss+=c[i], sss+=c[i]*c[i];

    for (int i=0; i<n; ++i) {

        int pre=1;
        ll now=f(c[i],0)-f(c[i],1);

        while (pre<=100000) {

            int l=pre, r=100000;
            while (l<r) {
                int mid=(l+r+1)/2;
                if (f(c[i],mid-1)-f(c[i],mid)==now) l=mid;
                else r=mid-1;
            }

            v.push_back({now,l-pre+1,0});
            pre=l+1;
            now=f(c[i],pre-1)-f(c[i],pre);
        }
    }
    v.push_back({LLONG_MAX,0,0});
    sort(v.begin(),v.end());

    ll sum=0;
    ll cnt=0;
    for (int i=1; i<v.size(); ++i) {
        sum+=v[i].dec*v[i].cnt;
        v[i].sum=sum;
        cnt+=v[i].cnt;
        v[i].cnt=cnt;
    }
}


long long least_crowded(int P) {

    if (P>v.back().cnt) return ss;

    int l=0,r=v.size()-1;
    while (l<r) {
        int mid=(l+r+1)/2;
        if (v[mid].cnt<=P) l=mid;
        else r=mid-1;
    }

    return sss-(v[l].sum+(P-v[l].cnt)*v[l+1].dec);
}
