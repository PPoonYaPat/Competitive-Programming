#include "landlord.h"
#include "public.cpp"
#include <bits/stdc++.h>
using namespace std;

int n,m;
int U[2001][2001],D[2001][2001],sum[2001][2001][4],L[2001][2001],R[2001][2001];

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

    //consider quadrant 0 and 2

    for (int i=0; i<n; ++i) {
        // 2
        for (int j=0; j<m; ++j) {
            if (K[i][j]==1) {
                int cnt=0, mmin=D[i][j]-i+1;

                for (int k=j; k>=0; --k) {
                    if (D[i][k]==-1 || mmin==0) break;
                    mmin=min(mmin,D[i][k]-i+1);
                    cnt+=mmin;
                }
                sum[i][j][2]=cnt;
            } else {
                int cnt=0,mmin;
                if (D[i+1][j]==-1 || i+1==n) mmin=1;
                else mmin=D[i+1][j]-i+1;

                for (int k=j; k>=0; --k) {
                    if ((D[i][k]==-1 && k!=j) || mmin==0) break;
                    if (k!=j) mmin=min(mmin,D[i][k]-i+1);
                    cnt+=mmin;
                }
                sum[i][j][2]=cnt;
            }
        }

        // 0

        for (int j=0; j<m; ++j) {
            if (K[i][j]==1) {
                int cnt=0, mmin=i-U[i][j]+1;
                for (int k=j; k>=0; --k) {
                    if (U[i][k]==-1 || mmin==0) break;
                    mmin=min(mmin,i-U[i][k]+1);
                    cnt+=mmin;
                }
                sum[i][j][0]=cnt;
            } else {
                int cnt=0,mmin;
                if (U[i-1][j]==-1 || i-1==-1) mmin=1;
                else mmin=i-U[i-1][j]+1;

                for (int k=j; k>=0; --k) {
                    if ((U[i][k]==-1 && k!=j) || mmin==0) break;
                    if (k!=j) mmin=min(mmin,i-U[i][k]+1);
                    cnt+=mmin;
                }
                sum[i][j][0]=cnt;
            }
        }
    }

    //consider quadrant 3

    for (int i=0; i<n; ++i) {
        for (int j=m-1; j>=0; --j) {
            if (K[i][j]==1) {
                int cnt=0, mmin=D[i][j]-i+1;
                for (int k=j; k<m; ++k) {
                    if (D[i][k]==-1 || mmin==0) break;
                    mmin=min(mmin,D[i][k]-i+1);
                    cnt+=mmin;
                }
                sum[i][j][3]=cnt;
            } else {
                int cnt=0,mmin;
                if (D[i+1][j]==-1 || i+1==n) mmin=1;
                else mmin=D[i+1][j]-i+1;

                for (int k=j; k<m; ++k) {
                    if ((D[i][k]==-1 && k!=j) || mmin==0) break;
                    if (k!=j) mmin=min(mmin,D[i][k]-i+1);
                    cnt+=mmin;
                }
                sum[i][j][3]=cnt;
            }
        }

//quadrant 1

        for (int j=m-1; j>=0; --j) {
            if (K[i][j]==1) {
                int cnt=0, mmin=i-U[i][j]+1;
                for (int k=j; k<m; ++k) {
                    if (U[i][k]==-1 || mmin==0) break;
                    mmin=min(mmin,i-U[i][k]+1);
                    cnt+=mmin;
                }
                sum[i][j][1]=cnt;
            } else {
                int cnt=0,mmin;
                if (U[i-1][j]==-1 || i-1==-1) mmin=1;
                else mmin=i-U[i-1][j]+1;

                for (int k=j; k<m; ++k) {
                    if ((U[i][k]==-1 && k!=j) || mmin==0) break;
                    if (k!=j) mmin=min(mmin,i-U[i][k]+1);
                    cnt+=mmin;
                }
                sum[i][j][1]=cnt;
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

/*
3 3 4
100
101
111
0 1
0 2
1 1
2 2
->2 3 6 4

5 5 5
01011
10110
11101
11000
00101
3 3
3 4
0 2
1 4
1 0
-> 1 3 7 6 3
*/
