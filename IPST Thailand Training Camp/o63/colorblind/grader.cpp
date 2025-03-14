#include "colorblind.h"
#include <bits/stdc++.h>
using namespace std;

int NUMBER_OF_MONKEYS, NUMBER_OF_CALLS;

std::string S;

int check() {
    std::vector<int> a,b;
    int ans=0;
    for (int i=0; i<S.size(); ++i) {
        if (S[i]=='B') a.push_back(i);
        else b.push_back(i);
    }
    for (int i=0; i<a.size(); ++i) ans+=abs(a[i]-b[i]);
    return ans;
}

int use_device(int a, int b) {

	if(a < 0 || NUMBER_OF_MONKEYS <= a || b < 0 || NUMBER_OF_MONKEYS <= b) {
		printf("Wrong Answer: illegal call\n");
		exit(0);
	}

	if(a == b) {
		printf("Wrong Answer: illegal call\n");
		exit(0);
	}

	NUMBER_OF_CALLS++;

	swap(S[a],S[b]);
	int res=check();
	swap(S[a],S[b]);
	return res;
}

int main() {

	//////////// run multiple tests ////////////

	int T; scanf("%d",&T);

	while(T--) {

		//////////////// get input ////////////////

		int N;
		std::cin >> N >> S;

		NUMBER_OF_MONKEYS = 2 * N;

		////////////////// solve //////////////////

		NUMBER_OF_CALLS = 0;
		std::string ret = investivate_colors(N);

		if(ret != S) {
			printf("Wrong Answer: incorrect\n");
			exit(0);
		}

		printf("Accepted: %d\n",NUMBER_OF_CALLS);
	}

	return 0;
}
