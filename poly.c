#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <uchar.h>

#include "poly.h"
#include "util.h"

// Enum for doing Addition or subtractio
enum sign{ADD, SUB};

// Custom hidden function prototypes
polynomial *poly_math(polynomial *newPoly, const polynomial *oldP, int sign);
void poly_sort(polynomial *p);
void poly_is_sorted(polynomial *p);

// Term Struct form the starter code
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

// Poly Destroy from the starter code
void poly_destroy(polynomial *eqn)
{
    while(eqn)
    {
        struct term *tmp = eqn->next;
        free(eqn);
        eqn = tmp;
    }
}

// Poly Print form the starter code, MODIFIED
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
            // Modified this part
            // Now prints a subscript unicode char
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

// Returns the poly as a string
char *poly_to_string(const polynomial *p)
{
    // Checking if the poly exists
    if(!p)
    {
        return NULL;
    }

    // Initializing Variables
    size_t length = 1;
    char first[32];
    char middle[32];
    strncpy(first, "\0", 32);
    strncpy(middle, "\0", 32);

    // Making sure the coeff exists
    if(p->coeff)
    {
        // Storing the sign and coeff and logging the length
        length += sprintf(first, "%c%d", p->coeff > 0 ? '+' : '-', abs(p->coeff));

        // If there is an exponent do one of these ifs
        if(p->exp > 1)
        {
            // Get's the unicode subscript and cat's it
            char *strExp = subscript(p->exp);
            if(strExp)
            {
                strcat(middle, strExp);
                length += strlen(strExp);
                free(strExp);
            }
        }
        // If the exponent is ^1
        else if(p->exp == 1)
        {
            length += sprintf(middle, "x");
            length++;
        }
    }

    // Adds the collected strings to the return string
    char *curStr = malloc(sizeof(*curStr) * length + 1);
    if(curStr)
    {
        strcpy(curStr, "\0");
        strncat(curStr, first, strlen(first));
        strncat(curStr, middle, strlen(middle));
    }

    // Going to the next poly if it exists
    if(p->next)
    {
        // Running the function against the next one and storing the return
        char *pastStr = poly_to_string(p->next);
        if(pastStr)
        {
            // Reallocing the current string to fit the old one and the new one
            char *tmp = realloc(curStr, sizeof(*curStr) * (strlen(pastStr) + length));
            if(tmp)
            {
                // Adding the new and old strings together
                curStr = tmp;
                strcat(curStr, pastStr);
            }
            free(pastStr);
        }
    }

    return curStr;
}

// Adding Polys together
polynomial *poly_add(const polynomial *a, const polynomial *b)
{
    // Checking if they exist
    if(!a || !b)
    {
        return NULL;
    }

    // Adding the two together and then sorting them
    polynomial *c = poly_math(NULL, a, ADD);
    poly_math(c, b, ADD);
    poly_is_sorted(c);

    return c;
}

// Subtracting the polys
polynomial *poly_sub(const polynomial *a, const polynomial *b)
{
    // Checking if they exist
    if(!a || !b)
    {
        return NULL;
    }

    // Subtracting the two polys and then sorting them
    polynomial *c = poly_math(NULL, a, SUB);
    poly_math(c, b, SUB);
    poly_is_sorted(c);

    return c;
}

// Checking the the new polys are equal
bool poly_equal(const polynomial *a, const polynomial *b)
{
    // Checking if they exsist / are the same
    if((!a && b) || (a && !b))
    {
        return false;
    }
    else if(!a && !b)
    {
        return true;
    }

    // If the values match, it will go to the next poly in the chain
    if(a->exp == b->exp && a->coeff == b->coeff)
    {
        if(poly_equal(a->next, b->next))
        {
            return true;
        }
    }

    return false;

}

// Subsitues X in the polys as the value given
double poly_eval(const polynomial *p, double x)
{
    // Checking if poly exists
    if(!p)
    {
        return 0;
    }

    // Raising X by the exp
    double result = pow(x, p->exp);
    // Them multipling against the coeff
    result = p->coeff * result;

    // Going to the next poly if it exists
    if(p->next)
    {
        // Returning the past value plus the current one
        return result + poly_eval(p->next, x);
    }

    return result;
}

// Iterates through the entire poly chain and let's user run a funtion on everything
void poly_iterate(polynomial *p, void (*transform)(struct term *))
{
    // Checking if poly exists
    if(!p)
    {
        return;
    }

    transform(p);

    poly_iterate(p->next, transform);
}

// Adds or Subtracts polys
polynomial *poly_math(polynomial *p, const polynomial *oldP, int sign)
{
    // Checking if poly to be added exists
    if(!oldP)
    {
        return NULL;
    }
    // If the poly to be added to doesn't exist make it
    else if(!p)
    {
        p = term_create(oldP->coeff, oldP->exp);
        // After making the new poly, run the function again with the next adding poly value
        if(p)
        {
            poly_math(p, oldP->next, sign);
        }
        else
        {
            return NULL;
        }
    }
    // When the adding to poly exists
    else
    {
        // Take a snapshot of the old one
        polynomial *temp = p;

        // Loop through the entire new poly
        while(p)
        {
            // There is a match and addition
            if((p->exp == oldP->exp) && (sign == ADD))
            {
                p->coeff = p->coeff + oldP->coeff;
                break;
            }
            // There is a match and subtraction
            else if((p->exp == oldP->exp) && (sign == SUB))
            {
                p->coeff = p->coeff - oldP->coeff;
                break;
            }
            // If they aren't the same and it's the end of the poly chain
            else if(!p->next)
            {
                // Make a new poly and add the values to it
                polynomial *newPoly = term_create(oldP->coeff, oldP->exp);
                if(newPoly)
                {
                    // Then add the new poly to the chain
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

// Sorting a poly chain
void poly_sort(polynomial *p)
{
    // Checking if poly exists and the next poly exists
    if(!p || !p->next)
    {
        return;
    }

    // If the first poly is less than the second one, swap them
    if(p->exp < p->next->exp)
    {
        // I swap the values of the two polys
        // Because I couldn't get the pointers to swap correctly
        unsigned int tempExp = p->exp;
        int tempCoeff = p->coeff;

        p->exp = p->next->exp;
        p->coeff = p->next->coeff;

        p->next->exp = tempExp;
        p->next->coeff = tempCoeff;
    }
    
    // Going to the next value on the chain
    poly_sort(p->next);

}

// Checking if a poly chain is sorted
void poly_is_sorted(polynomial *p)
{
    // Checking if poly exists and the next poly exists
    if(!p || !p->next)
    {
        return;
    }

    // Saving the origial position of the first poly
    polynomial *orgP = p;
    size_t counter = 1;

    // Checking out long the poly chain is
    while(p)
    {
        p = p->next;
        counter++;
    }

    // Sorting the poly chain O(log(N)) times
    for(size_t i = 1; i < counter; i*=2)
    {
        poly_sort(orgP);
    }
}