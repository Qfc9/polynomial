
#include <stdio.h>
#include <stdlib.h>

#include "poly.h"

int main(void)
{
    
    polynomial *eqn_a = term_create(2, 2);
    polynomial *eqn_b = term_create(-10, 1);
    polynomial *eqn_d = term_create(-2, 2);

    poly_print(eqn_a);
    printf("\n");
    poly_print(eqn_b);
    printf("\n");

    polynomial *eqn_c = poly_add(eqn_a, eqn_b);
    eqn_c = poly_add(eqn_c, eqn_d);

    poly_print(eqn_c);
    printf("\n");


    poly_destroy(eqn_a);
    poly_destroy(eqn_b);
    poly_destroy(eqn_c);

    return 0;
}