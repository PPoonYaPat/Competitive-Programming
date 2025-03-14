#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct A {
    int x,y;
} s[100001];

bool cmp(A a, A b) {
    return a.x+a.y<b.x+b.y;
}

int n,k;
ll ans,rsum,lsum,con,g[100001];

priority_queue<int> lsq;
priority_queue<int, vector<int>, greater<int>> rsq;

void add(int x) {
    int median = lsq.empty() ? 1000000002 : lsq.top();

    if (x<=median) lsq.push(x), lsum+=x;
    else rsq.push(x), rsum+=x;

    if (lsq.size() < rsq.size()) {
        int k=rsq.top();
        rsq.pop();
        lsq.push(k);
        rsum-=k;
        lsum+=k;
    }

    if (lsq.size() > rsq.size()+1) {
        int k=lsq.top();
        lsq.pop();
        rsq.push(k);
        rsum+=k;
        lsum-=k;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>k>>n;
    int idx=0;
    for (int i=0; i<n; ++i) {
        char a,b;
        int x,y;
        cin>>a>>x>>b>>y;
        if (a==b) con+=abs(x-y);
        else s[idx++]={x,y}, ++con;
    }
    sort(s,s+idx,cmp);

    for (int i=0; i<idx; ++i) add(s[i].x), add(s[i].y), g[i]=rsum-lsum;
    ans=rsum-lsum+con;

    if (k==1) {
        cout<<ans;
        return 0;
    }

    while (!lsq.empty()) lsq.pop();
    while (!rsq.empty()) rsq.pop();

    lsum=0; rsum=0;
    for (int i=idx-1; i>0; --i) {
        add(s[i].x); add(s[i].y);
        ans=min(ans,rsum-lsum+g[i-1]+con);
    }
    cout<<ans;
}