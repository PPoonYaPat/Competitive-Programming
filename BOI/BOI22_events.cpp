#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,q;
pii s[1<<20];
pii pos[200001],com_pos[200001];
int jump[200001][20];
map<int,int> com;

void update(int l, int r, int idx, int x, pii node) {
    if (x>r || x<l) return;
    if (l==r) s[idx]=min(s[idx],node);
    else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,node);
        update(mid+1,r,2*idx+1,x,node);
        s[idx]=min(s[2*idx],s[2*idx+1]);
    }
}

pii query(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return pii(INT_MAX,INT_MAX);
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    return min(query(l,mid,2*idx,x,y),query(mid+1,r,2*idx+1,x,y));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>q;
    for (int i=0; i<1<<20; ++i) s[i]=pii(INT_MAX,INT_MAX);
    for (int i=1; i<=n; ++i) {
        int st,ed; cin>>st>>ed;
        pos[i].first=st;
        pos[i].second=ed;
        com[st]=1;
        com[ed]=1;
    }

    int cnt=1;
    for (auto it=com.begin(); it!=com.end(); ++it) (*it).second=cnt++;
    for (int i=1; i<=n; ++i) {
        com_pos[i]=pii(com[pos[i].first],com[pos[i].second]);
        update(1,2*n,1,com_pos[i].second,pii(com_pos[i].first,i));
    }
    for (int i=1; i<=n; ++i) jump[i][0]=query(1,2*n,1,com_pos[i].first,com_pos[i].second).second;

    for (int i=1; i<18; ++i) {
        for (int j=1; j<=n; ++j) {
            jump[j][i]=jump[jump[j][i-1]][i-1];
        }
    }

    while (q--) {
        int st,ed,cnt=1;
        cin>>st>>ed;

        if (com_pos[st].second>com_pos[ed].second) cout<<"impossible\n";
        else if (st==ed) cout<<"0\n";
        else {
            if (com_pos[ed].first>com_pos[st].second) {
                for (int i=17; i>=0; --i) {
                    if (com_pos[jump[ed][i]].first>com_pos[st].second) {
                        ed=jump[ed][i];
                        cnt+=(1<<i);
                    }
                }
                if (com_pos[jump[ed][0]].first<=com_pos[st].second) cout<<cnt+1<<"\n";
                else cout<<"impossible\n";
            } else cout<<"1\n";
        }

    }
}
