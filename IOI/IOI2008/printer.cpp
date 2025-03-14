#include <bits/stdc++.h>
using namespace std;

int n,mmax;
bool havemax=false;
const int sz=26;
vector<char> ans;

struct Trienode {
    struct Trienode *children[26];
    int level;
    char x;
    bool Endword,longest;
};

struct Trienode *getnode(char x, int l) {
    struct Trienode *pnode = new  Trienode;
    for (int i=0; i<sz; ++i) pnode->children[i]=NULL;
    pnode->level=l;
    pnode->x=x;
    pnode->Endword=false;
    pnode->longest=false;
    return pnode;
};

void insert(struct Trienode *root, string key) {
    struct Trienode *pnode = root;

    for (int i=0; i<key.size(); ++i) {
        int idx=key[i]-'a';
        if (!pnode->children[idx]) pnode->children[idx]=getnode(key[i],pnode->level+1);

        pnode=pnode->children[idx];
    }
    pnode->Endword=true;
}

bool fm(struct Trienode *root) { //if it has the longest path, it will return true;
    if (root->level==mmax && !havemax) {
        havemax=true;
        root->longest=true;
        return true;
    }
    for (int i=0; i<sz; ++i) if (root->children[i] && fm(root->children[i])) {
        root->longest=true;
        return true;
    }
    return false;
}

void dfs(struct Trienode *root) {
    if (root->x != '-') ans.push_back(root->x);
    if (root->Endword) ans.push_back('P');

    struct Trienode *pnode;
    bool haveP=false;

    for (int i=0; i<sz; ++i) if (root->children[i]) {
        if (!root->children[i]->longest) dfs(root->children[i]);
        else pnode=root->children[i], haveP=true;
    }

    if (haveP) dfs(pnode);

    if (!root->longest) ans.push_back('-');
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    struct Trienode *root = getnode('-',0);
    while (n--) {
        string s; cin>>s;
        mmax=max(mmax,(int)(s.size()));
        insert(root,s);
    }
    fm(root);
    dfs(root);
    cout<<ans.size()<<"\n";
    for (auto s : ans) cout<<s<<"\n";
}