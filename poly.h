
#ifndef STACK_H
 #define STACK_H

#include <stdbool.h>
#include <stdlib.h>

struct term;

typedef struct term polynomial;

struct term * term_create(int coeff, unsigned int exp);

void poly_destory(polynomial *eqn);

void poly_print(const polynomial *eqn);

#endif
