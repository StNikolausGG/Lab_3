#include <stdio.h>
#include <stdbool.h>

void PrintBV (unsigned int vec)
{
    unsigned int  mask = 1;
    mask = mask<<31;

    for(int ix=0; ix < 32; ix++)
    {
        if ( mask & vec) printf("%c", '1');
        else printf("%c", '0');
        mask = mask>>1;
    }
    printf("\n");
}

unsigned int StrToInt(char* vec)
{
    unsigned int res = 0;
    unsigned int mask = 1;

    if (vec)
    {
        while (*vec)
        {
            res = res << 1;
            if (*vec != 48)
            {
                res = res | mask;
            }
            vec++;
        }
    }
    return res;
}

int main()
{
    unsigned int vecA = StrToInt("10101010");
    PrintBV(vecA);
    return 0;
}
