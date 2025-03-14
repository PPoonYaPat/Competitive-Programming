#include "manager.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

struct node {
    int val;
    node *l, *r;

    node(int v) : val(v), l(NULL), r(NULL) {}
    node(node *L, node *R) : val(0), l(L), r(R) {
        if (L) val+=L->val;
        if (R) val+=R->val;
    }
};

vector<node*> arr;
int n,after[50001],jump[50001][250][17],power[17],sq=240;
map<int,int> c;

node* build(int l, int r) {
    if (l==r) return new node(0);
    else {
        int mid=(l+r)/2;
        return new node(build(l,mid),build(mid+1,r));
    }
}

node* update(int l, int r, int x, int val, node* pnode) {
    if (x>r || x<l) return pnode;
    if (l==r) return new node(pnode->val+val);
    int mid=(l+r)/2;
    return new node(update(l,mid,x,val,pnode->l),update(mid+1,r,x,val,pnode->r));
}

int query(int l, int r, int want, node* pnode) {
    if (l==r) return l-1;
    int mid=(l+r)/2;
    if (pnode->l->val>want) return query(l,mid,want,pnode->l);
    else return query(mid+1,r,want-pnode->l->val,pnode->r);
}

int find(int want, node* pnode) {
    if (pnode->val<=want) return n-1;
    else return query(0,n-1,want,pnode);
}

int d[50001];

void initialize(int N, int q, std::vector<int> A) {
    //assert(N<=1000);
    n=N;
    arr.push_back(build(0,n-1));
    power[0]=1;
    for (int i=1; i<17; ++i) power[i]=2*power[i-1];

    for (int i=n-1; i>=0; --i) {
        after[i]=c[A[i]];
        c[A[i]]=i;
    }

    for (int i=n-1; i>=0; --i) {
        node* temp=update(0,n-1,i,1,arr.back());
        if (after[i]==0) arr.push_back(temp);
        else arr.push_back(update(0,n-1,after[i],-1,temp));
    }
    reverse(arr.begin(),arr.end());

    for (int i=0; i<n; ++i) if (after[i]==0) after[i]=INT_MAX;

    for (int i=0; i<n-1; ) {
        int h=i+1;
        while (A[i]==A[h] && h<n) ++h;
        for (int j=i; j<h; ++j) d[j]=h-1;
        i=h;
    }

    for (int i=n-1; i>=0; --i) {
        for (int j=1; j<=sq; ++j) {
            if (i==n-1) jump[i][j][0]=n-1;
            else if (j==1) jump[i][j][0]=d[i];
            else if (jump[i+1][j][0]>=after[i]) jump[i][j][0]=jump[i+1][j][0];
            else if (jump[i+1][j][0]<after[i]) jump[i][j][0]=jump[i+1][j-1][0];
        }
    }

    for (int j=1; j<=sq; ++j) {
        for (int k=1; k<16; ++k) {

            if (power[k]*j>n) continue;

            for (int i=0; i<n; ++i) {
                if (jump[i][j][k-1]!=n-1) jump[i][j][k]=jump[jump[i][j][k-1]+1][j][k-1];
                else jump[i][j][k]=n-1;
            }
        }
    }
}

int min_managers(int l, int r, int x) {
    if (x<=sq) {
        int now=l,cnt=0;
        for (int i=15; i>=0; --i) {
            if (x*power[i]>n) continue;
            if (jump[now][x][i]<r) {
                cnt+=power[i];
                now=jump[now][x][i]+1;
            }
        }
        return cnt+1;
    } else {
        int cnt=1,now=find(x,arr[l]);
        while (now<r) {
            now=find(x,arr[now+1]);
            ++cnt;
        }
        return cnt;
    }
}
