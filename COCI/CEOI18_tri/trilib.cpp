#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "trilib.h"

static int N;
static long long *x, *y;
static int queries=0;

static void init() {
	static int is_inited=0;
	if (is_inited)
		return;
	is_inited=1;
	assert(scanf("%d", &N)==1);
	x=(long long*)malloc((N+1)*sizeof(long long));
	y=(long long*)malloc((N+1)*sizeof(long long));
	for (int i=1; i<=N; i++)
		assert(scanf("%lld%lld", &x[i], &y[i])==2);
}

int get_n() {
	init();
	return N;
}

int is_clockwise(int a, int b, int c) {
	init();
	assert(a>=1 && a<=N);
	assert(b>=1 && b<=N);
	assert(c>=1 && c<=N);
	assert(a!=b && a!=c && b!=c);
	queries++;
        if(queries == 1000 * 1000 + 1)
            printf("Too many queries!");
	return (x[b]-x[a])*(y[c]-y[a])-(x[c]-x[a])*(y[b]-y[a])<0;
}

void give_answer(int s) {
	init();
	printf("%d\n", s);
}
