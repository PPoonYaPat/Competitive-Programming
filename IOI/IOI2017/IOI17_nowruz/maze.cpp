#include <bits/stdc++.h>
#include <time.h>
using namespace std;
typedef pair<int,int> pii;

struct point {
    int x,y;
};
typedef pair<point,point> ppp;

int n,m,lim;
int mmax;
pii best;
string s[1050],ans[1050];
int vis[1050][1050],mark[1050][1050];
bool fre[1050][1050],ran[1050][1050];
vector<pii> adj[1050][1050];
queue<ppp> q;

void bfs(int x, int y) {
    q.push(ppp({x,y},{-1,-1}));
    vis[x][y]=true;

    while (!q.empty()) {
        int x=q.front().first.x, y=q.front().first.y;
        int px=q.front().second.x, py=q.front().second.y;
        q.pop();

        mark[x][y]=true;

        if (s[x][y]=='#') {
            ans[x][y]='#';
            continue;
        } else if (vis[x][y]>=2) {
            ans[x][y]='X';
            continue;
        }
        
        for (auto s : adj[x][y]) {
            int nx=s.first, ny=s.second;
            if (nx==x && ny==y) continue;
            if (mark[nx][ny]) continue;
            ++vis[nx][ny];
            q.push(ppp({nx,ny},{x,y}));
        }
    }
}

void solve(int stx, int sty) {
    memset(vis,0,sizeof(vis));
    memset(mark,0,sizeof(mark));
    memset(fre,0,sizeof(fre));

    for (int i=1; i<=n; ++i) {
        ans[i]=" ";
        for (int j=1; j<=m; ++j) {
            if (s[i][j]=='#') ans[i]+='#';
            else ans[i]+='.';
        }
    }

    bfs(stx,sty);
    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) if (!vis[i][j] && ans[i][j]!='#') ans[i][j]='X';

    for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) if (ans[i][j]=='.') fre[i][j]=true;

    int cnt=0;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            int x=0;
            if (ans[i][j]!='.') continue;
            if (fre[i-1][j]) ++x;
            if (fre[i+1][j]) ++x;
            if (fre[i][j-1]) ++x;
            if (fre[i][j+1]) ++x;
            if (x==1) ++cnt;
        }
    }

    if (cnt>mmax) {
        mmax=cnt;
        best=pii(stx,sty);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    srand(time(0));
    freopen("nowruz10.in.txt","r",stdin);
    freopen("nowruz10.out.txt","w",stdout);
    cin>>n>>m>>lim;
    for (int i=1; i<=n; ++i) cin>>s[i], s[i]=" "+s[i];

    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            if (s[i][j]=='.') {
                if (s[i][j+1]=='.' && j!=m) {
                    adj[i][j+1].push_back(pii(i,j));
                    adj[i][j].push_back(pii(i,j+1));
                }
                if (s[i+1][j]=='.' && i!=n) {
                    adj[i+1][j].push_back(pii(i,j));
                    adj[i][j].push_back(pii(i+1,j));
                }
            }
        }
    }
    int cc=0;
    while (cc<=200) {
        int x=rand()%n+1, y=rand()%m+1;
        if (ran[x][y]) continue;
        ran[x][y]=true;
        solve(x,y);
        ++cc;
    }

    solve(best.first,best.second);
    
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) cout<<ans[i][j];
        cout<<"\n";
    }
}