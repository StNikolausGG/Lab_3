#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

unsigned char * logMul(unsigned char *vecA, size_t bitsA, unsigned char *vecB, size_t bitsB);
unsigned char * logSum(unsigned char *vecA, size_t bitsA, unsigned char *vecB, size_t bitsB);
unsigned char * sumMod2(unsigned char *vecA, size_t bitsA, unsigned char *vecB, size_t bitsB);
void inversion(unsigned char *vec, size_t bits);
void shiftLeft(unsigned char *vec, size_t bits, size_t k);
void shiftRight(unsigned char *vec, size_t bits, size_t k);
void set1(unsigned char *vec, size_t bits, size_t bit);
void set0(unsigned char *vec, size_t bits, size_t bit);

int main()
{
    return 0;
}

unsigned char * logMul(unsigned char *vecA, size_t bitsA, unsigned char *vecB, size_t bitsB)
{
    unsigned char* res = NULL;
    if (vecA && vecB && bitsA && bitsB && bitsA == bitsB)
    {
        size_t bytes = ((bitsA - 1) / 8) + 1;
        res = (unsigned char *)calloc(bytes, sizeof(unsigned char));
        if (res)
        {
            for (size_t i = 0; i < bytes; i++)
            {
                res[i] = vecA[i] & vecB[i];
            }
        }
    }
    return res;
}

unsigned char * logSum(unsigned char *vecA, size_t bitsA, unsigned char *vecB, size_t bitsB)
{
    unsigned char* res = NULL;
    if (vecA && vecB && bitsA && bitsB && bitsA == bitsB)
    {
        size_t bytes = ((bitsA - 1) / 8) + 1;
        res = (unsigned char*)calloc(bytes, sizeof (unsigned char));
        if (res)
        {
            for (size_t i = 0; i < bytes; i++)
            {
                res[i] = vecA[i] | vecB[i];
            }
        }
    }
    return res;
}

unsigned char * sumMod2(unsigned char *vecA, size_t bitsA, unsigned char *vecB, size_t bitsB)
{
    unsigned char* res = NULL;
    if (vecA && vecB && bitsA && bitsB && bitsA == bitsB)
    {
        size_t bytes = ((bitsA - 1) / 8) + 1;
        res = (unsigned char*)calloc(bytes, sizeof (unsigned char));
        if (res)
        {
            for (size_t i = 0; i < bytes; i++)
            {
                res[i] = vecA[i] ^ vecB[i];
            }
        }
    }
    return res;
}

void inversion(unsigned char *vec, size_t bits)
{
    if (vec && bits)
    {
        size_t bytes = ((bits - 1) / 8) + 1;
        for (size_t i = 0; i < bytes; i++)
        {
            vec[i] = ~vec[i];
        }
    }
}

void printLongBv(unsigned char* vec, size_t bits)
{
    if (vec)
    {
        if (bits)
        {
            printf("%s", vec);
        }
        else
        {
            printf("Null length BV recieved! \n");
        }
    }
    else
    {
        printf("Null address recieved! \n");
    }
}

void shiftLeft(unsigned char *vec, size_t bits, size_t k)
{

}


void PrintBV (unsigned char* label, unsigned char* vec, size_t bits)
{

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


