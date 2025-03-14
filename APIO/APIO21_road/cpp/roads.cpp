#include "roads.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int n,d[100001],p[1000001],level[1000001],de[100001];
ll dp[100001][2],w[100001],sum,c[100001];
vector<int> deg;
vector<pii> adj[100001];
vector<ll> ans;

bool comp(pii a, pii b) {return a.second<b.second;}
bool comp2(int a, int b) {return level[a]>level[b];}
bool comp3(int a, int b) {return d[a]>d[b];}

struct node {
    int cnt,prior;
    ll val,sum;
    node *l, *r;

    node(ll v) : cnt(1), val(v), sum(v), prior(rand()), l(NULL), r(NULL) {}
};
typedef node* pnode;
pnode tr[100001];

void upd(pnode t) {
    if (t) {
        t->cnt=1;
        t->sum=t->val;
        if (t->l) {
            t->cnt+=t->l->cnt;
            t->sum+=t->l->sum;
        }
        if (t->r) {
            t->cnt+=t->r->cnt;
            t->sum+=t->r->sum;
        }
    }
}

int get_cnt(pnode t) {
    if (!t) return 0;
    else return t->cnt;
}

void split1(pnode t, pnode &l, pnode &r, int v) { //split by cnt
    if (t==NULL) l=r=NULL;
    else if (get_cnt(t->l)>=v) split1(t->l,l,t->l,v), r=t;
    else split1(t->r,t->r,r,v-get_cnt(t->l)-1), l=t;
    upd(t);
}

void split2(pnode t, pnode &l, pnode &r, int v) { //split by val
    if (t==NULL) l=r=NULL;
    else if (t->val>=v) split2(t->l,l,t->l,v), r=t;
    else split2(t->r,t->r,r,v), l=t;
    upd(t);
}

void merge(pnode l, pnode r, pnode &t) {
    if (!l) t=r;
    else if (!r) t=l;
    else if (l->prior>=r->prior) merge(l->r,r,l->r), t=l;
    else merge(l,r->l,r->l), t=r;
    upd(t);
}

void dfs(int x, int par) {
    p[x]=par;
    level[x]=level[par]+1;
    for (auto s : adj[x]) {
        if (s.first==par) continue;
        w[s.first]=s.second;
        merge(tr[x],new node(s.second),tr[x]);
        dfs(s.first,x);
    }
}

void cal(int x, int want) {
    pnode A,B,C;

    //find dp[x][0], don't cut the edge above it

    split1(tr[x],A,B,adj[x].size()-want-de[x]);
    if (A) dp[x][0]=A->sum+c[x];
    else dp[x][0]=c[x];
    merge(A,B,tr[x]);

    if (x) {
        //find dp[x][1], cut the edge above it

        split1(tr[x],A,B,adj[x].size()-want-1-de[x]);
        if (A) dp[x][1]=A->sum+w[x]+c[x];
        else dp[x][1]=w[x]+c[x];
        merge(A,B,tr[x]);

        //replace the value of the parent by dp[x][1]-dp[x][0]

        int par=p[x];
        split2(tr[par],A,B,w[x]);
        split1(B,C,B,1);
        merge(A,B,tr[par]);

        ll nw=dp[x][1]-dp[x][0];
        if (nw<=0) {
            c[par]+=dp[x][1];
            ++de[par];
        } else {
            split2(tr[par],A,B,nw+1);
            merge(A,new node(nw),A);
            merge(A,B,tr[par]);
            c[par]+=dp[x][0];
        }
    }
}

vector<ll> minimum_closure_costs(int N, vector<int> U, vector<int> V, vector<int> W) {
    n=N;
    for (int i=0; i<n-1; ++i) {
        adj[U[i]].push_back(pii(V[i],W[i]));
        adj[V[i]].push_back(pii(U[i],W[i]));
        ++d[U[i]]; ++d[V[i]];
    }
    for (int i=0; i<n; ++i) deg.push_back(i), sort(adj[i].begin(),adj[i].end(),comp);
    sort(deg.begin(),deg.end(),comp3);

    dfs(0,0);
    p[0]=-1;
    for (int i=1; i<n; ++i) dp[i][1]=w[i], sum+=w[i];
    ans.push_back(sum);

    for (int i=1; i<n; ++i) {
        sum=0;
        while (!deg.empty()) {
            if (d[deg.back()]<i+1) deg.pop_back();
            else break;
        }
        vector<int> v;
        for (auto s : deg) v.push_back(s);
        sort(v.begin(),v.end(),comp2);

        for (auto s : v) {
            cal(s,i);
            if (s==0) sum+=dp[s][0];
            else if (d[p[s]]<=i) sum+=min(dp[s][0],dp[s][1]);
        }
        ans.push_back(sum);

        //reset
        for (auto s : v) {
            c[s]=de[s]=0;
            if (s==0) continue;

            int par=p[s];
            pnode A,B,C;

            if (dp[s][1]>dp[s][0]) {
                split2(tr[par],A,B,dp[s][1]-dp[s][0]);
                split1(B,C,B,1);
                merge(A,B,tr[par]);
            }

            split2(tr[par],A,B,w[s]+1);
            merge(A,new node(w[s]),A);
            merge(A,B,tr[par]);
        }
    }

    return ans;
}
/*
5
0 1 1
0 2 4
0 3 3
2 4 2
-> 10 5 1 0 0

4
0 1 5
2 0 10
0 3 5
-> 20 10 5 0

10
5 3 24464
3 6 28145
3 4 16827
3 7 491
5 0 11942
4 9 5436
6 8 14604
9 2 153
7 1 12382
*/
