#include <bits/stdc++.h>
#include "castle.h"
#include "castle.cpp"
using namespace std;
typedef pair<int,int> pii;

int n,m,Q,y;
vector<int> A,B,v;
int in[100001],out[100001],cnt,level[100001],fen[100010],p[100001][18];
bool vis[100001],special[100020];
vector<pii> edge,adj[100001];

void dfs(int x, int parent) {
    in[x]=++cnt;
    level[x]=level[parent]+1;
    p[x][0]=parent;
    vis[x]=true;
    for (int i=1; i<18; ++i) p[x][i]=p[p[x][i-1]][i-1];

    for (auto s : adj[x]) {
        if (s.first==parent) continue;
        if (vis[s.first]) {
            if (!special[s.second]) special[s.second]=true, v.push_back(s.second);
        } else dfs(s.first,x);
    }
    out[x]=cnt;
}

void update(int x, int val) {
    while (x<=n+5) {
        fen[x]+=val;
        x+=(x&-x);
    }
}

int find(int x) {
    int sum=0;
    while (x) {
        sum+=fen[x];
        x-=(x&-x);
    }
    return sum;
}

int f(int x) { //find leader of group
    int k=find(in[x]);
    for (int i=17; i>=0; --i) {
        if (p[x][i]!=-1 && find(in[p[x][i]])==k) x=p[x][i];
    }
    return x;
}

vector<int> adj2[100001],ans;
bool vis2[100001];
int val[100];

int main() {

    freopen("in.txt","r",stdin);

    castle_init(n,m,Q,y);
    castle_read_map(A,B);

    for (int i=0; i<m; ++i) {
        adj[A[i]].push_back({B[i],i});
        adj[B[i]].push_back({A[i],i});
        edge.push_back(pii(A[i],B[i]));
    }

    dfs(0,-1);

    while (Q--) {
        int mode,st,ed;
        castle_read_event(mode,st,ed);

        if (mode==1) {
            if (special[st]) special[st]=false;
            else {
                int a=edge[st].first, b=edge[st].second;
                if (level[a]>level[b]) swap(a,b);
                update(in[b],1);
                update(out[b]+1,-1);
            }

        } else {
            vector<int> temp;
            for (auto s : v) {
                if (!special[s]) continue;
                int a=f(edge[s].first), b=f(edge[s].second);
                adj2[a].push_back(b);
                adj2[b].push_back(a);
                temp.push_back(a); temp.push_back(b);
            }

            int start=f(st), tar=f(ed), ans=0;
            temp.push_back(start); temp.push_back(tar);

            queue<int> q;
            q.push(start);

            while (!q.empty()) {
                int node=q.front();
                q.pop();

                if (vis2[node]) continue;
                vis2[node]=true;

                if (node==tar) ans=1;

                for (auto s : adj2[node]) {
                    if (!vis2[s]) q.push(s);
                }
            }
            castle_answer(ans);

            for (auto s : temp) {
                adj2[s].clear();
                vis2[s]=false;
            }
        }
    }
}


