#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

unsigned char* convertStrToLongBv(char* str, size_t* bits)
{
    size_t bytes = 0;
    size_t ix = 0;
    unsigned char mask = 1;
    unsigned char* vec = NULL;

    if (str && *str && bits)
    {
        *bits = strlen(str);
        bytes = ((*bits - 1) / 8) + 1;
        vec = (unsigned char*) calloc (bytes, sizeof (unsigned char));
        if (vec)
        {
            for (size_t i = 0; i < bytes; i++)
            {
                mask = 1;
                for (size_t j = 0; j < 8 && (ix < *bits); j++)
                {
                    if (str[ix] != '0')
                    {
                        vec[i] = vec[i] | mask;
                    }
                    mask = mask << 1;
                    ix++;
                }
            }
        }
    }
    return vec;
}

char* convertLongBvToStr(unsigned char* vec, size_t bits)
{
    size_t bytes = 0;
    size_t ix = 0;
    unsigned char mask = 1;
    char* str = NULL;

    if (vec && bits)
    {
        str = (char*) calloc (bits + 1, sizeof (char));
        bytes = ((bits - 1) / 8) + 1;
        if (str)
        {
            for (size_t i = 0; i < bytes; i++)
            {
                mask = 1;
                for (size_t j = 0; j < 8 && (ix < bits); j++)
                {
                    if (vec[i] & mask)
                    {
                        str[ix] = '1';
                    }
                    else
                    {
                        str[ix] = '0';
                    }
                    mask = mask << 1;
                    ix++;
                }
            }
            str[ix] = '\0';
        }
    }
    return str;
}


void printLongBv(unsigned char* vec, size_t bits)
{
    size_t bytes = 0;
    size_t ix = 0;
    unsigned char mask = 1;

    if (vec && bits)
    {
        bytes = ((bits - 1) / 8) + 1;
        for (size_t i = 0; i < bytes; i++)
        {
            mask = 1;
            for (size_t j = 0; j < 8 && (ix < bits); j++)
            {
                if (vec[i] & mask)
                {
                    printf("1");
                }
                else
                {
                    printf("0");
                }
                mask = mask << 1;
                ix++;
            }
        }
        printf("\n");
    }
}

unsigned char * logMul(unsigned char *vecA, size_t bitsA, unsigned char *vecB, size_t bitsB)
{
    unsigned char* res = NULL;
    if (vecA && vecB && bitsA && bitsB && bitsA == bitsB)
    {
        size_t bytes = ((bitsA - 1) / 8) + 1;
        res = (unsigned char *) calloc (bytes, sizeof(unsigned char));
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
        size_t remaining_bits = bits % 8;

        if (remaining_bits != 0)
        {
            unsigned char mask = (1 << remaining_bits) - 1;
            vec[bytes - 1] = vec[bytes - 1] & mask;
        }
    }
}



void shiftLeft(unsigned char *vec, size_t bits, size_t k)
{
    if (vec && bits && k > 0)
    {

        size_t bytes = ((bits - 1) / 8) + 1;
        size_t byte_shift = k / 8;
        size_t bit_shift = k % 8;

        if (byte_shift > 0)
        {
               for (size_t i = 0; i < bytes - byte_shift; i++)
               {
                   vec[i] = vec[i + byte_shift];
               }
               for (size_t i = bytes - byte_shift; i < bytes; i++)
               {
                   vec[i] = 0;
               }
           }
           if (bit_shift > 0)
           {
               unsigned char carry = 0;
               for (size_t i = bytes - 1; i >= 0; i--)
               {
                   unsigned char current = vec[i];
                   unsigned char prev_carry = current << (8 - bit_shift);

                   vec[i] = (current >> bit_shift) | carry;
                   carry = prev_carry;
               }
           }


        size_t remaining_bits = bits % 8;
        if (remaining_bits != 0)
        {
            unsigned char mask = (1 << remaining_bits) - 1;
            vec[bytes - 1] = vec[bytes - 1] & mask;
        }
    }

}

void shiftRight(unsigned char *vec, size_t bits, size_t k) {
    if (vec && bits && k > 0)
    {

        size_t bytes = ((bits - 1) / 8) + 1;
        size_t byte_shift = k / 8;
        size_t bit_shift = k % 8;

        if (byte_shift > 0)
        {
                for (size_t i = bytes - 1; i >= byte_shift; i--)
                {
                    vec[i] = vec[i - byte_shift];
                }
                for (size_t i = 0; i < byte_shift; i++)
                {
                    vec[i] = 0;
                }
        }

        if (bit_shift > 0)
        {
            unsigned char carry = 0;
            for (size_t i = 0; i < bytes; i++)
            {
                unsigned char current = vec[i];
                unsigned char next_carry = current >> (8 - bit_shift);
                vec[i] = (current << bit_shift) | carry;
                carry = next_carry;
            }
        }

        size_t remaining_bits = bits % 8;
        if (remaining_bits != 0)
        {
            unsigned char mask = (1 << remaining_bits) - 1;
            vec[bytes - 1] = vec[bytes - 1] & mask;
        }
    }
}

void set0(unsigned char* vec, size_t bits, size_t k)
{
    if (vec && bits && k <= bits)
    {
        unsigned char mask = 1;
        size_t byte = k / 8;
        size_t bit = k % 8;
        mask = mask << bit;
        vec[byte] = vec[byte] & ~mask;
    }
}

void set1 (unsigned char* vec, size_t bits, size_t k)
{
    if (vec && bits && k <= bits)
    {
        unsigned char mask = 1;
        size_t byte = k / 8;
        size_t bit = k % 8;
        mask = mask << bit;
        vec[byte] = vec[byte] | mask;
    }
}

int main()
{
//    char text[] = "0000000000000000000000000000000000000000000000000011111111111111111111111111111111111111111111111111";
//    size_t bits = 0;
//    unsigned char* vec = convertStrToLongBv(text, &bits);
//    inversion(vec, bits);
//    printLongBv(vec, bits);
//    free(vec);
//    vec = NULL;

    char text1[256] = "0110110101";
    char text2[256] = "0110110101";
    size_t bitsA = 0;
    size_t bitsB = 0;
    unsigned char* vec1 = convertStrToLongBv(text1, &bitsA);
    unsigned char* vec2 = convertStrToLongBv(text2, &bitsB);
    printLongBv(vec1, bitsA);
    shiftLeft(vec1, bitsA, 1);
    printLongBv(vec1, bitsA);
    free(vec1);
    vec1 = NULL;
    free(vec2);
    vec2 = NULL;
    return 0;



//    inversion(vec1, bitsA);
//    printLongBv(vec1, bitsA);
//    shiftLeft(vec1, bitsA, 4);
//    printLongBv(vec1, bitsA);
//    free(vec1);
//    vec1 = NULL;
//    free(vec2);
//    vec2 = NULL;
    return 0;
}


