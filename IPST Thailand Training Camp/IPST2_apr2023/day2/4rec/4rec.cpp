#include <bits/stdc++.h>
//#include "grader.cpp"
using namespace std;
typedef long long ll;

int n;
ll fenL[500010],fenR[500010];
struct point {
    int x,y;
} c[500001];

ll findL(int x) {
    ll sum=0;
    while (x) {
        sum+=fenL[x];
        x-=x&-x;
    }
    return sum;
}

ll findR(int x) {
    ll sum=0;
    while (x) {
        sum+=fenR[x];
        x-=x&-x;
    }
    return sum;
}

void updateL(int x, int val) {
    while (x<=500005) {
        fenL[x]+=val;
        x+=x&-x;
    }
}

void updateR(int x, int val) {
    while (x<=500005) {
        fenR[x]+=val;
        x+=x&-x;
    }
}

vector<int> v[500001],Y; //group by Y
bool have[500001];
set<int> X;
int cntL,cntR;
ll ans;

long long find_rec(vector<vector<int>> Point, int P, int Q){
    n=Point.size();
    for (int i=0; i<n; ++i) c[i+1]={Point[i][0],Point[i][1]};

    for (int i=1; i<=n; ++i) {
        int x=c[i].x, y=c[i].y;

        if (!have[y]) Y.push_back(y);
        have[y]=true;

        X.insert(x);
        v[x].push_back(y);
        updateR(y,1);
        ++cntR;
    }
    Y.push_back(0);
    sort(Y.begin(),Y.end());
    X.insert(0);

    for (auto it=X.begin(); it!=X.end(); ++it) {
        int col=(*it);
        for (auto y : v[col]) {
            --cntR; ++cntL;
            updateL(y,1);
            updateR(y,-1);
        }

        int l=0, r=500002;
        while (l<r) { //find Upper
            int mid=(l+r+1)/2;
            int val3=findL(mid), val1=cntL-val3, val4=findR(mid), val2=cntR-findR(mid);
            if (val4-val1<=P && val3-val2<=Q) l=mid;
            else r=mid-1;
        }
        int upper=l;

        l=0; r=500002;
        while (l<r) { //find Lower
            int mid=(l+r)/2;
            int val3=findL(mid), val1=cntL-val3, val4=findR(mid), val2=cntR-findR(mid);
            if (val1-val4<=P && val2-val3<=Q) r=mid;
            else l=mid+1;
        }
        int lower=l;

        if (lower<=upper) {
            auto it1=upper_bound(Y.begin(),Y.end(),upper), it2=upper_bound(Y.begin(),Y.end(),lower-1);
            ans+=upper_bound(Y.begin(),Y.end(),upper)-upper_bound(Y.begin(),Y.end(),lower-1);
        }
    }

    return ans;
}
