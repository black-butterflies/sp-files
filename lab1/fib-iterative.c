#include <stdio.h>

long fib_while(int x) {
	long xnow = 0;
	long xnext = 1;

	while (x > 1) {
		long xtmp = xnow + xnext;
		xnow = xnext;
		xnext = xtmp;
		x = x - 1;
	}
	
	return xnext;
}

long fib_for(int x) {
	long xnow = 0;
	long xnext = 1;
	
	for (; x > 1; x = x - 1) {
		long xtmp = xnow + xnext;
		xnow = xnext;
		xnext = xtmp;
	}

	return xnext;
}

int main(void) {
	// printf("fib(%d) = %d\n", 6, fib_while(6));
	printf("fib(%d) = %ld\n", 100, fib_for(100));
}
