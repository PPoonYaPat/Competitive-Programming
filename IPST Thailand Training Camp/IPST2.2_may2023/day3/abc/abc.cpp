#include "abc.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

struct point {
    ll x,y;
    int idx;
};

ll sq(ll a) {return a*a;}
ll dis(point a, point b) {return sq(a.x-b.x)+sq(a.y-b.y)+sq(a.x+a.y-b.x-b.y);}
ll cross(point a, point b, point c) {return (b.x-a.x)*(c.y-b.y)-(c.x-b.x)*(b.y-a.y);}

point base;

bool comp(point a, point b) {
    if (cross(base,a,b)==0) return dis(base,a)<dis(base,b);
    else return cross(base,a,b)>0;
}

int A,B,C;
pii ans;
vector<point> v,ch;

pair<int,int> max_unbalance(string s) {
    v.push_back({0,0,-1});
    for (int i=0; i<s.size(); ++i) {
        if (s[i]=='a') ++A;
        if (s[i]=='b') ++B;
        if (s[i]=='c') ++C;
        v.push_back({A-B,B-C,i});
    }

    int mmin=INT_MAX;
    for (int i=0; i<v.size(); ++i) {
        if (v[i].y<mmin || (v[i].y==mmin && v[i].x<base.x)) {
            mmin=v[i].y;
            base=v[i];
            swap(v[i],v[v.size()-1]);
        }
    }
    v.pop_back();
    sort(v.begin(),v.end(),comp);

    ch.push_back(base);
    for (int i=0; i<v.size(); ++i) {
        if ((i==0 && v[i].x==base.x && v[i].y==base.y) || (i!=0 && v[i].x==v[i-1].x && v[i].y==v[i-1].y)) continue;
        while (ch.size()>=2 && cross(ch[ch.size()-2],ch[ch.size()-1],v[i])<0) ch.pop_back();
        ch.push_back(v[i]);
    }
    while (ch.size()>=2 && cross(ch[ch.size()-2],ch[ch.size()-1],ch[0])<0) ch.pop_back();

    ll mmax=-1; int idx=0;
    for (int i=0; i<ch.size(); ++i) {
        while (dis(ch[i],ch[idx])<dis(ch[i],ch[(idx+1)%ch.size()])) idx=(idx+1)%ch.size();
        if (dis(ch[i],ch[idx])>mmax) {
            mmax=dis(ch[i],ch[idx]);
            ans=pii(ch[i].idx+1,ch[idx].idx+1);
        }
    }

    if (ans.first>ans.second) swap(ans.first,ans.second);
    return ans;
}
