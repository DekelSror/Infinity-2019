#include <stdlib.h> /* NULL */
#include <stdio.h> /* printf */
#include <math.h> /* pow */
#include <limits.h> /* INT_MAX */
#include "bitwise.h"

/*========================================================================*/
/* WorkSheet 6 exercises 1 - 12                                           */
/* Bitwise operations                                                     */
/* Tests                                                                  */
/* Dekel Sror */
/*========================================================================*/
static void TestPow2                 (void); /* very limited */
static void TestPrintFloat           (void);
static void TestXorSwap              (void);
static void TestArithmeticSwap       (void); /* extra */
static void TestBitwiseIncrement     (void);
static void TestIsExactExpOf2        (void);
static void TestIsExactExpOf2Loop    (void);
static void TestSwapBitThreeWithFive (void);
static void TestCountSetBitsLoop     (void);
static void TestCountSetBits         (void); /* NOT MINE! refer to README */
static void TestFloorToSixTeen       (void);
static void TestAreBitsTwoAndSixSet  (void);
static void TestAreBitsTwoOrSixSet   (void);
static void TestByteMirror           (void);
static void TestByteMirrorAlternate  (void); /* extra */
static void TestByteMirrorLoop       (void);

/* test data */

static const unsigned char tests_uc[]    = { 0x00u, 0x01u, 0x0fu, 0x33u, 0x11u, 0x4cu, 0x40u };

static const unsigned char res_mirror[]  = { 0x00u, 0x80u, 0xf0u, 0xccu, 0x88u, 0x32u, 0x02u };
static const unsigned char res_swap_35[] = { 0x00u, 0x01u, 0x1bu, 0x27u, 0x05u, 0x58u, 0x40u };
static const int           res_26_or[]   = { 0    , 0    , 1    , 1    , 0    , 0    , 0     };
static const int           res_26_and[]  = { 0    , 0    , 0    , 1    , 0    , 0    , 0     };

static const unsigned int tests_ui[]     = {
                                                0x00000103u, /* TRUE for three bits */
                                                0x0aa00550u,
                                                0xf0003303u,
                                                0x000000fbu,
                                                0x00400000u,
                                                0x0ff0ff01u,
                                                0x00000033u,
                                                0x00000000u,
                                                0x00008000u
                                           };
static const unsigned char res_count[]   = {0x03u, 0x08u, 0x0au, 0x07u,0x01u ,0x11u, 0x04u, 0x00u, 0x01u};

static const unsigned int res_inc[]      = {

                                                0x00000104u,
                                                0x0aa00551u,
                                                0xf0003304u,
                                                0x000000fcu,
                                                0x00400001u,
                                                0x0ff0ff02u,
                                                0x00000034u,
                                                0x00000001u,
                                                0x00008001u
                                           };
static const unsigned int res_16[]       = {
                                                0x00000100u,
                                                0x0aa00550u,
                                                0xf0003300u,
                                                0x000000f0u,
                                                0x00400000u,
                                                0x0ff0ff00u,
                                                0x00000030u,
                                                0x00000000u,
                                                0x00008000u
                                           };
static const int res_is_exp[] = { 0, 0, 0, 0, 1, 0, 0, 0, 1 };

int main(void)
{
    TestCountSetBits();
    TestCountSetBitsLoop();
    TestFloorToSixTeen();
    TestAreBitsTwoAndSixSet();
    TestAreBitsTwoOrSixSet();
    TestByteMirror();
    TestByteMirrorAlternate();
    TestByteMirrorLoop();
    TestSwapBitThreeWithFive();
    TestIsExactExpOf2();
    TestIsExactExpOf2Loop();
    TestBitwiseIncrement();
    TestXorSwap();
    TestArithmeticSwap();
    TestPow2();
    printf("PrintFloat says - \n");
    TestPrintFloat();
    printf("ThreeBits says - \n");
    AreExactly3BitsSet(tests_ui, 9);

    return 0;
}

/* definitions */
static void TestIsExactExpOf2Loop(void)
{
    int test = 0;
    size_t i = 0;

    for (i = 0; i < ARR_LEN(tests_ui); ++i)
    {
        test = IsExactExpOf2Loop(tests_ui[i]);

        if (test != res_is_exp[i])
        {
            printf("IsExactExpOf2Loop failed! input 0x%x, with 0x%x against 0x%x\n"
                    , tests_ui[i], test, res_is_exp[i]);
        }
    }
}

static void TestIsExactExpOf2(void)
{
    int test = 0;
    size_t i = 0;

    for (i = 0; i < ARR_LEN(tests_ui); ++i)
    {
        test = IsExactExpOf2(tests_ui[i]);

        if (test != res_is_exp[i])
        {
            printf("IsExactExpOf2 failed! input 0x%x, with 0x%x against 0x%x\n"
                    , tests_ui[i], test, res_is_exp[i]);
        }
    }
}

static void TestAreBitsTwoAndSixSet(void)
{
    int test = 0;
    size_t i = 0;

    for (i = 0; i < ARR_LEN(tests_uc); ++i)
    {
        test = AreBitsTwoAndSixSet(tests_uc[i]);

        if (test != res_26_and[i])
        {
            printf("AreBitsTwoAndSixSet failed! input 0x%x, with 0x%x against 0x%x\n"
                    , tests_uc[i], test, res_26_and[i]);
        }
    }
}

static void TestAreBitsTwoOrSixSet(void)
{
    int test = 0;
    size_t i = 0;

    for (i = 0; i < ARR_LEN(tests_uc); ++i)
    {
        test = AreBitsTwoOrSixSet(tests_uc[i]);

        if (test != res_26_or[i])
        {
            printf("TwoSixOr AreBitsTwoOrSixSet! input 0x%x, with 0x%x against 0x%x\n"
                    , tests_uc[i], test, res_26_or[i]);
        }
    }
}

