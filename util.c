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