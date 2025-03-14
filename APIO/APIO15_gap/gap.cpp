#include "gap.h"
#include "grader.cpp"

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

vector<pll> v;
vector<ll> k;
ll mx,mn,ans;

ll findGap(int T, int n) {
    if (T==1) {
        ll l=0, r=1e18;
        while (k.size()<n) {
            MinMax(l,r,&mn,&mx);
            if (mn==mx) k.push_back(mn);
            else {
                k.push_back(mn);
                k.push_back(mx);
            }
            l=mn+1; r=mx-1;
        }
        sort(k.begin(),k.end());
        for (int i=1; i<k.size(); ++i) ans=max(ans,k[i]-k[i-1]);
    } else {
        MinMax(0,1e18,&mn,&mx);
        ll mmin=mn,mmax=mx;
        v.push_back(pll(mn,mn));

        ll wide=(mx-mn+n-2)/(n-1);

        for (int i=0; i<n-1; ++i) {
            if (mmin+1+wide*i > min(mmin+wide*(i+1),mmax-1)) break;
            MinMax(mmin+1+wide*i,min(mmin+wide*(i+1),mmax-1),&mn,&mx);
            if (mn!=-1) v.push_back(pll(mn,mx));
        }

        v.push_back(pll(mmax,mmax));

        for (int i=1; i<v.size(); ++i) ans=max(ans,v[i].first-v[i-1].second);
    }
    return ans;
}
/*
2 6
12 15 34 54 675 678
*/