static void TestFloorToSixTeen(void)
{
    unsigned int test = 0;
    size_t i = 0;

    for (i = 0; i < ARR_LEN(tests_ui); ++i)
    {
        test = FloorToSixTeen(tests_ui[i]);

        if (test != res_16[i])
        {
            printf("FloorToSixTeen failed! input 0x%x, with 0x%x against 0x%x\n"
                    , tests_ui[i], test, res_16[i]);
        }
    }
}

static void TestCountSetBitsLoop(void)
{
    unsigned int test = 0;
    size_t i = 0;

    for (i = 0; i < ARR_LEN(tests_ui); ++i)
    {
        test = CountSetBitsLoop(tests_ui[i]);

        if (test != res_count[i])
        {
            printf("CountSetBitsLoop failed! input 0x%x, with 0x%x against 0x%x\n"
                    , tests_ui[i], test, res_count[i]);
        }
    }
}

/* the algorithm implemented by the function tested here ISN'T MINE */
/* refer to README */
static void TestCountSetBits(void)
{
    int test = 0;
    size_t i = 0;

    for (i = 0; i < ARR_LEN(tests_ui); ++i)
    {
        test = CountSetBits(tests_ui[i]);

        if (test != res_count[i])
        {
            printf("CountSetBits failed! input 0x%x, with 0x%x against 0x%x\n"
                    , tests_ui[i], test, res_count[i]);
        }
    }
}

static void TestSwapBitThreeWithFive(void)
{
    unsigned char test = 0;
    size_t i = 0;

    for (i = 0; i < ARR_LEN(tests_uc); ++i)
    {
        test = SwapBitThreeWithFive(tests_uc[i]);

        if (test != res_swap_35[i])
        {
            printf("SwapBitThreeWithFive failed! input 0x%x, with 0x%x against 0x%x\n"
                    , tests_uc[i], test, res_swap_35[i]);
        }
    }
}

static void TestByteMirror(void)
{
    unsigned char test = 0;
    size_t i = 0;

    for (i = 0; i < ARR_LEN(tests_uc); ++i)
    {
        test = ByteMirror(tests_uc[i]);

        if (test != res_mirror[i])
        {
            printf("ByteMirror failed! input 0x%x, with 0x%x against 0x%x\n"
                    , tests_uc[i], test, res_mirror[i]);
        }
    }
}

static void TestByteMirrorAlternate(void)
{
    unsigned char test = 0;
    size_t i = 0;

    for (i = 0; i < ARR_LEN(tests_uc); ++i)
    {
        test = ByteMirrorAlternate(tests_uc[i]);

        if (test != res_mirror[i])
        {
            printf("TestByteMirrorAlternate failed! input 0x%x, with 0x%x against 0x%x\n"
                    , tests_uc[i], test, res_mirror[i]);
        }
    }
}

static void TestByteMirrorLoop(void)
{
    unsigned char test = 0;
    size_t i = 0;

    for (i = 0; i < ARR_LEN(tests_uc); ++i)
    {
        test = ByteMirrorLoop(tests_uc[i]);

        if (test != res_mirror[i])
        {
            printf("ByteMirrorLoop failed! input 0x%x, with 0x%x against 0x%x\n"
                    , tests_uc[i], test, res_mirror[i]);
        }
    }
}

static void TestBitwiseIncrement(void)
{
    unsigned int test = 0;
    unsigned int *p_test = &test;
    size_t i = 0;

    for (i = 0; i < ARR_LEN(tests_ui); ++i)
    {
        test = tests_ui[i];
        BitwiseIncrement(p_test);

        if (test != res_inc[i])
        {
            printf("BitwiseIncrement failed! input 0x%x, with 0x%x against 0x%x\n"
                    , tests_ui[i], test, res_inc[i]);
        }
    }
}

static void TestXorSwap(void)
{
    unsigned char  c1  = 0xf0;
    unsigned char  c2  = 0x3b;

    XorSwap(&c1, &c2);

    if (!((0x3b == c1) && (0xf0 == c2)))
    {
        printf("XorSwap failed its only test!!\n");
    }
}

static void TestArithmeticSwap(void)
{
    unsigned char  c1  = 0xf0;
    unsigned char  c2  = 0x3b;

    ArithmeticSwap(&c1, &c2);
    if (!((0x3b == c1) && (0xf0 == c2)))
    {
        printf("ArithmeticSwap failed its only test!!\n");
    }
}

static void TestPrintFloat(void)
{
    size_t i = 0;
    float og_nums[] = { 3.1415926F, -2.71828F, 1.6180339F, 9965555462516.77676F };

    for (i = 0; i < ARR_LEN(og_nums); ++i)
    {
        printf("\n%f\n", og_nums[i]);
        PrintFloat(&og_nums[i]);
    }
}

static void TestPow2(void)
{
    long test = 0l;
    long lib = 0l;
    size_t i = 0;

    for (i = 0; i < ARR_LEN(tests_uc) - 1; ++i)
    {
        test = Pow2((int)tests_uc[i], (int)tests_uc[i+1]/2);
        lib = tests_uc[i] * pow(2, tests_uc[i+1]/2);

        if ((test != lib) && lib <= INT_MAX)
        {
            printf("Pow2 failed! input [%d, %d], with %lu against %lu\n"
                    , tests_uc[i], tests_uc[i+1], test, lib);
        }
    }
}
