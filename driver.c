
#include <stdio.h>
#include <stdlib.h>

#include "poly.h"

int main(int argc, char *argv[])
{
    
    polynomial *eqn_a = term_create(2, 2);
    polynomial *eqn_b = term_create(-10, 1);

    poly_print(eqn_a);
    printf("\n");
    char *strPoly = poly_to_string(eqn_a);
    printf("%s\n", strPoly);

    poly_destroy(eqn_a);
    poly_destroy(eqn_b);
}