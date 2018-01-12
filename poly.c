#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "poly.h"


int intToChar(int a);

typedef struct term polynomial;
polynomial *poly_add_onto(polynomial *newPoly, const polynomial *a);

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

    if(!p)
    {
        return NULL;
    }

    size_t length = 1;
    char first[64];
    char middle[64];

    if(p->coeff)
    {
        length += sprintf(first, "%c%d", p->coeff > 0 ? '+' : '-', abs(p->coeff));
        if(p->exp > 1)
        {
            length += sprintf(middle, "x^%d", p->exp);
            length += 3;
        }
        else if(p->exp == 1)
        {
            length += sprintf(middle, "x");
            length++;
        }
    }

    char *curStr = malloc(sizeof(*curStr) * length);
    strcat(curStr, first);
    strcat(curStr, middle);

    if(p->next)
    {
        char *pastStr = poly_to_string(p->next);
        char *tmp = realloc(curStr, sizeof(*curStr) * (strlen(pastStr) + length));
        curStr = tmp;
        strcat(curStr, pastStr);
    }

    return curStr;
}

polynomial *poly_add_onto(polynomial *newPoly, const polynomial *a)
{
    if(!a)
    {
        return NULL;
    }
    else if(!newPoly)
    {
        // ABCs
        newPoly = term_create(a->coeff, a->exp);
        poly_add_onto(newPoly, a->next);
    }
    else
    {
        polynomial *temp = newPoly;
        while(newPoly)
        {
            if(newPoly->exp == a->exp)
            {
                newPoly->coeff = newPoly->coeff + a->coeff;
                break;
            }
            else if(!newPoly->next)
            {
                polynomial *newerPoly = term_create(a->coeff, a->exp);
                newPoly->next = newerPoly;
                break;
            }
            newPoly = newPoly->next;   
        }

        poly_add_onto(temp, a->next);
    }

    return newPoly;
}

polynomial *poly_add(const polynomial *a, const polynomial *b)
{
    if(!a || !b)
    {
        return NULL;
    }

    polynomial *c = poly_add_onto(NULL, a);
    poly_add_onto(c, b);

    return c;
}

polynomial *poly_sub_onto(polynomial *newPoly, const polynomial *a)
{
    if(!a)
    {
        return NULL;
    }
    else if(!newPoly)
    {
        // ABCs
        newPoly = term_create(a->coeff, a->exp);
        poly_sub_onto(newPoly, a->next);
    }
    else
    {
        polynomial *temp = newPoly;
        while(newPoly)
        {
            if(newPoly->exp == a->exp)
            {
                newPoly->coeff = newPoly->coeff - a->coeff;
                break;
            }
            else if(!newPoly->next)
            {
                polynomial *newerPoly = term_create(a->coeff, a->exp);
                newPoly->next = newerPoly;
                break;
            }
            newPoly = newPoly->next;   
        }

        poly_sub_onto(temp, a->next);
    }

    return newPoly;
}

polynomial *poly_sub(const polynomial *a, const polynomial *b)
{
    if(!a || !b)
    {
        return NULL;
    }

    polynomial *c = poly_sub_onto(NULL, a);
    poly_sub_onto(c, b);

    return c;
}

bool poly_equal(const polynomial *a, const polynomial *b)
{
    if((!a && b) || (a && !b))
    {
        return false;
    }
    else if(!a && !b)
    {
        return true;
    }

    if(a->exp == b->exp && a->coeff == b->coeff)
    {
        if(poly_equal(a->next, b->next))
        {
            return true;
        }
    }

    return false;

}

double poly_eval(const polynomial *p, double x)
{
    if(!p)
    {
        return 0;
    }

    double result = pow(x, p->exp);
    result = p->coeff * result;

    if(p->next)
    {
        return result + poly_eval(p->next, x);
    }

    return result;
}

void poly_iterate(polynomial *p, void (*transform)(struct term *))
{
    if(!p)
    {
        return 0;
    }

    transform(p);

    poly_iterate(p->next)
}

int intToChar(int a)
{
    return a + 48;
}