#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

string s;
int n,cnt,com[20000005];
bool is_min[2000005];
vector<int> adj[2000005];

int build(int l, int r) {
    int now=++cnt;
    if (l!=r) {
        adj[now].push_back(build(l+4,com[l+3]-1));
        adj[now].push_back(build(com[l+3]+1,r-1));
        if (s[l+1]=='i') is_min[now]=true;
    }
    return now;
}

pii dfs(int x) { //return min,max
    if (adj[x].size()==0) return pii(1,n);

    pii L=dfs(adj[x][0]), R=dfs(adj[x][1]), res;
    
    if (is_min[x]) {
        res.first=min(L.first,R.first);
        res.second=L.second+R.second-n-1;
    } else {
        res.first=L.first+R.first;
        res.second=max(L.second,R.second);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>s;
    for (auto h : s) if (h=='?') ++n;

    stack<int> st;
    for (int i=0; i<s.size(); ++i) {
        if (s[i]=='(') st.push(i);
        else if (s[i]==',') com[st.top()]=i;
        else if (s[i]==')') st.pop();
    }

    pii res=dfs(build(0,s.size()-1));
    cout<<res.second-res.first+1;
}