#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,p[1000005],r[1000005],lst=-1,deg[1000005];
vector<int> adj[1000005],br;
vector<pii> edge;
set<int> ans;
bool nope=false,vis[1000005];
vector<int> st;

void dfs(int x, int par, int tar) {
  st.push_back(x);
  vis[x]=true;
  if (x==tar) for (auto s : st) br.push_back(s);
  else for (auto s : adj[x]) if (s!=par && !vis[s]) dfs(s,x,tar);
  st.pop_back();
}

int find(int x) {
  while (x!=p[x]) x=p[x];
  return x;
}

void unite(int a, int b) {
  a=find(a); b=find(b);
  if (r[a]<r[b]) swap(a,b);
  p[b]=a;
  if (r[a]==r[b]) ++r[a];
}

void Init(int N_) {
  n=N_;
  for (int i=0; i<n; ++i) ans.insert(i), p[i]=i;
}

void add(vector<int> x) {
  set<int> temp;
  for (auto s : x) if (ans.find(s)!=ans.end()) temp.insert(s);
  swap(temp,ans);
}

void Link(int A, int B) {
  if (nope) return;
  
  if (lst==-1) {
    if (find(A)==find(B)) {
      memset(vis,0,sizeof(vis));
      br.clear();
      dfs(A,-1,B);
      add(br);
    } else unite(A,B);

    adj[A].push_back(B);
    adj[B].push_back(A);
    edge.push_back(pii(A,B));

    if (adj[A].size()==3) add({adj[A][0],adj[A][1],adj[A][2],A});
    else if (adj[A].size()==4) for (auto s : adj[A]) if (ans.find(s)!=ans.end()) ans.erase(ans.find(s));

    if (adj[B].size()==3) add({adj[B][0],adj[B][1],adj[B][2],B});
    else if (adj[B].size()==4) for (auto s : adj[B]) if (ans.find(s)!=ans.end()) ans.erase(ans.find(s));

    if (ans.size()==0) nope=true;
    if (ans.size()==1) {
      lst=*(ans.begin());

      for (int i=0; i<n; ++i) p[i]=i;
      for (auto s : edge) {
        if (s.first!=lst && s.second!=lst) {
          ++deg[s.first]; ++deg[s.second];
          unite(s.first,s.second);
        }
      }
    }

  } else {
    if (A!=lst && B!=lst) {
      ++deg[A];
      ++deg[B];
      if (deg[A]>2 || deg[B]>2 || find(A)==find(B)) nope=true;
      unite(A,B);
    }
  }

}

int CountCritical() {
  if (nope) return 0;
  return ans.size();
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int N,L; cin>>N>>L;
  Init(N);
  while (L--) {
    int a; cin>>a;
    if (a==-1) cout<<CountCritical()<<"\n";
    else {
      int b; cin>>b;
      Link(a,b);
    }
  }
}