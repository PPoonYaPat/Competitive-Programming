#include <bits/stdc++.h>
#include <time.h>
using namespace std;

bool have[1050][1050];

int main() {
    srand(time(0));
    freopen("test.txt","w",stdout);
    int n=100,m;
    m=rand()%300;
    cout<<n<<" "<<m<<"\n";

    while (m) {
        int a=rand()%n, b=rand()%n;
        if (!have[a][b] && a!=b) {
            have[a][b]=have[b][a]=true;
            cout<<a<<" "<<b<<"\n";
            --m;
        }
    }
}