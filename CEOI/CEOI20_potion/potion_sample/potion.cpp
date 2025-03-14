#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
//#include "grader.cpp"
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,set<pii>> piv;

int n,h[100005];
const int sq=45;
vector<pii> c[100005];
vector<piv> v[100005];

bool comp(int a, int b) {return h[a]<h[b];}

void init(int N, int D, int H[]) {
    n=N;
    for (int i=0; i<n; ++i) h[i]=H[i], v[i].push_back(piv(0,{}));
}

void curseChanges(int U, int A[], int B[]) {
    for (int i=0; i<U; ++i) {
        c[A[i]].push_back(pii(i+1,B[i]));
        c[B[i]].push_back(pii(i+1,A[i]));
    }

    for (int i=0; i<n; ++i) {
        set<pii> temp;
        for (int j=0; j<c[i].size(); ++j) {
            int add=c[i][j].second;
            if (temp.find(pii(h[add],add))==temp.end()) temp.insert(pii(h[add],add));
            else temp.erase(temp.find(pii(h[add],add)));
            if ((j+1)%sq==0) v[i].push_back(piv(c[i][j].first,temp));
        }
    }
}

int question(int x, int y, int day) {
    int hx=upper_bound(v[x].begin(),v[x].end(),piv(day+1,{}))-v[x].begin()-1;
    int hy=upper_bound(v[y].begin(),v[y].end(),piv(day+1,{}))-v[y].begin()-1;

    set<pii> tempX=v[x][hx].second, tempY=v[y][hy].second;

    int Hx=upper_bound(c[x].begin(),c[x].end(),pii(v[x][hx].first,INT_MAX))-c[x].begin();
    int Hy=upper_bound(c[y].begin(),c[y].end(),pii(v[y][hy].first,INT_MAX))-c[y].begin();

    while (Hx<c[x].size() && c[x][Hx].first<=day) {
        int add=c[x][Hx].second;
        if (tempX.find(pii(h[add],add))==tempX.end()) tempX.insert(pii(h[add],add));
        else tempX.erase(tempX.find(pii(h[add],add)));
        ++Hx;
    }

    while (Hy<c[y].size() && c[y][Hy].first<=day) {
        int add=c[y][Hy].second;
        if (tempY.find(pii(h[add],add))==tempY.end()) tempY.insert(pii(h[add],add));
        else tempY.erase(tempY.find(pii(h[add],add)));
        ++Hy;
    }

    int ans=1e9;
    auto itx=tempX.begin(), ity=tempY.begin();
    while (itx!=tempX.end() && ity!=tempY.end()) {
        ans=min(ans,abs((*itx).first-(*ity).first));
        if ((*itx).first<(*ity).first) ++itx;
        else ++ity;
    }
    return ans;
}
