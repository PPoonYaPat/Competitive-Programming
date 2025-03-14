#include "cave.h"
#include <bits/stdc++.h>
using namespace std;

int con[5000],test[5000],ans[5000]; // switch i connect to door con[i]
bool fix_switch[5000];

void exploreCave(int n) {
    for (int i=0; i<n; ++i) { //find door x (0 to x-1 are open)
        int k;
        if (tryCombination(ans)==i) k=1;
        else k=0;

        int l=0, r=n-1;
        while (r>l) {
            int mid=(l+r)/2;

            for (int j=0; j<n; ++j) {
                if (fix_switch[j]) test[j]=ans[j];
                else test[j]=k;
            }
            for (int j=l; j<=mid; ++j) if (!fix_switch[j]) test[j]=1-k;

            if (tryCombination(test)==i) r=mid; //not change
            else l=mid+1; //change
        }

        ans[r]=k;
        fix_switch[r]=true;
        con[r]=i;
    }

    answer(ans,con);
}
