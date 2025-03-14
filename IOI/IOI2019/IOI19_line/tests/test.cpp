#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

pii p[200005];
int n;
bool use[200005];

vector<pii> vt,vd,vl,vr,Ans,ANS;
vector<int> v[4];
int idxt,idxd,idxl,idxr;

struct rect {
    int l,d,r,t;
};
vector<rect> rec;

void make_rec() {
    if (rec.size()) {
        vector<int> temp;
        temp.push_back(n);

        reverse(rec.begin(),rec.end());
        temp.push_back(rec[0].l);
        temp.push_back(rec[0].t);
        temp.push_back(rec[0].r);
        temp.push_back(rec[0].d);

        for (int i=1; i<rec.size(); ++i) {
            int l=rec[i].l,r=rec[i].r,t=rec[i].t,d=rec[i].d;
            
            if (p[temp.back()].second>p[rec[i].l].second) {
                temp.push_back(l);
                temp.push_back(d);
                temp.push_back(r);
                temp.push_back(t);
            } else {
                temp.push_back(l);
                temp.push_back(t);
                temp.push_back(r);
                temp.push_back(d);
            }
        }

        for (int i=0; i<temp.size()-1; ++i) {
            if (i%2==0) Ans.push_back(pii(p[temp[i+1]].first,Ans.back().second));
            else Ans.push_back(pii(Ans.back().first,p[temp[i+1]].second));
        }
        Ans.push_back(p[temp.back()]);
    }
}

void v0(int mode) {
    if (v[0].size()) {
        if (mode) Ans.push_back(pii(p[v[0][0]].first,Ans.back().second));
        else Ans.push_back(pii(Ans.back().first,p[v[0][0]].second));
        Ans.push_back(p[v[0][0]]);

        for (int i=1; i<v[0].size(); ++i) {
            if (i%2==1) Ans.push_back(pii(p[v[0][i]].first,Ans.back().second));
            else Ans.push_back(pii(Ans.back().first,p[v[0][i]].second));
        }
        Ans.push_back(p[v[0].back()]);
    }
}

void v1(int mode) {
    if (v[1].size()) {
        if (mode) Ans.push_back(pii(p[v[1][1]].first,Ans.back().second));
        else Ans.push_back(pii(Ans.back().first,p[v[1][0]].second));
        Ans.push_back(p[v[1][0]]);

        for (int i=1; i<v[1].size(); ++i) {
            if (i%2==1) Ans.push_back(pii(p[v[1][i]].first,Ans.back().second));
            else Ans.push_back(pii(Ans.back().first,p[v[1][i]].second));
        }
        Ans.push_back(p[v[1].back()]);
    }
}

vector<pii> bruh;

void check() {
    for (int i=2; i<Ans.size(); ++i) {
        
    }
    for (auto s : Ans) if (s.first!=-1) bruh.push_back(s);
}

vector<vector<int>> vec;

void gen(vector<int> x, int mode1, int mode2) {
    Ans.clear();
    bruh.clear();
    Ans.push_back(pii(0,0));

    for (auto s : x) {
        if (s==0) make_rec();
        else if (s==1) v0(mode1);
        else if (s==2) v1(mode2);
    }

    check();
    if (ANS.size()==0 || bruh.size()<ANS.size()) swap(ANS,bruh);
}

int main() {
    freopen("05.in","r",stdin);
    freopen("05.out.txt","w",stdout);

    vec.push_back({0,1,2});
    vec.push_back({0,2,1});
    vec.push_back({1,0,2});
    vec.push_back({1,2,0});
    vec.push_back({2,1,0});
    vec.push_back({2,0,1});

    cin>>n;
    p[n]=pii(0,0);
    for (int i=0; i<n; ++i) {
        int x,y; cin>>x>>y;
        p[i]=pii(x,y);
        vl.push_back(pii(x,i));
        vr.push_back(pii(x,i));
        vt.push_back(pii(y,i));
        vd.push_back(pii(y,i));
    }

    sort(vl.begin(),vl.end());
    sort(vr.begin(),vr.end(),greater<pii>());
    sort(vt.begin(),vt.end(),greater<pii>());
    sort(vd.begin(),vd.end());

    int cnt=0;

    while (idxl<n && idxr<n && idxt<n && idxd<n) {

        while (idxl<n && use[vl[idxl].second]) ++idxl;
        while (idxr<n && use[vr[idxr].second]) ++idxr;
        while (idxt<n && use[vt[idxt].second]) ++idxt;
        while (idxd<n && use[vd[idxd].second]) ++idxd;

        if (idxl>=n || idxr>=n || idxt>=n || idxd>=n) break;

        int xl=vl[idxl].second, xr=vr[idxr].second, xd=vd[idxd].second, xt=vt[idxt].second;

        bool bruh=false;

        if (xl==xd) v[0].push_back(xl), use[xl]=true, bruh=true;
        else if (xr==xt) v[2].push_back(xr), use[xr]=true, bruh=true;

        if (xd==xr) v[1].push_back(xd), use[xd]=true, bruh=true;
        else if (xt==xl) v[3].push_back(xt), use[xt]=true, bruh=true;

        if (!bruh) {
            rec.push_back({xl,xd,xr,xt});
            use[xl]=true;
            use[xr]=true;
            use[xd]=true;
            use[xt]=true;
        }
    }

    reverse(v[2].begin(),v[2].end());
    for (auto s : v[2]) v[0].push_back(s);
    reverse(v[3].begin(),v[3].end());
    for (auto s : v[3]) v[1].push_back(s);

    for (auto s : vec) {
        for (int i=0; i<2; ++i) {
            //for (int j=0; j<2; ++j) gen(s,i,j);
        }
    }

    gen(vec[0],0,0);

    cout<<ANS.size()-1<<"\n";
    for (int i=1; i<ANS.size(); ++i) cout<<ANS[i].first<<" "<<ANS[i].second<<"\n";
}