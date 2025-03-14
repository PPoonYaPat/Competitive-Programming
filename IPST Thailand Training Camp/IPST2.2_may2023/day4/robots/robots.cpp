#include "robots.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int a,b,n,s[1<<19],lz[1<<19];
bool can[200001];
set<int> rock;

void push(int l, int r, int idx) {
    s[idx]+=lz[idx];
    if (l!=r) {
        lz[2*idx]+=lz[idx];
        lz[2*idx+1]+=lz[idx];
    }
    lz[idx]=0;
}

void update(int l, int r, int idx, int x, int y, int val) {
    push(l,r,idx);
    if (x>r || y<l) return;
    if (x<=l && r<=y) {
        lz[idx]+=val;
        push(l,r,idx);
    } else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,y,val);
        update(mid+1,r,2*idx+1,x,y,val);
        s[idx]=max(s[2*idx],s[2*idx+1]);
    }
}

int query(int l, int r, int idx, int x, int y) {
    push(l,r,idx);
    if (x>r || y<l) return 0;
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    return max(query(l,mid,2*idx,x,y),query(mid+1,r,2*idx+1,x,y));
}

void change(int x) { //assert x!=0 && x!=n-1
    if (can[x]) { //rock to lava
        can[x]=false;

        auto it=rock.find(x);
        --it; int l=*it;
        ++it; ++it; int r=*it;
        --it; rock.erase(it);

        update(0,n-1,1,l,x-1,r-x);
        update(0,n-1,1,x+a,r-1+a,x-l);

    } else { //lava to rock
        can[x]=true;

        auto it=rock.upper_bound(x);
        int r=*it;
        --it; int l=*it;
        rock.insert(x);

        update(0,n-1,1,l,x-1,x-r);
        update(0,n-1,1,x+a,r-1+a,l-x);
    }
}

void init_robots(string str, int A, int B) {
    a=A; b=B; n=str.size();
    rock.insert(0);
    rock.insert(n-1);
    update(0,n-1,1,0,n-2,n-1); //rock at n-1
    for (int i=1; i<str.size()-1; ++i) if (str[i]=='R') change(i);
}

bool update(int k) {
    change(k);
    if (query(0,n-1,1,a,n-1)>b) return false;
    return true;
}
/*
3 2 5
RRLRLRLRLRR
6
3
4
*/
