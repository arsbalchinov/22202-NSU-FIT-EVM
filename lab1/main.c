#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double exponent(double x, int N) {
	double exp = 1;
	double p = 1;
	double n_fact = 1;
	for (int i = 1; i <= N; i++) {
		p *= x;
		n_fact *= i;
		exp += (p / n_fact);
	}
	return exp;
}

int main() {
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	long double x = 1;
	int N = 80000000;
	printf("%lf\n", exponent(x, N));
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	printf("Time taken: %lf sec.\n", end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec));
	return 0;
}
