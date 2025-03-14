#include <bits/stdc++.h>
//#include "rescuelib.cpp"
#include "rescuelib.h"
using namespace std;

int r,c,cnt;
int val[1001][1001];

int main() {
    get_size(r,c);

    val[1][1]=drop_robot(1,1);
    val[1][c]=drop_robot(1,c);
    val[r][1]=drop_robot(r,1);
    val[r][c]=drop_robot(r,c);

    if (val[1][1]==-1) ++cnt;
    if (val[1][c]==-1) ++cnt;
    if (val[r][1]==-1) ++cnt;
    if (val[r][c]==-1) ++cnt;

    if (cnt==0) { // no wall
        int x=(val[1][1]+val[1][c]+3-c)/2;
        int y=val[1][1]+2-x;
        answer(x,y);

    } else if (cnt==2 || cnt==3) { // 1 wall, 2 wall and robot in big room

        if (val[1][1]!=-1 && val[1][c]!=-1) {
            int x=(val[1][1]+val[1][c]+3-c)/2;
            int y=val[1][1]+2-x;
            answer(x,y);

        } else if (val[1][1]!=-1 && val[r][1]!=-1) {
            int y=(val[1][1]+val[r][1]+3-r)/2;
            int x=val[1][1]+2-y;
            answer(x,y);

        } else if (val[r][1]!=-1 && val[r][c]!=-1) {
            int x=r+1-(val[r][1]+val[r][c]+3-c)/2;
            int y=r-x+c-val[r][c];
            answer(x,y);

        } else {
            int y=c+1-(val[1][c]+val[r][c]+3-r)/2;
            int x=r-y+c-val[r][c];
            answer(x,y);

        }

    } else { //2 wall robot in small room

        if (val[1][1]!=-1) {

            int ll=1, rr=c;
            while (ll<rr) {
                int mid=(ll+rr)/2;
                if (drop_robot(1,mid)==-1) rr=mid-1;
                else ll=mid;
            }

            val[1][ll]=drop_robot(1,ll);
            int x=(val[1][1]+val[1][ll]+3-ll)/2;
            int y=val[1][1]+2-x;
            answer(x,y);


        } else if (val[r][1]!=-1) {

            int ll=1, rr=c;
            while (ll<rr) {
                int mid=(ll+rr)/2;
                if (drop_robot(r,mid)==-1) rr=mid-1;
                else ll=mid;
            }

            val[r][ll]=drop_robot(r,ll);
            int x=r+1-(val[r][1]+val[r][ll]+3-ll)/2;
            int y=val[r][ll]+x+1-r;
            answer(x,y);

        } else if (val[1][c]!=-1) {

            int ll=1, rr=c;
            while (ll<rr) {
                int mid=(ll+rr)/2;
                if (drop_robot(1,mid)==-1) ll=mid+1;
                else rr=mid;
            }

            val[1][ll]=drop_robot(1,ll);
            int x=(val[1][ll]+val[1][c]+2-c+ll)/2;
            int y=c+x-1-val[1][c];
            answer(x,y);

        } else {

            int ll=1, rr=c;
            while (ll<rr) {
                int mid=(ll+rr)/2;
                if (drop_robot(r,mid)==-1) ll=mid+1;
                else rr=mid;
            }

            val[r][ll]=drop_robot(r,ll);
            int x=r-(val[r][c]+val[r][ll]-c+ll)/2;
            int y=c+r-x-val[r][c];
            answer(x,y);

        }

    }


    return 0;
}
