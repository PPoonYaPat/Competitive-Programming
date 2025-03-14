#include "boxes.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll pre[10000010],suf[10000010];

long long delivery(int n, int k, int l, int pos[]) {
    sort(pos,pos+n);

    pre[0]=0;
    for (int i=0; i<n; ++i) pre[i+1]=pre[max(0,i+1-k)]+2*pos[i];

    suf[n+1]=0;
    for (int i=n-1; i>=0; --i) suf[i+1]=suf[min(n+1,i+1+k)]+2*(l-pos[i]);

    ll ans=LLONG_MAX;
    for (int i=0; i<=n; ++i) ans=min(ans,pre[i]+suf[i+1]);
    for (int i=0; i<=n-k; ++i) ans=min(ans,pre[i]+suf[i+k+1]+l);
    return ans;
}
