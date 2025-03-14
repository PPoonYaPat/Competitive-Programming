#include <bits/stdc++.h>
using namespace std;

bool fre[1050][1050];
int cnt,n=256,m=256;
string s[1050];
bool vis[1050][1050];

void dfs(int x, int y) {
    if (vis[x][y]) return;
    vis[x][y]=true;
    s[x][y]='P';
    
    if (fre[x-1][y]) dfs(x-1,y);
    if (fre[x+1][y]) dfs(x+1,y);
    if (fre[x][y-1]) dfs(x,y-1);
    if (fre[x][y+1]) dfs(x,y+1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("nowruz4.out.txt","r",stdin);
    //freopen("nowruz2.out.txt","a",stdout);

    for (int i=1; i<=n; ++i) cin>>s[i], s[i]=" "+s[i];

    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) if (s[i][j]=='.') fre[i][j]=true;

    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            int x=0;
            if (s[i][j]!='.') continue;
            if (fre[i-1][j]) ++x;
            if (fre[i+1][j]) ++x;
            if (fre[i][j-1]) ++x;
            if (fre[i][j+1]) ++x;
            if (x==1) ++cnt;
        }
    }
    dfs(1,1);

    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) if (s[i][j]=='.') cout<<"bruh";
    //for (int i=1; i<=n; ++i) cout<<s[i]<<"\n";

    cout<<cnt;
}