#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tu;

int n,k,nxL[100005][18],nxR[100005][18];
const int mx=200010;
pii seg[100005];
set<tu> range;
map<int,int> mp;
pii fen1[200015]; //find max (seg[idx].first,idx) at position of seg[idx].second
pii fen2[200015]; //find min (seg[idx].second,idx) at position of seg[idx].first

int find1(int x) {
    int ma=-INT_MAX, ans;
    while (x) {
        if (fen1[x].first && ma<=fen1[x].first){
            ma=fen1[x].first;
            ans=fen1[x].second;
        }
        x-=x&-x;
    }
    return ans;
}

void update1(int x, int val, int idx) {
    while (x<=mx+2) {
        if (fen1[x].first==0 || val>fen1[x].first) {
            fen1[x]=pii(val,idx);
        }
        x+=x&-x;
    }
}

int find2(int x) {
    int mi=INT_MAX, ans;
    while (x) {
        if (fen2[x].first && fen2[x].first<=mi) {
            mi=fen2[x].first;
            ans=fen2[x].second;
        }
        x-=x&-x;
    }
    return ans;
}

void update2(int x, int val, int idx) {
    while (x<=mx+2) {
        if (fen2[x].first==0 || fen2[x].first>val) fen2[x]=pii(val,idx);
        x+=x&-x;
    }
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    freopen("sample-04-in.txt","r",stdin);
    cin>>n>>k;

    seg[0]=pii(-INT_MAX,-INT_MAX);
    seg[n+1]=pii(INT_MAX,INT_MAX);
    mp[-INT_MAX]=0; mp[INT_MAX]=0;
    for (int i=0; i<18; ++i) nxL[0][i]=0, nxR[n+1][i]=n+1;

    for (int i=1; i<=n; ++i) {
        cin>>seg[i].first>>seg[i].second;
        mp[seg[i].first]=0;
        mp[seg[i].second]=0;
    }

    int cnt=0;
    for (auto s : mp) mp[s.first]=++cnt;

    for (int i=0; i<=n; ++i) update1(mp[seg[i].second],seg[i].first,i);
    for (int i=1; i<=n+1; ++i) update2(mx-mp[seg[i].first],seg[i].second,i);

    for (int i=1; i<=n; ++i) nxL[i][0]=find1(mp[seg[i].first]), nxR[i][0]=find2(mx-mp[seg[i].second]);

    for (int j=1; j<18; ++j) {
        for (int i=1; i<=n; ++i) {
            nxL[i][j]=nxL[nxL[i][j-1]][j-1];
            nxR[i][j]=nxR[nxR[i][j-1]][j-1];
        }
    }

    vector<int> ans;
    range.insert(tu(1,1e9,0));
    int sum=0;

    for (int i=1; i<=n; ++i) {
        auto it=range.upper_bound(tu(seg[i].first,INT_MAX,INT_MAX));
        if (it==range.begin()) continue;
        --it;

        int l,r,cnt,idx,cntL=0,cntR=0;
        tie(l,r,cnt)=*it;
        if (r<seg[i].second) continue;

        idx=i;
        for (int j=17; j>=0; --j) {
            if (seg[nxL[idx][j]].first>=l) idx=nxL[idx][j], cntL+=(1<<j);
        }

        idx=i;
        for (int j=17; j>=0; --j) {
            if (seg[nxR[idx][j]].second<=r) idx=nxR[idx][j], cntR+=(1<<j);
        }

        if (sum-cnt+cntL+cntR+1+ans.size()>=k) {
            ans.push_back(i);
            range.erase(it);
            sum-=cnt;
            if (seg[i].first!=l) range.insert(tu(l,seg[i].first,cntL)), sum+=cntL;
            if (seg[i].second!=r) range.insert(tu(seg[i].second,r,cntR)), sum+=cntR;
        }

        if (ans.size()==k) {
            for (auto s : ans) cout<<s<<"\n";
            return 0;
        }

    }
    cout<<-1;
}