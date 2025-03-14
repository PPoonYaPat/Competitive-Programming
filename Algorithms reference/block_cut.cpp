#include <bits/stdc++.h>
using namespace std;

int cnt_group=0;
vector<int> adj[6000005],group[6000005];
stack<int> st;

int disc[6000005],lw[6000005],cnt;
bool cant[6000005];

void dfs(int x, int par) {
    st.push(x);
    lw[x]=disc[x]=++cnt;
 
    for (auto s : adj[x]) {
        if (s==par) continue;
        if (disc[s]) lw[x]=min(lw[x],disc[s]);
        else {
            dfs(s,x);
            lw[x]=min(lw[x],lw[s]);
 
            if (lw[s]>=disc[x]) {
                ++cnt_group;
                group[cnt_group].push_back(x);

                while (group[cnt_group].back()!=s) {
                    group[cnt_group].push_back(st.top());
                    st.pop();
                }
            }
        }
    }
}