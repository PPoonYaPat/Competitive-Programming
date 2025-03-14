#include "game.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int n,p[1501],d[1501][1501];

int find(int x) {
    while (x!=p[x]) x=p[x];
    return x;
}

void initialize(int N) {
    n=N;
    for (int i=0; i<n; ++i) {
        p[i]=i;
        for (int j=0; j<n; ++j) d[i][j]=d[j][i]=1;
    }
}

int hasEdge(int u, int v) {
    u=find(u); v=find(v);
    if (u==v) return 1;
    if (d[u][v]==1) {
        p[v]=u;
        for (int i=0; i<n; ++i) {
            if (p[i]==i && i!=u) { //leader of component
                d[u][i]=d[i][u]=d[u][i]+d[v][i];
            }
        }
        return 1;
    } else {
        --d[u][v];
        --d[v][u];
        return 0;
    }
}
