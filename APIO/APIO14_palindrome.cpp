#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node {
    ll lenght,cnt;
    int ins[26],suffix;
} tree[300001];

string s;
int cur_node=1,c=2;

void add(int idx) {

    int temp=cur_node;
    while (true) {
        int len=tree[temp].lenght;
        if (idx-len>=1 && s[idx]==s[idx-len-1]) break;
        temp=tree[temp].suffix;
    }

    if (tree[temp].ins[s[idx]-'a']!=0) { //already have
        cur_node=tree[temp].ins[s[idx]-'a'];
        tree[cur_node].cnt=tree[cur_node].cnt+1;
        return;
    }

    tree[temp].ins[s[idx]-'a']=++c;
    tree[c].lenght=tree[temp].lenght+2;
    tree[c].cnt=1;

    cur_node=c;

    if (tree[cur_node].lenght==1) {
        tree[cur_node].suffix=2;
        return;
    }

    temp=tree[temp].suffix;

    while (true) {
        int len=tree[temp].lenght;
        if (idx-len>=1 && s[idx]==s[idx-len-1]) break;
        temp=tree[temp].suffix;
    }

    tree[cur_node].suffix=tree[temp].ins[s[idx]-'a'];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>s;

    tree[1].lenght=-1;
    tree[1].suffix=1;
    tree[2].lenght=0;
    tree[2].suffix=1;

    for (int i=0; i<s.size(); ++i) add(i);
    for (int i=c; i>=3; --i) tree[tree[i].suffix].cnt=tree[tree[i].suffix].cnt+tree[i].cnt;

    ll mmax=0;
    for (int i=3; i<=c; ++i) mmax=max(mmax,tree[i].cnt*tree[i].lenght);
    cout<<mmax;
}