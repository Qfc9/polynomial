#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "poly.h"

struct term
{
    int coeff;
    unsigned int exp;
    struct term *next;
};

typedef struct term polynomial;

struct term * term_create(int coeff, unsigned int exp)
{
    struct term *node = malloc(sizeof(*node));
    if(node)
    {
        node->coeff = coeff;
        node->exp = exp;
        node->next = NULL;
    }
    return node;
}

void poly_destroy(polynomial *eqn)
{
    while(eqn)
    {
        struct term *tmp = eqn->next;
        free(eqn);
        eqn = tmp;
    }
}

void poly_print(const polynomial *eqn)
{
    if(!eqn)
    {
        return;
    }

    if(eqn->coeff)
    {
        printf("%c%d", eqn->coeff > 0 ? '+' : '\0', eqn->coeff);
        if(eqn->exp > 1)
        {
            printf("x^%d", eqn->exp);
        }
        else if(eqn->exp == 1)
        {
            printf("x");
        }
        printf(" ");
    }
    poly_print(eqn->next);
}

char *poly_to_string(const polynomial *p)
{
    return ' ';
}
polynomial *poly_add(const polynomial *a, const polynomial *b)
{
    return NULL;
}
polynomial *poly_sub(const polynomial *a, const polynomial *b)
{
    return NULL;
}
bool poly_equal(const polynomial *a, const polynomial *b)
{
    return true;
}
double poly_eval(const polynomial *p, double x)
{
    return 0.0;
}
void poly_iterate(polynomial *p, void(*transform)(struct term *))
{

}