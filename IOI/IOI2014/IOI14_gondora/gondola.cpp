#include "gondola.h"
#include "grader.cpp"

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod=1000000009;
int head[250001];


int valid(int n, int s[]) {

    for (int i=0; i<n; ++i) {
        if (s[i]<=n) {
            int val=s[i];
            for (int j=i+1; j<n; ++j) {
                ++val;
                if (val>n) val-=n;
                if (s[j]<=n && s[j]!=val) return 0;
            }
            break;
        }
    }

    sort(s,s+n);
    for (int i=1; i<n; ++i) if (s[i]==s[i-1]) return 0;

  	return 1;
}

int replacement(int n, int s[], int ans[]) {
    int mmax=0,hm,sc=0;
    bool fix=false;
    for (int i=0; i<n; ++i) {
        mmax=max(mmax,s[i]);
        if (s[i]<=n) {
            fix=true;
            if (sc==0) sc=i;
        }
    }

    if (!fix) {
        for (int i=0; i<n; ++i) {
            head[s[i]]=i+1;
        }
    } else {
        int val=s[sc];
        for (int i=sc; i<n; ++i) {
            head[s[i]]=val++;
            if (val>n) val-=n;
        }
      	for (int i=0; i<sc; ++i) {
          	head[s[i]]=val++;
          	if (val>n) val-=n;
        }
    }
    hm=head[mmax];

    int idx=0;
    for (int i=n+1; i<mmax; ++i) {
        if (!head[i]) {
            ans[idx++]=hm;
            hm=i;
        } else {
            ans[idx++]=head[i];
        }
    }
    ans[idx]=hm;

    return mmax-n;
}

ll power(int x, int y) {
    if (y==0) return 1;
    ll a[30],ans=1;
    a[0]=x;

    for (int i=1; i<=30; ++i) {
        ll h=(a[i-1]*a[i-1])%mod;
        a[i]=h;
    }

    for (int i=0; i<=30; ++i) {
        if (y&(1<<i)) {
            ll h=(ans*a[i])%mod;
            ans=h;
        }
    }
    return ans;
}

int countReplacement(int n, int s[]) {
    if (!valid(n,s)) return 0;

    ll ans=1;
    vector<int> v;

    int cnt=n;

    for (int i=0; i<n; ++i) {
        if (s[i]<=n) --cnt;
        else v.push_back(s[i]);
    }

    if (cnt==n) ans=n;

    v.push_back(n);
    sort(v.begin(),v.end());

    for (int i=1; i<v.size(); ++i) {
        ll h=(ans*power(cnt,v[i]-v[i-1]-1))%mod;
        ans=h;
        --cnt;
    }

    return ans;
}
