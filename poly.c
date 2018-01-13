#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <uchar.h>

#include "poly.h"


int intToChar(int a);
char *subscript(unsigned int normalExp);

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
        if(newPoly)
        {
            poly_add_onto(newPoly, a->next);
        }
        else
        {
            return NULL;
        }
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
                if(newerPoly)
                {
                    newPoly->next = newerPoly;
                    break;
                }
                else
                {
                    return NULL;
                }
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
        if(newPoly)
        {
            poly_sub_onto(newPoly, a->next);
        }
        else
        {
            return NULL;
        }
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
                if(newerPoly)
                {
                    newPoly->next = newerPoly;
                    break;
                }
                else
                {
                    return NULL;
                }
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
        return;
    }

    transform(p);

    poly_iterate(p->next, transform);
}

int intToChar(int a)
{
    return a + 48;
}

char *subscript(unsigned int normalExp)
{
    char *subExp = malloc(sizeof(*subExp) * 64);
    strncpy(subExp, "x", 2);
    char strExp[64];
    sprintf(strExp, "%63u", normalExp);

    for(unsigned int i = 0; i < strlen(strExp); i++)
    {
        switch(strExp[i] - 48)
        {
            case 2:
                strcat(subExp, "\u00B2");
                break;
            case 3:
                printf("%s", u8"\u00B3");
                break;
            case 4:
                printf("%s", u8"\u2074");
                break;
            case 5:
                printf("%s", u8"\u2075");
                break;
            case 6:
                printf("%s", u8"\u2076");
                break;
            case 7:
                printf("%s", u8"\u2077");
                break;
            case 8:
                printf("%s", u8"\u2078");
                break;
            case 9:
                printf("%s", u8"\u2079");
                break;
        }
    }

    return subExp;
}