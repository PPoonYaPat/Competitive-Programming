#include "garden.h"
#include "gardenlib.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int n,m,dis1[300001],dis2[300001],cycle1,cycle2;
vector<int> adj[150001],adj2[300001],rev[300001];
bool vis[300001];

void new_graph(int now) {
    if (now>=n) {
        if (adj[now-n].size()>1) { //go second
            int des=adj[now-n][1];
            if (adj[des][0]==now-n) adj2[now].push_back(des+n);
            else adj2[now].push_back(des);
        } else { //go best
            int des=adj[now-n][0];
            if (adj[des][0]==now-n) adj2[now].push_back(des+n);
            else adj2[now].push_back(des);
        }
    } else { //go best
        int des=adj[now][0];
        if (adj[des][0]==now) adj2[now].push_back(des+n);
        else adj2[now].push_back(des);
    }
}

void dfs(int x, int step, int *dis, int &cycle_sz) {
    if (!vis[x]) {
        vis[x]=true;
        dis[x]=step;
        for (auto s : rev[x]) dfs(s,step+1,dis,cycle_sz);
    } else {
        cycle_sz=step;
    }
}

void count_routes(int N, int M, int P, int R[][2], int q, int g[]) {
    n=N; m=M;
    for (int i=0; i<m; ++i) {
        adj[R[i][0]].push_back(R[i][1]);
        adj[R[i][1]].push_back(R[i][0]);
    }
    for (int i=0; i<2*n; ++i) new_graph(i);
    for (int i=0; i<2*n; ++i) for (auto s : adj2[i]) rev[s].push_back(i);
    memset(dis1,0x3f,sizeof(dis1));
    memset(dis2,0x3f,sizeof(dis2));
    cycle1=cycle2=-1;

    dfs(P,0,dis1,cycle1);
    memset(vis,0,sizeof(vis));
    dfs(P+n,0,dis2,cycle2);

    for (int i=0; i<q; ++i) {
        int want=g[i],cnt=0;

        for (int node=0; node<n; ++node) {
            int have=false;

            if (dis1[node]==want) have=true;
            if (dis2[node]==want) have=true;
            if (cycle1!=-1 && want>=dis1[node] && (want-dis1[node])%cycle1==0) have=true;
            if (cycle2!=-1 && want>=dis2[node] && (want-dis2[node])%cycle2==0) have=true;

            if (have) ++cnt;
        }
        answer(cnt);
    }
}
