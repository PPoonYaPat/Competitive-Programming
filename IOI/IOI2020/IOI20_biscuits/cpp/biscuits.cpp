#include "biscuits.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll qs[60],sum[60],bag;

ll find(ll x) {
    if (x<0) return 0;
    if (x==0) return 1;
    if (x==1) return qs[0];

    int k;
    for (int i=59; i>0; --i) {
        if ((1ll<<i)<=x) {
            k=i;
            break;
        }
    }
    return qs[k-1]+find(min(x-(1ll<<k),(sum[k]/bag)-(1ll<<k)));
}

ll count_tastiness(ll X, vector<ll> a) {
    bag=X;
    sum[0]=a[0];
    if (a[0]>=bag) qs[0]=2;
    else qs[0]=1;

    for (int i=1; i<60; ++i) {
        if (i<a.size()) sum[i]=sum[i-1]+(1ll<<i)*a[i];
        else sum[i]=sum[i-1];
        qs[i]=find((1ll<<(i+1))-1);
    }

    return qs[59];
}

