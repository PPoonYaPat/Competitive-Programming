#include <bits/stdc++.h>
using namespace std;

int n,d;
vector<int> adj[200001];
deque<int> temp[200001];

void dfs(int x) {

    for (auto s : adj[x]) dfs(s);

    if (adj[x].size()==0) temp[x].push_front(1);
    else {
        int sum=1;
        if (temp[adj[x][0]].size()>=d) sum+=temp[adj[x][0]][d-1];
        swap(temp[x],temp[adj[x][0]]);

        for (int j=1; j<adj[x].size(); ++j) {
            int c=adj[x][j];
            if (temp[c].size()>=d) sum+=temp[c][d-1];
            if (temp[x].size()<temp[c].size()) swap(temp[x],temp[c]);

            for (int i=0; i<temp[c].size(); ++i) {
                if (2*(i+1)<d) {
                    if (temp[c].size()>=d-i-1) temp[x][i]=max(temp[x][i]+temp[c][d-2-i],temp[c][i]+temp[x][d-2-i]);
                    else if (temp[x].size()>=d-i-1) temp[x][i]=max(temp[x][i],temp[c][i]+temp[x][d-2-i]);
                    else temp[x][i]=max(temp[x][i],temp[c][i]);
                } else temp[x][i]+=temp[c][i];
            }

            for (int i=min((int)(temp[x].size())-2,(int)(temp[c].size())-1); i>=0; --i) temp[x][i]=max(temp[x][i],temp[x][i+1]);
        }
        temp[x].push_front(max(sum,temp[x][0]));
    }
    while (temp[x].size()>d) temp[x].pop_back();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>d;
    for (int i=1; i<n; ++i) {
        int x; cin>>x;
        adj[x].push_back(i);
    }
    dfs(0);
    cout<<temp[0].front();
}