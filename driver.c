
#include <stdio.h>
#include <stdlib.h>

#include "poly.h"

int main(void)
{
    
    polynomial *eqn_a = term_create(2, 2);
    polynomial *eqn_b = term_create(-10, 1);
    polynomial *eqn_e = term_create(-2, 3);

    polynomial *eqn_cc = poly_add(eqn_a, eqn_b);
    polynomial *eqn_c = poly_add(eqn_cc, eqn_e);

    polynomial *a = term_create(1, 3);
    polynomial *b = term_create(5, 1);
    polynomial *e = term_create(2, 4);

    polynomial *cc = poly_add(a, b);
    polynomial *c = poly_add(cc, e);

    poly_print(eqn_c);
    printf("\n");
    poly_print(c);
    printf("\n");

    polynomial *asdf = poly_add(eqn_c, c);

    poly_print(asdf);
    printf("\n");


    poly_destroy(eqn_a);
    poly_destroy(eqn_b);
    poly_destroy(eqn_c);
    poly_destroy(a);
    poly_destroy(b);
    poly_destroy(c);

    return 0;
}