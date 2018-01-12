
#ifndef STACK_H
 #define STACK_H

#include <stdbool.h>
#include <stdlib.h>

struct term
{
    int coeff;
    unsigned int exp;
    struct term *next;
} term;

typedef struct term polynomial;

struct term * term_create(int coeff, unsigned int exp);

void poly_destroy(polynomial *eqn);

void poly_print(const polynomial *eqn);

// Make
char *poly_to_string(const polynomial *p);
polynomial *poly_add(const polynomial *a, const polynomial *b);
polynomial *poly_sub(const polynomial *a, const polynomial *b);
bool poly_equal(const polynomial *a, const polynomial *b);
double poly_eval(const polynomial *p, double x);
void poly_iterate(polynomial *p, void (*transform)(struct term *));

#endif
