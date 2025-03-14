#include "landlord.h"
//#include "public.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,m;
int U[2001][2001],D[2001][2001],L[2001][2001],R[2001][2001],sum[2001][2001][4];

void landlord(int N, int M, vector<vector<int>> K){
    n=N; m=M;

    //consider down
    for (int j=0; j<m; ++j) {
        for (int i=n-1; i>=0; --i) {
            if (K[i][j]==0) D[i][j]=-1;
            else {
                if (i==n-1) D[i][j]=i;
                else {
                    if (D[i+1][j]==-1) D[i][j]=i;
                    else D[i][j]=D[i+1][j];
                }
            }
        }
    }

    //consider up
    for (int j=0; j<m; ++j) {
        for (int i=0; i<n; ++i) {
            if (K[i][j]==0) U[i][j]=-1;
            else {
                if (i==0) U[i][j]=i;
                else {
                    if (U[i-1][j]==-1) U[i][j]=i;
                    else U[i][j]=U[i-1][j];
                }
            }
        }
    }

    //consider left
    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            if (K[i][j]==0) L[i][j]=-1;
            else {
                if (j==0) L[i][j]=j;
                else {
                    if (L[i][j-1]==-1) L[i][j]=j;
                    else L[i][j]=L[i][j-1];
                }
            }
        }
    }

    //consider right
    for (int i=0; i<n; ++i) {
        for (int j=m-1; j>=0; --j) {
            if (K[i][j]==0) R[i][j]=-1;
            else {
                if (j==m-1) R[i][j]=j;
                else {
                    if (R[i][j+1]==-1) R[i][j]=j;
                    else R[i][j]=R[i][j+1];
                }
            }
        }
    }

    //consider quarter 0
    for (int i=0; i<n; ++i) {
        stack<pii> st; //{val,cnt}
        int s=0;

        for (int j=0; j<m; ++j) {
            int now;
            if (K[i][j]==1) now=i-U[i][j]+1;
            else {
                if (i==0 || K[i-1][j]==0) now=1;
                else now=i-U[i-1][j]+1;
            }

            int cnt=1;
            while (st.size() && st.top().first>now) {
                s-=st.top().first*st.top().second;
                cnt+=st.top().second;
                st.pop();
            }
            st.push(pii(now,cnt));
            s+=now*cnt;
            sum[i][j][0]=s;

            if (K[i][j]==0) {
                s=0;
                while (st.size()) st.pop();
            }
        }
    }

    //consider quarter 1
    for (int i=0; i<n; ++i) {
        stack<pii> st; //{val,cnt}
        int s=0;

        for (int j=m-1; j>=0; --j) {
            int now;
            if (K[i][j]==1) now=i-U[i][j]+1;
            else {
                if (i==0 || K[i-1][j]==0) now=1;
                else now=i-U[i-1][j]+1;
            }

            int cnt=1;
            while (st.size() && st.top().first>now) {
                s-=st.top().first*st.top().second;
                cnt+=st.top().second;
                st.pop();
            }
            st.push(pii(now,cnt));
            s+=now*cnt;
            sum[i][j][1]=s;

            if (K[i][j]==0) {
                s=0;
                while (st.size()) st.pop();
            }
        }
    }

    //consider quarter 2
    for (int i=0; i<n; ++i) {
        stack<pii> st; //{val,cnt}
        int s=0;

        for (int j=0; j<m; ++j) {
            int now;
            if (K[i][j]==1) now=D[i][j]-i+1;
            else {
                if (i==n-1 || K[i+1][j]==0) now=1;
                else now=D[i+1][j]-i+1;
            }

            int cnt=1;
            while (st.size() && st.top().first>now) {
                s-=st.top().first*st.top().second;
                cnt+=st.top().second;
                st.pop();
            }
            st.push(pii(now,cnt));
            s+=now*cnt;
            sum[i][j][2]=s;

            if (K[i][j]==0) {
                s=0;
                while (st.size()) st.pop();
            }
        }
    }

    //consider quarter 3
    for (int i=0; i<n; ++i) {
        stack<pii> st; //{val,cnt}
        int s=0;

        for (int j=m-1; j>=0; --j) {
            int now;
            if (K[i][j]==1) now=D[i][j]-i+1;
            else {
                if (i==n-1 || K[i+1][j]==0) now=1;
                else now=D[i+1][j]-i+1;
            }

            int cnt=1;
            while (st.size() && st.top().first>now) {
                s-=st.top().first*st.top().second;
                cnt+=st.top().second;
                st.pop();
            }
            st.push(pii(now,cnt));
            s+=now*cnt;
            sum[i][j][3]=s;

            if (K[i][j]==0) {
                s=0;
                while (st.size()) st.pop();
            }
        }
    }
}

int house(int A, int B){
    int cnt=sum[A][B][0]+sum[A][B][1]+sum[A][B][2]+sum[A][B][3];

    if (D[A][B]!=-1) {
        cnt=cnt-(D[A][B]-A+1)-(A-U[A][B]+1)-(R[A][B]-B+1)-(B-L[A][B]+1);
        return cnt+1;

    } else {

        if (D[A+1][B]!=-1 && A+1!=n) cnt-=(D[A+1][B]-A);
        if (U[A-1][B]!=-1 && A-1!=-1) cnt-=(A-U[A-1][B]);
        if (R[A][B+1]!=-1 && B+1!=m) cnt-=(R[A][B+1]-B);
        if (L[A][B-1]!=-1 && B-1!=-1) cnt-=(B-L[A][B-1]);

        return cnt-3;
    }
}
