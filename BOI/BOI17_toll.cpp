#include <bits/stdc++.h>
using namespace std;

int k,n,m,q;
int dis[50001][17][5][5]; //(a,b,x,y) : from ak+x to (a+(1<<b))k+y

void merge(int ans[5][5], int a[5][5], int b[5][5]) {
    for (int i=0; i<k; ++i) {
        for (int j=0; j<k; ++j) {
            //find ans[i][j]
            for (int z=0; z<k; ++z) {
                ans[i][j]=min(ans[i][j],a[i][z]+b[z][j]);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>k>>n>>m>>q;
    memset(dis,0x3f,sizeof(dis));

    for (int i=0; i<m; ++i) {
        int a,b,w;
        cin>>a>>b>>w;
        dis[a/k][0][a%k][b%k]=w;
    }

    for (int i=1; i<17; ++i) {
        for (int j=0; j+(1<<i)<=n/k; ++j) {
            merge(dis[j][i],dis[j][i-1],dis[j+(1<<(i-1))][i-1]);
        }
    }

    while (q--) {
        int x,y; cin>>x>>y;
        int group=x/k;
        //from x/k to y/k

        int ans[5][5],temp[5][5];
        memset(ans,0x3f,sizeof(ans));
        for (int i=0; i<k; ++i) ans[i][i]=0;

        for (int i=16; i>=0; --i) {
            if (group+(1<<i)<=y/k) {
                memset(temp,0x3f,sizeof(temp));
                merge(temp,ans,dis[group][i]);
                swap(ans,temp);
                group+=(1<<i);
            }
        }
        if (ans[x%k][y%k]==0x3f3f3f3f) cout<<-1<<"\n";
        else cout<<ans[x%k][y%k]<<"\n";
    }
}
