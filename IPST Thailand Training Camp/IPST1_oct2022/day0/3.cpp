#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,m,c[200001];
multiset<ll> s; //pos
multiset<ll, greater<ll>> val; //val

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;

    ll a,b,w;

    cin>>a>>b>>w;
    s.insert(a);
    val.insert(w);
    c[a]=w;

    if (a!=b) s.insert(b);
    if (a!=b) val.insert(w);
    if (a!=b) c[b]=w;

    cout<<w<<"\n";

    for (int i=1; i<m; ++i) {
        cin>>a>>b>>w;

        ll mmax_a=0,mmax_b=0;

        for (auto it=s.begin(); it!=s.end(); ++it) {
            mmax_a = max(mmax_a,c[*it]-abs(*it-a));
            mmax_b = max(mmax_b,c[*it]-abs(*it-b));
        }

        bool can_a=false, can_b=false;

        for (auto it=s.begin(); it!=s.end(); ++it) {
            if (c[*it]-abs(*it-b)<mmax_a+w) can_b=true;
        }

        if (can_b && mmax_a+w>c[b]) {
            for (auto it=s.begin(); it!=s.end(); ) {

                if (mmax_a+w-abs(*it-b)>=c[*it]) {
                    auto h=it;
                    val.erase(val.find(c[*it]));
                    c[*it]=0;
                    ++it;
                    s.erase(h);
                } else ++it;
            }
            c[b]=mmax_a+w;
            val.insert(mmax_a+w);
            assert(s.find(b)==s.end());
            s.insert(b);
        }

        if (a!=b) {

            for (auto it=s.begin(); it!=s.end(); ++it) {
                if (c[*it]-abs(*it-a)<mmax_b+w) can_a=true;
            }

            if (can_a && mmax_b+w>c[a]) {
                for (auto it=s.begin(); it!=s.end(); ) {

                    if (mmax_b+w-abs(*it-a)>=c[*it]) {
                        auto h=it;
                        val.erase(val.find(c[*it]));
                        c[*it]=0;
                        ++it;
                        s.erase(h);
                    } else ++it;
                }

                c[a]=mmax_b+w;
                val.insert(mmax_b+w);
                assert(s.find(a)==s.end());
                s.insert(a);
            }
        }

        cout<<max(*(val.begin()),0LL)<<"\n";
    }
}

/*
        it=s.lower_bound(a);
        can=false;
        if (it!=s.end() && c[*it]-abs(*it-a)<mmax_b+w) can=true;
        if (it!=s.begin() && c[*(--it)]-abs(*it-a)<mmax_b+w) can=true; */

/*
        auto it=s.lower_bound(b);
        bool can=false;
        if (it!=s.end() && c[*it]-abs(*it-b)<mmax_a+w) can=true;
        if (it!=s.begin() && c[*(--it)]-abs(*it-b)<mmax_a+w) can=true; */
