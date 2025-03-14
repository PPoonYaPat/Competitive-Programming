#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
 
int n,p[200005],h[200005];
ll val[200005],Ans;
vector<int> adj[200005],adj2[400005],v[400005];
set<ll> ss[400005];
map<ll,ll> temp[400005];
bool mark[200005],vis[200005];
stack<int> st;
 
void dfs1(int x) {
    vis[x]=true;
    st.push(x);
    for (auto s : adj[x]) if (!vis[s]) dfs1(s);
}
 
void dfs2(int x) {
    for (auto s : adj2[x]) dfs2(s);
 
    if (adj2[x].size()) {
        swap(ss[x],ss[adj2[x][0]]);
        swap(temp[x],temp[adj2[x][0]]);
 
        for (int i=1; i<adj2[x].size(); ++i) {
            int c=adj2[x][i];
            if (ss[c].size()>ss[x].size()) swap(temp[x],temp[c]), swap(ss[x],ss[c]);
 
            for (auto s : ss[c]) temp[x][s]+=temp[c][s], ss[x].insert(s);
        }
    }
 
    if (x<=n) {

        temp[x][0]+=val[x]; ss[x].insert(0);
        temp[x][h[x]]-=val[x]; ss[x].insert(h[x]);
        temp[x][h[x]+1]+=val[x]; ss[x].insert(h[x]+1);
 
        if (temp[x][h[x]]<0) {
            ll k=-temp[x][h[x]];
            auto it=ss[x].find(h[x]);
 
            temp[x][h[x]]=0;
            auto h=it; --it;
            ss[x].erase(h);
 
            while (true) {
                if (temp[x][*it]<k) {
                    k-=temp[x][*it];
                    temp[x][*it]=0;
                    auto h=it; --it;
                    ss[x].erase(h);
                } else {
                    temp[x][*it]-=k;
                    if (temp[x][*it]==0) ss[x].erase(it);
                    break;
                }
            }
        }
 
    } else {
        
        for (auto s : v[x]) {
            temp[x][0]+=val[s]; ss[x].insert(0);
            temp[x][h[s]]-=val[s]; ss[x].insert(h[s]);
            temp[x][h[s]+1]+=val[s]; ss[x].insert(h[s]+1);
        }
 
        ll sum=0;
        Ans=LLONG_MAX;
 
        for (auto s : ss[x]) {
            sum+=temp[x][s];
            Ans=min(Ans,sum);
        }
 
    }

    
}
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=1; i<=n; ++i) {
        cin>>p[i]>>h[i]>>val[i];
        adj[p[i]].push_back(i);
    }
 
    ll ans=0;
    for (int i=1; i<=n; ++i) {
        if (!vis[i]) {
            int x=i;
            dfs1(x);
            while (!vis[p[x]]) {
                x=p[x];
                dfs1(x);
            }
 
            int idx=p[x];
            while (idx!=x) {
                mark[idx]=true;
                v[n+x].push_back(idx);
                idx=p[idx];
            }
            mark[x]=true;
            v[n+x].push_back(x);
 
            while (st.size()) {
                int node=st.top();
                st.pop();
                if (mark[node]) for (auto s : adj[node]) {
                    if (mark[s]) continue;
                    if (node!=p[x] || s!=x) adj2[n+x].push_back(s);
                } else for (auto s : adj[node]) adj2[node].push_back(s);
            }
 
            dfs2(n+x);
            ans+=Ans;
        }
    }
    cout<<ans;
}