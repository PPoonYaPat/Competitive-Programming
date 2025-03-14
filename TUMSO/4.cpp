#include <bits/stdc++.h>
using namespace std;

struct A {
    int dis,node;
};

int n,mmax,cnt;
vector<int> adj[500001];
set<int> t[500001];
queue<A> q;

void make(int a, int b) {
    adj[a].push_back(b);
    adj[b].push_back(a);
}

int main() {
    cin>>n;

    for (int i=1; i<=n; ++i) {
        if (i!=n) {
            for (int j=1; j<=i; ++j) {
                make(j+cnt,j+cnt+i);
                make(j+cnt,j+cnt+i+1);
            }
        }

        for (int j=1; j<i; ++j) make(j+cnt,j+cnt+1);
        cnt+=i;
    }

    int ax,ay,bx,by;
    cin>>ax>>ay>>bx>>by;

    q.push({0,ax*(ax-1)/2 + ay});

    while (!q.empty()) {
        A k=q.front();
        q.pop();

        if (k.dis<2*n) {
            for (auto s : adj[k.node]) if (t[k.dis+1].find(s)==t[k.dis+1].end()) q.push({k.dis+1,s}), t[k.dis+1].insert(s);
        }
    }

    q.push({0,bx*(bx-1)/2 + by});

    while (!q.empty()) {
        A k=q.front();
        q.pop();

        mmax=max(mmax,k.dis);

        for (auto s : adj[k.node]) {
            if (t[k.dis+1].find(s)==t[k.dis+1].end()) q.push({k.dis+1,s}), t[k.dis+1].insert(s);
        }
    }

    cout<<mmax+1;
}
