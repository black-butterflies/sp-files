#include <stdio.h>

long _fib(long x, long x1, long x2) {
	if (x == 0) {
		return x2;
	} else {
		return _fib(x - 1, x1 + x2, x1);
	}
}

long fib(long x) {
	return _fib(x, 1, 0);
}

int main(void) {
	printf("fib(%d) = %ld\n", 100, fib(100));
}
