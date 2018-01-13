#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"


int intToChar(int a)
{
    return a + 48;
}

char *subscript(unsigned int normalExp)
{
    char *subExp = malloc(sizeof(*subExp) * 64);
    strncpy(subExp, "x", 1);
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
                strcat(subExp, "\u00B3");
                break;
            case 4:
                strcat(subExp, "\u2074");
                break;
            case 5:
                strcat(subExp, "\u2075");
                break;
            case 6:
                strcat(subExp, "\u2076");
                break;
            case 7:
                strcat(subExp, "\u2077");
                break;
            case 8:
                strcat(subExp, "\u2078");
                break;
            case 9:
                strcat(subExp, "\u2079");
                break;
        }
    }

    return subExp;
}