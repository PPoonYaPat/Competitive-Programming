#include "railroad.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tu;

ll ans,cross[400010],dis[400010];
int p[400010],lv[400010];
vector<int> adj[400010];
vector<tu> v;
set<int> ss;
map<int,int> c;

void dfs(int x, int val) {
    p[x]=val;
    for (auto s : adj[x]) {
        if (p[s]==-1) dfs(s,val);
    }
}

int find(int x) {
    while (x!=p[x]) x=p[x];
    return x;
}

bool same(int x, int y) {
    return find(x)==find(y);
}

void unite(int x, int y) {
    x=find(x); y=find(y);
    if (lv[x]>lv[y]) p[y]=x;
    else if (lv[y]>lv[x]) p[x]=y;
    else {
        p[x]=y; ++lv[y];
    }
}

long long plan_roller_coaster(std::vector<int> s, std::vector<int> t) {
    int n = (int) s.size();
    memset(p,-1,sizeof(p));
    for (int i=0; i<n; ++i) {
        ss.insert(s[i]);
        ss.insert(t[i]);
    }
    ss.insert(1000000010);

    int cnt=0,pre=0;
    for (auto it=ss.begin(); it!=ss.end(); ++it) {
        if (cnt) v.push_back(tu(*it-pre,cnt,cnt-1)), dis[cnt]=*it-pre;
        c[*it]=cnt++;
        pre=*it;
    }
    --cnt;

    for (int i=0; i<n; ++i) {
        int st=c[s[i]], to=c[t[i]];
        cross[st+1]++;
        cross[to+1]--;
        adj[st].push_back(to);
    }
    adj[cnt].push_back(0);
    --cross[1];

    for (int i=1; i<=cnt; ++i) {
        cross[i]+=cross[i-1];
        if (cross[i]>0) {
            adj[i].push_back(i-1);
            ans+=dis[i]*cross[i];
        } else if (cross[i]<0) {
            adj[i-1].push_back(i);
        }
    }

    for (int i=0; i<=cnt; ++i) {
        if (p[i]==-1) dfs(i,i), lv[i]=1;
    }

    sort(v.begin(),v.end());
    for (auto s : v) {
        int a,b,w;
        tie(w,a,b)=s;

        if (!same(a,b)) {
            unite(a,b);
            ans+=w;
        }
    }

    return ans;
}

int main() {
    int n; cin>>n;
    vector<int> s,t;
    for (int i=0; i<n; ++i) {
        int x,y;
        cin>>x>>y;
        s.push_back(x);
        t.push_back(y);
    }
    cout<<plan_roller_coaster(s,t);
}
/*
4
1 7
4 3
5 8
6 6
*/
