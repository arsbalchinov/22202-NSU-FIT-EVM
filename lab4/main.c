#include <stdio.h>
#include <stdlib.h>

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
	double x = 1;
	int N = 1000000;
	printf("%f\n", exponent(x, N));
	return 0;
}
