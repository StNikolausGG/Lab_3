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
            size_t byte_sdvig = k / 8;
            size_t i = 0;
            size_t iy = bytes - 1;
            if (byte_sdvig)
            {
                while (byte_sdvig < bytes)
                {
                    vec[i] = vec[byte_sdvig];
                    i++;
                    byte_sdvig++;
                }
                iy = i - 1;
                while (i < bytes)
                {
                    vec[i] = 0;
                    i++;
                }
            }

            size_t bit = k % 8;
            size_t ost_bit = 8 - bit;
            unsigned char ib = 0;
            unsigned char mask = -1;
            size_t ix = 0;

            if (bit)
            {
                for (ix = 0; ix < iy; ix++)
                {
                    mask = -1;
                    vec[ix] = vec[ix] >> bit;
                    mask = mask >> ost_bit;
                    ib = vec[ix + 1] & mask;
                    ib = ib << ost_bit;
                    vec[ix] = vec[ix] | ib;
                }
                vec[ix] = vec[ix] >> bit;
            }
            mask = -1;
            mask = mask >> (bytes * 8 - bits);
            vec[bytes - 1] = vec[bytes - 1] & mask;
        }
}

void shiftRight(unsigned char *vec, size_t bits, size_t k)
{
    if (vec && bits && k > 0)
    {

        size_t bytes = ((bits - 1) / 8) + 1;
        size_t byte_sdvig = k / 8;
        size_t j = bytes - 1;
        size_t i = j - byte_sdvig;

        if (byte_sdvig)
        {
            if (j > byte_sdvig)
            {
                while (i > 0)
                {
                    vec[j] = vec[i];
                    i--;
                    j--;
                }
                vec[j] = vec[i];
            }
            i = 0;
            while (i < byte_sdvig)
            {
                vec[i] = 0;
                i++;
            }
        }

        size_t bit = k % 8;
        size_t _bit = 8 - bit;
        unsigned char ibx = 0;
        unsigned char iby = 0;
        unsigned char mask = -1;
        if (bit)
        {
            for (; byte_sdvig < bytes; byte_sdvig++)
            {
                mask = -1;
                mask = mask << _bit;
                iby = vec[byte_sdvig] & mask;
                iby = iby >> _bit;
                vec[byte_sdvig] = vec[byte_sdvig] << bit;
                vec[byte_sdvig] = vec[byte_sdvig] | ibx;
                ibx = iby;
            }
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
    //Конвертация str to BV, printBV, конвертация BV to str
//    char text1[256] = "0110110101"; //10 Символов 2 байта не кратно 8
//    char text2[256] = "11100011"; //8 Символов 1 байт кратно 8
//    size_t bitsA = 0;
//    size_t bitsB = 0;
//    unsigned char* vec1 = convertStrToLongBv(text1, &bitsA);
//    unsigned char* vec2 = convertStrToLongBv(text2, &bitsB);
//    printf("vec1 in BV: ");
//    printLongBv(vec1, bitsA);
//    printf("vec2 in BV: ");
//    printLongBv(vec2, bitsB);
//    char* res1 = convertLongBvToStr(vec1, bitsA);
//    char* res2 = convertLongBvToStr(vec2, bitsB);
//    printf("%s\n", res1);
//    printf("%s", res2);
//    free(res1);
//    res1 = NULL;
//    free(res2);
//    res2 = NULL;
//    free(vec1);
//    vec1 = NULL;
//    free(vec2);
//    vec2 = NULL;

    //Логические Mul, Sum, SumMod2, set0/1
//    char text1[256] = "10111000";
//    char text2[256] = "11100010";
//    size_t bitsA = 0;
//    size_t bitsB = 0;
//    unsigned char* vec1 = convertStrToLongBv(text1, &bitsA);
//    unsigned char* vec2 = convertStrToLongBv(text2, &bitsB);
//    printf("vec1 in BV: ");
//    printLongBv(vec1, bitsA);
//    printf("vec2 in BV: ");
//    printLongBv(vec2, bitsB);

//    unsigned char* res1 = logMul(vec1, bitsA, vec2, bitsB);
//    unsigned char* res2 = logSum(vec1, bitsA, vec2, bitsB);
//    unsigned char* res3 = sumMod2(vec1, bitsA, vec2, bitsB);

//    if (res1)
//    {
//        printf("logMul: ");
//        printLongBv(res1, bitsA);
//    }
//    else
//    {
//        printf("Incorrect input data");
//    }

//    if (res2)
//    {
//        printf("logSum: ");
//        printLongBv(res2, bitsA);
//    }
//    else
//    {
//        printf("Incorrect input data");
//    }

//    if (res3)
//    {
//        printf("sumMod2: ");
//        printLongBv(res3, bitsA);
//    }
//    else
//    {
//        printf("Incorrect input data");
//    }

//    set0(vec1, bitsA, 2);
//    set1(vec2, bitsB, 7);
//    printf("vec1 after set bit 0: ");
//    printLongBv(vec1, bitsA);
//    printf("vec2 after set bit 1: ");
//    printLongBv(vec2, bitsB);

//    free(res1);
//    res1 = NULL;
//    free(res2);
//    res2 = NULL;
//    free(res3);
//    res3 = NULL;
//    free(vec1);
//    vec1 = NULL;
//    free(vec2);
//    vec2 = NULL;

    //Инверсия и сдвиги (<< >>)

    //char text1[256] = "0000111010101"; //13 символов
    char text1[256] = "0000111111110000";
    size_t bitsA = 0;
    unsigned char* vec = convertStrToLongBv(text1, &bitsA);
    inversion(vec, bitsA);
    printf("Inversion: ");
    printLongBv(vec, bitsA);
    shiftRight(vec, bitsA, 8);
    printf("ShiftRight: ");
    printLongBv(vec, bitsA);
    shiftLeft(vec, bitsA, 9);
    printf("ShiftLeft: ");
    printLongBv(vec, bitsA);
    free(vec);
    vec = NULL;
    return 0;
}


