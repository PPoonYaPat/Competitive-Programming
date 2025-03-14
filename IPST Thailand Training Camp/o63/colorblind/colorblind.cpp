#include "colorblind.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

string investivate_colors(int N) {
    if (N==1) return "RB";

    string ans="R";
    int base=use_device(0,1),pref; //pref = R - B

    int x=use_device(0,2), y=use_device(1,2);
    if (x-base==0) {
        if (y-base==0) ans+="RR", pref=3;
        else ans+="BR", pref=1;
    } else if (x-base==-2) ans+="RB", pref=1;
    else ans+="BB", pref=-1;

    for (int i=3; i<2*N; ++i) {
        if (ans[i-2]=='R') {
            int now=pref;

            if (ans[i-1]=='R') --now;
            else ++now;

            if (ans[i-2]=='R') --now;
            else ++now;

            if (ans[i-1]==ans[i-2]) {
                if (now>=0) {
                    if (use_device(i,i-1)-base==0) ans+="R";
                    else ans+="B";
                } else {
                    if (use_device(i,i-2)-base==0) ans+="R";
                    else ans+="B";
                }
            } else {
                if (now>=0) {
                    if (use_device(i,i-1)-base==0) ans+="B";
                    else ans+="R";
                } else {
                    if (use_device(i,i-2)-base==0) ans+="R";
                    else ans+="B";
                }
            }
        } else {
            int now=-pref;

            if (ans[i-1]=='B') --now;
            else ++now;

            if (ans[i-2]=='B') --now;
            else ++now;

            if (ans[i-1]==ans[i-2]) {
                if (now>=0) {
                    if (use_device(i,i-1)-base==0) ans+="B";
                    else ans+="R";
                } else {
                    if (use_device(i,i-2)-base==0) ans+="B";
                    else ans+="R";
                }
            } else {
                if (now>=0) {
                    if (use_device(i,i-1)-base==0) ans+="R";
                    else ans+="B";
                } else {
                    if (use_device(i,i-2)-base==0) ans+="B";
                    else ans+="R";
                }
            }
        }

        if (ans[i]=='R') ++pref;
        else --pref;
    }

    return ans;
}
/*
1
10
RBBRBRBRBRBRRBRBRBRB

2
RRBB
2
RBRB
*/
