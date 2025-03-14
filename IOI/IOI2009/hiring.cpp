#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef pair<ld,ld> pii;

int n,mx_people=-1;
ld w,use_max,ans;

struct node {
    ld s,q;
    int ord;
    bool operator < (const node &o) {
        if (s != o.s) return s > o.s;
        else return q>o.q;
    }
};

node x[500001];
vector<pii> v;
ld fen1[500010],fen2[500010];

ld find1(int x) {
    ++x;
    ld sum=0;
    while (x) {
        sum+=fen1[x];
        x-=x&-x;
    }
    return sum;
}

ld find2(int x) {
    ++x;
    ld sum=0;
    while (x) {
        sum+=fen2[x];
        x-=x&-x;
    }
    return sum;
}

void update1(int x, ld val) {
    ++x;
    while (x<=n+5) {
        fen1[x]+=val;
        x+=x&-x;
    }
}

void update2(int x, ld val) {
    ++x;
    while (x<=n+5) {
        fen2[x]+=val;
        x+=x&-x;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>w;
    for (int i=0; i<n; ++i) {
        ld k;
        cin>>k>>x[i].q;
        x[i].s=k/x[i].q;
        v.push_back({x[i].q,i});
    }
    sort(v.begin(),v.end());
    for (int i=0; i<n; ++i) {
        x[(int)(v[i].second)].ord=i;
        update1(i,x[(int)(v[i].second)].q);
        update2(i,1);
    }
    sort(x,x+n);

    int prev=-1;
    for (int i=0; i<n; ++i) {

        if (i!=n-1 && x[i+1].s==x[i].s) {
            if (prev==-1) prev=i;
        } else {

            //b-search
            int l=0, r=n-1;
            while (l<r) {
                int mid=(l+r+1)/2;
                if (find1(mid)*x[i].s<=w) l=mid;
                else r=mid-1;
            }

            if ((find2(l)>mx_people) || (find2(l)==mx_people && use_max>find1(l)*x[i].s)) {
                mx_people=find2(l);
                ans=x[i].s;
                use_max=find1(l)*x[i].s;
            }

            //delete
            if (prev==-1) {
                update1(x[i].ord,-x[i].q);
                update2(x[i].ord,-1);
            } else {
                for (int j=prev; j<=i; ++j) {
                    update1(x[j].ord,-x[j].q);
                    update2(x[j].ord,-1);
                }
                prev=-1;
            }
        }
    }

    cout<<mx_people<<"\n";
    for (int i=0; i<n; ++i) if (x[i].s>ans) v[x[i].ord].first=0;
    for (int i=0; i<n; ++i) {
        if (v[i].first==0) continue;
        if (w-v[i].first*ans>=0) {
            cout<<v[i].second+1<<"\n";
            w=w-v[i].first*ans;
        }
    }
}