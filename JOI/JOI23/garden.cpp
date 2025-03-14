#include <bits/stdc++.h>
using namespace std;

struct List {
    int bef,nxt;
} c[5005];

int n,m,d,last_use[5005],at_least,mmin,mi,ma;
vector<int> temp;
bool haveA[5005],haveB[5005][5005];
queue<int> gone[5005],typeA;

void reset() {
    mmin=INT_MAX;
    
    int pre=-1;
    for (int i=0; i<d; ++i) {
        if (last_use[i]!=-1) {
            c[i].bef=pre;
            c[i].nxt=-1;
            
            if (pre!=-1) c[pre].nxt=i, mmin=min(mmin,d+pre-i+1);
            else mi=i;

            pre=i;
            ma=i;
        }
    }
    mmin=min(mmin,ma-mi+1);
}

void Del(int x) {
    int bef=c[x].bef, nxt=c[x].nxt;

    if (bef==-1) {
        mi=nxt;
        c[nxt].bef=-1;
        mmin=min(mmin,ma-mi+1);
    } else if (nxt==-1) {
        ma=bef;
        c[bef].nxt=-1;
        mmin=min(mmin,ma-mi+1);
    } else {
        c[bef].nxt=nxt;
        c[nxt].bef=bef;
        mmin=min(mmin,d+bef-nxt+1);
    }

}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    memset(last_use,-1,sizeof(last_use));

    cin>>n>>m>>d;
    for (int i=0; i<n; ++i) {
        int a,b; cin>>a>>b;
        haveA[a]=true;
        at_least=max(at_least,a);
        last_use[b]=2*d+3;
    }
    for (int i=0; i<m; ++i) {
        int a,b; cin>>a>>b;
        haveB[b][a]=true;
        last_use[b]=max(last_use[b],a);
    }

    for (int i=0; i<d; ++i) if (haveA[i]) typeA.push(i);
    for (int i=0; i<d; ++i) {
        for (int j=0; j<d; ++j) if (haveB[i][j]) gone[i].push(j);
    }

    int ans=d*d;
    for (int l=0; l<d; ++l) {

        if (typeA.size() && typeA.front()==l-1) {
            at_least=l+d-1;
            typeA.pop();
        }

        vector<int> del[10005];
        for (int i=0; i<d; ++i) {
            if (gone[i].size() && gone[i].front()==l-1) {
                last_use[i]=max(last_use[i],l+d-1);
                gone[i].pop();
            }
            if (last_use[i]!=-1) del[last_use[i]].push_back(i);
        }

        reset();
        for (int r=l; r<l+d; ++r) {
            for (auto s : del[r]) Del(s);
            if (r>=at_least) ans=min(ans,(r-l+1)*mmin);
        }   
    }
    cout<<ans;
}