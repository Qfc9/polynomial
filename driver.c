
#include <stdio.h>
#include <stdlib.h>

#include "poly.h"

int main(void)
{
    
    polynomial *eqn_a = term_create(2, 2);
    polynomial *eqn_b = term_create(-10, 1);

    polynomial *eqn_c = poly_add(eqn_a, eqn_b);

    polynomial *a = term_create(4, 2);
    polynomial *b = term_create(5, 2);

    // poly_print(poly_add(a, b));
    // printf("\n");
    // poly_print(poly_add(eqn_a, eqn_b));
    // printf("\n");

    // poly_print(poly_add(poly_add(a, b), poly_add(eqn_a, eqn_b)));
    // printf("\n");

    // poly_print(poly_sub(poly_add(a, b), poly_add(eqn_a, eqn_b)));
    // printf("\n");

    poly_print(eqn_c);
    printf("\n");

    printf("%lf\n", poly_eval(eqn_a, 3));
    printf("%lf\n", poly_eval(eqn_b, 3));
    printf("%lf\n", poly_eval(eqn_c, 3));

    polynomial *test = poly_add(poly_add(a, b), poly_add(eqn_a, eqn_b));

    if(poly_equal(test, a))
    {
        printf("EQUAL\n");
    }
    else
    {
        printf("NOT\n");
    }

    poly_destroy(eqn_a);
    poly_destroy(eqn_b);
    poly_destroy(eqn_c);
    poly_destroy(a);
    poly_destroy(b);

    return 0;
}