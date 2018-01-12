
#include <stdio.h>
#include <stdlib.h>

#include "poly.h"

polynomial *build_parabola(int a, int b, int c);
void square_each(struct term *t);
void remove_evens(struct term *t);

int main(int argc, char *argv[])
{
	if(argc != 4) {
		fprintf(stderr, "Usage: %s A B C, for Ax^2 + Bx + C\n", argv[0]);
		return 1;
	}

	int coefficients[3];
	for(int n = 1; n < 4; ++n) {
		char *err;
		coefficients[n-1] = strtol(argv[n], &err, 10);
		if(*err) {
			fprintf(stderr, "Not a number: %s\n", argv[n]);
			return 1;
		}
	}

	polynomial *first = build_parabola(2, -10, 8);
	char *str = poly_to_string(first);
	polynomial *second = build_parabola(coefficients[0], coefficients[1], coefficients[2]);

	poly_print(second);
	puts("");
	puts(str);

	polynomial *sum = poly_add(first, second);
	poly_print(sum);
	puts("");
	poly_destroy(sum);

	polynomial *diff = poly_sub(first, second);
	poly_print(diff);
	puts("");
	poly_destroy(diff);

	if(poly_equal(first, second)) {
		puts("Parabolas are equal");
	} else {
		puts("Parabolas are NOT equal");
	}

	printf("f(7)    = %lf\n", poly_eval(second, 7.0));
	printf("f(0)    = %lf\n", poly_eval(second, 0.0));
	printf("f(-3.5) = %lf\n", poly_eval(second, -3.5));

	poly_iterate(second, remove_evens);
	poly_print(second);
	puts("");

	poly_iterate(second, square_each);
	poly_print(second);
	puts("");

	poly_destroy(first);
	poly_destroy(second);

	polynomial *big = term_create(coefficients[0], coefficients[1] + coefficients[2]);
	poly_print(big);
	puts("");
	poly_destroy(big);

	puts(str);

	free(str);

}

polynomial *build_parabola(int a, int b, int c)
{
	polynomial *eqn_a = term_create(a, 2);
	polynomial *eqn_b = term_create(b, 1);
	polynomial *eqn_d = poly_add(eqn_b, eqn_a);

	poly_destroy(eqn_a);
	poly_destroy(eqn_b);

	polynomial *eqn_c = term_create(c, 0);
	polynomial *eqn_e = poly_add(eqn_c, eqn_d);
	poly_destroy(eqn_c);
	poly_destroy(eqn_d);

	return eqn_e;
}

void square_each(struct term *t)
{
	t->exp *= 2;
}

void remove_evens(struct term *t)
{
	if(t->exp % 2 == 0) {
		t->coeff = 0;
	}
}