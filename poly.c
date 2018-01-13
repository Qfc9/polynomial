#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <uchar.h>

#include "poly.h"
#include "util.h"

enum sign{ADD, SUB};

polynomial *poly_math(polynomial *newPoly, const polynomial *oldP, int sign);
void poly_sort(polynomial *p);
void poly_is_sorted(polynomial *p);

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
            char *strExp = subscript(eqn->exp);
            if(strExp)
            {
                printf("%s", strExp);
                free(strExp);
            }
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
    char first[32];
    char middle[32];
    strncpy(first, "\0", 32);
    strncpy(middle, "\0", 32);

    if(p->coeff)
    {
        length += sprintf(first, "%c%d", p->coeff > 0 ? '+' : '-', abs(p->coeff));
        if(p->exp > 1)
        {
            char *strExp = subscript(p->exp);
            if(strExp)
            {
                strcat(middle, strExp);
                length += strlen(strExp);
                free(strExp);
            }
        }
        else if(p->exp == 1)
        {
            length += sprintf(middle, "x");
            length++;
        }
    }

    char *curStr = malloc(sizeof(*curStr) * length + 1);
    if(curStr)
    {
        strcpy(curStr, "\0");
        strncat(curStr, first, strlen(first));
        strncat(curStr, middle, strlen(middle));
    }

    if(p->next)
    {
        char *pastStr = poly_to_string(p->next);
        if(pastStr)
        {
            char *tmp = realloc(curStr, sizeof(*curStr) * (strlen(pastStr) + length));
            if(tmp)
            {
                curStr = tmp;
                strcat(curStr, pastStr);
            }
            free(pastStr);
        }
    }

    return curStr;
}

polynomial *poly_add(const polynomial *a, const polynomial *b)
{
    if(!a || !b)
    {
        return NULL;
    }

    polynomial *c = poly_math(NULL, a, ADD);
    poly_math(c, b, ADD);
    poly_is_sorted(c);

    return c;
}

polynomial *poly_sub(const polynomial *a, const polynomial *b)
{
    if(!a || !b)
    {
        return NULL;
    }

    polynomial *c = poly_math(NULL, a, SUB);
    poly_math(c, b, SUB);
    poly_is_sorted(c);

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
        return;
    }

    transform(p);

    poly_iterate(p->next, transform);
}

polynomial *poly_math(polynomial *p, const polynomial *oldP, int sign)
{
    if(!oldP)
    {
        return NULL;
    }
    else if(!p)
    {
        // ABCs
        p = term_create(oldP->coeff, oldP->exp);
        if(p)
        {
            poly_math(p, oldP->next, sign);
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        polynomial *temp = p;
        while(p)
        {
            if((p->exp == oldP->exp) && (sign == ADD))
            {
                p->coeff = p->coeff + oldP->coeff;
                break;
            }
            if((p->exp == oldP->exp) && (sign == SUB))
            {
                p->coeff = p->coeff - oldP->coeff;
                break;
            }
            else if(!p->next)
            {
                polynomial *newPoly = term_create(oldP->coeff, oldP->exp);
                if(newPoly)
                {
                    p->next = newPoly;
                    break;
                }
                else
                {
                    return NULL;
                }
            }
            p = p->next;   
        }
        poly_math(temp, oldP->next, sign);
    }

    return p;
}

void poly_sort(polynomial *p)
{
    if(!p || !p->next)
    {
        return;
    }

    if(p->exp < p->next->exp)
    {
        unsigned int tempExp = p->exp;
        int tempCoeff = p->coeff;

        p->exp = p->next->exp;
        p->coeff = p->next->coeff;

        p->next->exp = tempExp;
        p->next->coeff = tempCoeff;
    }
    

    poly_sort(p->next);

}

void poly_is_sorted(polynomial *p)
{
    if(!p || !p->next)
    {
        return;
    }

    polynomial *orgP = p;
    size_t counter = 1;

    while(p)
    {
        p = p->next;
        counter++;
    }

    for(size_t i = 1; i < counter; i*=2)
    {
        poly_sort(orgP);
    }
}