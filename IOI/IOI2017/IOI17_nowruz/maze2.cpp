#include <bits/stdc++.h>
#include <time.h>
using namespace std;
typedef pair<int,int> pii;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("nowruz4.out.txt","w",stdout);
    
    for (int x=1; x<=128; ++x) {
        for (int i=1; i<256; ++i) {
            if (i%6==1 || i%6==3) cout<<'X';
            else cout<<".";
        }
        cout<<"X\n";
        for (int i=1; i<256; ++i) {
            if (x==128) {
                if (i%6==5) cout<<'X';
                else cout<<".";
            }
            else if (i%6==4 || i%6==0) cout<<'X';
            else cout<<".";
        }
        cout<<"X\n";
    }
}