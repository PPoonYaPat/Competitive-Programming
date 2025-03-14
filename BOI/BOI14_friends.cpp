#include <bits/stdc++.h>
#include <string.h>
using namespace std;

string s,ans1,ans2,ans3;
int st,ed;
bool same,ok;

bool cmp(string a, string b) {
    if (a.size()==0 || b.size()==0) return true;
    for (int i=0; i<a.size(); ++i) {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin>>n;
    cin>>s;

    if (s.size()%2==0) {
        cout<<"NOT POSSIBLE";
        return 0;
    }

    //consider insert letter in the middle
    ok=true;
    for (int i=0; i<s.size()/2; ++i) {
        if (s[i]!=s[i+s.size()/2+1]) ok=false;
    }
    if (ok) {
        int k=0,idx=0;
        while (k<s.size()/2) {
            if (s.size()/2!=idx) ans1+=s[idx], ++k;
            ++idx;
        }
    }

    //consider insert letter on the left string
    for (int i=0; i<=s.size()/2; ++i) {
        if (s[i]!=s[i+s.size()/2+1] || i==s.size()/2) {
            ed=i;
            break;
        }
    }
    for (int i=s.size()/2; i>=0; --i) {
        if (s[i]!=s[i+s.size()/2] || i==0) {
            st=i;
            break;
        }
    }
    same=true;
    for (int i=st; i<=ed; ++i) {
        if (s[i]!=s[st]) {
            same=false;
            break;
        }
    }

    if (st<ed && !same) {
        cout<<"NOT UNIQUE";
        return 0;
    } else if (st==ed || (same && st<ed)) {
        int k=0,idx=0;
        while (k<s.size()/2) {
            if (st!=idx) ans2+=s[idx], ++k;
            ++idx;
        }
    }

    //consider insert letter on the right string
    for (int i=s.size()/2; i<s.size(); ++i) {
        if (s[i]!=s[i-s.size()/2] || i==s.size()-1) {
            ed=i;
            break;
        }
    }
    for (int i=s.size()-1; i>=s.size()/2; --i) {
        if (s[i]!=s[i-s.size()/2-1] || i==s.size()/2) {
            st=i;
            break;
        }
    }
    same=true;
    for (int i=st; i<=ed; ++i) {
        if (s[i]!=s[st]) {
            same=false;
            break;
        }
    }
    if (st<ed && !same) {
        cout<<"NOT UNIQUE";
        return 0;
    } else if (st==ed || (same && st<ed)) {
        int k=0,idx=0;
        while (k<s.size()/2) {
            if (st!=idx) ans3+=s[idx], ++k;
            ++idx;
        }
    }

    if (!ans1.size() && !ans2.size() && !ans3.size()) cout<<"NOT POSSIBLE";
    else if (!cmp(ans1,ans2) || !cmp(ans2,ans3) || !cmp(ans3,ans1)) cout<<"NOT UNIQUE";
    else {
        if (ans1.size()) cout<<ans1;
        else if (ans2.size()) cout<<ans2;
        else cout<<ans3;
    }
}
