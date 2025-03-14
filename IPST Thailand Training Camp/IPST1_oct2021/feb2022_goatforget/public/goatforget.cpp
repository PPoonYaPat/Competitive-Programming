#include "goatforget.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int cnt,N;
queue<pii> qq[101];
vector<int> adj[101];
bool vis[101][101],have[101];

int check(int node) {
    int l=qq[node].front().first, r=qq[node].front().second;
    qq[node].pop();

    int mid=(l+r+1)/2, des=talk_tae(mid);

    if (des<=r && des>=l) {
        if (des<mid) {
            if (des-1>=l) qq[node].push(pii(l,des-1));
            if (2*mid-des<=r) qq[node].push(pii(2*mid-des,r));
        } else {
            if (des+1<=r) qq[node].push(pii(des+1,r));
            if (2*mid-des-1>=l) qq[node].push(pii(l,2*mid-des-1));
        }
    }

    if (!vis[node][des]) adj[node].push_back(des), --cnt;
    vis[node][des]=vis[des][node]=true;

    queue<pii> temp;

    while ((qq[des].front().first>node || qq[des].front().second<node) && !qq[des].empty()) {
        temp.push(qq[des].front());
        qq[des].pop();
    }

    if (!qq[des].empty()) {
        int ll=qq[des].front().first, rr=qq[des].front().second;
        qq[des].pop();

        if (node+1<=rr) qq[des].push(pii(node+1,rr));
        if (node-1>=ll) qq[des].push(pii(ll,node-1));
    }

    while (!temp.empty()) {
        qq[des].push(temp.front());
        temp.pop();
    }

    return des;
}

void dfs(int x, int par) {
    if (cnt==0) return;
    int des=-1;
    while (!qq[x].empty()) {
        des=check(x);
        talk_tae(x);
    }
    have[x]=true;
    for (auto s : adj[x]) if (!have[s] && cnt!=0) talk_tae(s), dfs(s,x);
    if (cnt==0) return;
    talk_tae(par);
}

vector<vector<int> > recover_map(int n, int m, int q){
    N=n;
    cnt=m;
    vector<vector<int>> ans;
    for (int i=0; i<n; ++i) qq[i].push(pii(0,n-1));
    dfs(0,0);
    for (int i=0; i<n; ++i) {
        for (auto s : adj[i]) {
            vector<int> k;
            k.push_back(i);
            k.push_back(s);
            ans.push_back(k);
        }
    }
    return ans;
}
/*
5 4 200
0 1
1 2
2 3
3 4

4 3 200
0 1
1 2
2 3
*/
