#include "colorful.h"
//#include "grader.cpp";
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

struct A {
    int group,order,power;
} to_group[50001][401]; //node, color

queue<pii> q;
int cnt=-1,vis[50001][401]; //0 : not, 1 : this cycle, 2 : old cycle
vector<pii> G[50001]; //node,color
vector<int> adj[50001],prime;
bool notPrime[50001];
int k;

pii dfs(int x, int col) { //group and (0,1) 0 : incomplete cycle, 1 : complete cycle

    if (vis[x][col]==2) {
        return pii(to_group[x][col].group,1);

    } else if (vis[x][col]==1) {
        G[++cnt].push_back(pii(x,col));
        return pii(cnt,0);

    } else {

        vis[x][col]=1;
        q.push(pii(x,col));

        int nxt=x,mmin=INT_MAX;

        for (auto s : adj[x]) {
            if (s%prime[col]<mmin) {
                mmin=s%prime[col];
                nxt=s;
            } else if (s%prime[col]==mmin && s<nxt) nxt=s;
        }

        int nxt_col=(col+1)%k;

        pii a=dfs(nxt,nxt_col);
        int g=a.first; // g is number of the cycle

        if (G[g][0].first==x && G[g][0].second==col) { //complete group

            reverse(G[g].begin(),G[g].end());
            for (int i=0; i<G[g].size(); ++i) {
                to_group[G[g][i].first][G[g][i].second]={g,i,0};
            }

            return pii(g,1);

        } else {

            if (a.second==0) {
                G[g].push_back(pii(x,col));
                return pii(g,0);

            } else {
                to_group[x][col]={to_group[nxt][nxt_col].group,to_group[nxt][nxt_col].order,to_group[nxt][nxt_col].power+1};
                return pii(g,1);
            }

        }
    }


}

void init_machine(int N, int M, int K, int Q, vector<int> x, vector<int> y) {
    k=K;
    for (int i=0; i<M; ++i) {
        adj[x[i]].push_back(y[i]);
        adj[y[i]].push_back(x[i]);
    }

    for (int i=2; i<3000; ++i) {
        if (!notPrime[i]) {
            prime.push_back(i);
            if (prime.size()==K) break;
            for (int j=2; j<3000/i; ++j) notPrime[i*j]=true;
        }
    }
}

int dfs_noop(int x, int col, int dis) {
    int nxt,mmin=INT_MAX;

    if (dis==0) return x;

    for (auto s : adj[x]) {
        if (s%prime[col]<mmin) {
            mmin=s%prime[col];
            nxt=s;
        } else if (s%prime[col]==mmin && s<nxt) nxt=s;
    }

    return dfs_noop(nxt,(col+1)%k,dis-1);
}

int send_ball(int c, int s, ll t){

    if (vis[s][c]==0) {
        dfs(s,c);
        while (!q.empty()) {
            vis[q.front().first][q.front().second]=2;
            q.pop();
        }
    }

    int group=to_group[s][c].group, ord=to_group[s][c].order, power=to_group[s][c].power;

    int S=s,C=c;

    if (power>t) { //linear
        return dfs_noop(s,c,t);

    } else { //loop
        t-=power;
        t%=(int)(G[group].size());

        return G[group][(ord+t)%(int)(G[group].size())].first;
    }
}
/*
4 3 400 3
4 3
1 2
2 3
1 2 0
0 1 3
1 4 2

4 3 400 0
4 3
1 2
2 3
*/
