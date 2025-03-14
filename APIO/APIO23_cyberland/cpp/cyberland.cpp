#include "cyberland.h"
#include "stub.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef pair<int,ld> pii;

struct NN {
    ld d;
    int node,half;
    bool zer;
    bool operator < (const NN &o) const {return d>o.d;}
};

double solve(int N, int M, int K, int H, vector<int> x, vector<int> y, vector<int> c, vector<int> arr) {
    int n=N,m=M,k=min(K,70),st=H;
    vector<pii> adj[n];
    ld dis[n][k+5][2];
    bool vis[n][k+5][2];
    for (int i=0; i<n; ++i) for (int j=0; j<=k; ++j) dis[i][j][0]=DBL_MAX, dis[i][j][1]=DBL_MAX, vis[i][j][0]=false, vis[i][j][1]=false;

    for (int i=0; i<m; ++i) {
        adj[x[i]].push_back(pii(y[i],c[i]));
        adj[y[i]].push_back(pii(x[i],c[i]));
    }

    priority_queue<NN> q;
    dis[st][0][0]=0;
    q.push({dis[st][0][0],st,0,0});
    bool bef=false;

    while (!q.empty()) {
        int node=q.top().node, half=q.top().half;
        bool zer=q.top().zer;
        q.pop();

        if (vis[node][half][zer]) continue;
        vis[node][half][zer]=true;

        if (node==st) {
            if (!bef) bef=true;
            else continue;
        }
        if (node==0) return (double)(dis[node][half][zer]);

        for (auto s : adj[node]) {
            int des=s.first;
            ld w=s.second;

            if (zer==true) w=0;
            else w=w/pow(2,half);

            if (arr[node]==1) {
                if (dis[des][half][zer]>dis[node][half][zer]+w) {
                    dis[des][half][zer]=dis[node][half][zer]+w;
                    q.push({dis[des][half][zer],des,half,zer});
                }
            } else if (arr[node]==0) {
                if (dis[des][half][true]>dis[node][half][zer]) {
                    dis[des][half][true]=dis[node][half][zer];
                    q.push({dis[des][half][true],des,half,true});
                }
            } else {
                //don't use
                if (dis[des][half][zer]>dis[node][half][zer]+w) {
                    dis[des][half][zer]=dis[node][half][zer]+w;
                    q.push({dis[des][half][zer],des,half,zer});
                }

                //use
                if (half<k) {
                    if (dis[des][half+1][zer]>dis[node][half][zer]+w/2.0) {
                        dis[des][half+1][zer]=dis[node][half][zer]+w/2.0;
                        q.push({dis[des][half+1][zer],des,half+1,zer});
                    }
                }
            }

        }
    }
    return -1;
}
