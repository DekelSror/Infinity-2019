/* get strdup  */
#define _DEFAULT_SOURCE

#include <stdlib.h> /* NULL, size_t, malloc */
#include <stdio.h> /* printf */

/* to test against my functions */
#include <string.h> /* strlen, strcmp,  strncpy, strncat, strdup, strsnp, strtok */
#include <strings.h> /* strcasecmp, strcasecmp, */

#include "ilrd_string.h"

/*==========================================*/
/* WorkSheet 2 exercises 1 - 10             */
/* Implement standard string(s).h functions */
/* tests                                    */
/* Dekel Sror */
/*==========================================*/

#define OVER_CHAR 256
#define ArrLen(x) sizeof(x) / sizeof(x[0])

/*   forward declarations - test functions   */
void TestLen(void);
void TestCmp(void);
void TestCpy(void);
void TestnCpy(void);
void TestCaseCmp(void);
void TestnCaseCmp(void);
void TestDup(void);
void TestChr(void);
void TestCat(void);
void TestnCat(void);
void TestStr(void);
void TestSpn(void);
void TestTok(void);

/* uncomment whichever tests you wish to run */
int main(void)
{
    /*
    TestLen();
    TestCmp();
    TestCpy();
    TestnCpy();
    TestCaseCmp();
    TestnCaseCmp();
    TestDup();
    TestChr();
    TestCat();
    TestStr();
    */
    TestTok();

    return 0;
}

/* implementations - test functions */
void TestLen(void)
{
    size_t i = 0;
    char *tests[] = { "", "abcd", "ab\0cd" };
    for(i = 0; i < ArrLen(tests); ++i)
    {
        size_t me = StrLen(tests[i]);
        size_t them = strlen(tests[i]);
        if(me != them)
        {
            printf("Test-Len failed [%lu] input '%s', with %lu against %lu\n"
                , i, tests[i], me, them);
        }
    }

}

void TestCmp(void)
{
    size_t i = 0;
    char *against = { "abcd" };
    char *tests[] = { "abcd", "", "abc", "x", "acde" };
    int me = OVER_CHAR, them = OVER_CHAR;
    for(i = 0; i < ArrLen(tests); ++i)
    {
        me = StrCmp(against, tests[i]);
        them = strcmp(against, tests[i]);
        if(me != them)
        {
            printf("StrCmp failed [%lu] inputs '%s' '%s' with %d against %d\n"\
                , i, against, tests[i], me, them);
        }
    }
}

void TestCpy(void)
{
    size_t i = 0, j = 0;
    char *sources[] = { "abcd", "a", "" };
    char *me_buffer = NULL, *them_buffer = NULL;
    char *me = NULL, *them = NULL;
    size_t buffs[] = {0, 200, 1, 2};
    for(i = 0; i < ArrLen(sources); ++i)
    {
        for(j = 0; j < ArrLen(buffs); ++j)
        {
            me_buffer = malloc(buffs[j]);
            me = StrCpy(me_buffer, sources[i]);
            them_buffer = malloc(buffs[j]);
            them = strcpy(me_buffer, sources[i]);
            if(StrCmp(me, them))
            {
                printf("StrCpy failed [%lu] input '%s', buffer %lu, with '%s' against '%s'\n"
                    , i*j, sources[i], buffs[j], me, them);
            }
            free(me_buffer);
            free(them_buffer);
        }
    }
}

void TestnCpy(void)
{
    size_t i = 0, j = 0, k = 0;
    char *sources[] = { "abcd", "a", "" };
    char *me_buffer = NULL, *them_buffer = NULL;
    char *me = NULL, *them = NULL;
    size_t ns[] = { 0, 10, 2, 1 };
    size_t buffs[] = {0, 200, 1, 2};
    for(i = 0; i < ArrLen(sources); ++i)
    {
        for(j = 0; j < ArrLen(buffs); ++j)
        {
            for(k = 0; k < ArrLen(ns); ++k)
            {
/* does not work with malloc */
                me_buffer = calloc(buffs[j], 1);
                me = StrnCpy(me_buffer, sources[i], ns[k]);
                them_buffer = calloc(buffs[j], 1);
                them = strncpy(them_buffer, sources[i], ns[k]);
                if(StrCmp(me, them))
                {
                    printf("StrnCpy failed [%lu][%lu][%lu] input ['%s'], n=[%lu], buffer[ %lu], with ['%s'] against ['%s']\n"
                        , i,j,k, sources[i], ns[k], buffs[j], me, them);
                }
                free(me_buffer);
                free(them_buffer);
            }
        }
    }
}

void TestCaseCmp(void)
{
    size_t i = 0, j = 0;
    char *tests1[] = { "abcd", "abcd", "abcd", "abcd" };
    char *tests2[] = { "AbCd", "aBC", "AbcC", "" };
    int me = 0, them = 0;
    for(i = 0; i < ArrLen(tests1); ++i)
    {
        for(j = 0; j < ArrLen(tests1); ++j)
        {
            me = StrCaseCmp(tests1[i], tests2[j]);
            them = strcasecmp(tests1[i], tests2[j]);
            if(me != them)
            {
                printf("StrCaseCmp failed [%lu] inputs '%s' '%s', with %d against %d\n"
                    , i, tests1[i], tests2[j], me, them);
            }
        }
    }
}

void TestnCaseCmp(void)
{
    size_t ns[] = { 0, 1, 2, 3, 400 };
    size_t i = 0, j = 0, k = 0;
    char *tests1[] = { "abcd", "abcd", "abcd", "abcd" };
    char *tests2[] = { "AbCd", "aBCC", "AbcC", "" };
    int me = 0, them = 0;
    for(i = 0; i < ArrLen(tests1); ++i)
    {
        for(j = 0; j < ArrLen(tests1); ++j)
        {
            for(k = 0; k < ArrLen(ns); ++k)
            {
                me = StrnCaseCmp(tests1[i], tests2[j], ns[k]);
                them = strncasecmp(tests1[i], tests2[j], ns[k]);
                if(me != them)
                {
                    printf("StrCaseCmp failed for inputs '%s' '%s', with %d against %d\n"
                        , tests1[i], tests2[j], me, them);
                }
            }
        }
    }
}

void TestDup(void)
{
    size_t i = 0;
    /*TODO: read from a long file and Dup*/
    char *tests[] = { "", "abcdefghijklmnopqrstuvwxyz" , "abcd" };
    char *me = NULL, *them = NULL;
    for(i = 0; i < ArrLen(tests); ++i)
    {
        me = StrDup(tests[i]);
        them = strdup(tests[i]);
        if(StrCmp(me, them))
        {
            printf("StrDup failed [%lu] input '%s', with '%s' against '%s', cmp=%d\n"
                , i, tests[i], me, them, StrCmp(me, them));
        }
        free(me);
        free(them);
    }
}

void TestChr(void)
{
    size_t i = 0;
    char *test = { "abdjfbdhabdj" };
    char *matches = { "djxh" };
    char *me = NULL, *them = NULL;
    for(i = 0; i < ArrLen(matches); ++i)
    {
        me = StrChr(test, matches[i]);
        them = strchr(test, matches[i]);
        if(me != them)
        {
            printf("StrChr failed [%lu] '%s' '%c', '%s', '%s'\n"
                , i, test, matches[i], me, them);
        }
    }
}

void TestCat(void)
{
    size_t i = 0, j = 0;
    char *my_result = NULL, *lib_result = NULL;

    const char *tests[] = { "abcd", "aabfcaed\t", "a.a/.a" };
    const char *cats[] = {"", " :for you and for *ME*", "ef\"OG\""};
    const size_t buffs[] = {5, 32, 13};

    for (i = 0; i < ArrLen(tests); i++)
    {
        for (j = 0; j < ArrLen(cats); j++)
        {

            my_result = (char*)malloc(StrLen(tests[i]) + StrLen(cats[j]) + 1);
            my_result = StrCpy(my_result, tests[i]);
            my_result = StrCat(my_result, cats[j]);

            lib_result = (char*)malloc(strlen(tests[i]) + strlen(cats[j]) + 1);
            lib_result = strcpy(lib_result, tests[i]);
            lib_result = strcat(lib_result, cats[j]);

            if(StrCmp(my_result, lib_result))
                {
                    printf("StrCat failed test[%lu][%lu],\n\
                        input %s, cat %s, buffer %lu, with %s against %s\n\n"
                        , i, j, tests[i], cats[j], buffs[j]
                        , my_result, lib_result);
                }

            free(my_result);
            free(lib_result);
        }
    }
}

/*this test causes seg faults*/
void TestnCat(void)
{
    size_t i = 0, j = 0, k = 0;
    char *my_result = NULL, *lib_result = NULL;

    const char *tests[] = { "abcd", "aabfcaed\t", "a.a/.a" };
    const char *cats[] = {"", " :for you and for *ME*", "ef\"OG\""};
    const size_t lens[] = {0, 1, 5, 50, 13};

    for (i = 0; i < ArrLen(tests); ++i)
    {
        for (j = 0; j < ArrLen(cats); ++j)
        {
            for(k = 0; k < ArrLen(lens); ++k)
            {
                my_result = (char*)malloc(StrLen(tests[i]) + StrLen(cats[j]) + 1);
                my_result = StrCpy(my_result, tests[i]);
                my_result = StrnCat(my_result, cats[j], lens[k]);

                lib_result = (char*)malloc(strlen(tests[i]) + strlen(cats[j]) + 1);
                lib_result = strcpy(lib_result, tests[i]);
                lib_result = strncat(lib_result, cats[j], lens[k]);

                if(StrCmp(my_result, lib_result))
                    {
                        printf("StrCat failed test[%lu][%lu][%lu],\n\
                            input '%s', cat '%s', with '%s' against '%s'\n\n"
                            , i, j, lens[k], tests[i], cats[j]
                            , my_result, lib_result);
                    }
                free(my_result);
                free(lib_result);
            }
        }
    }

}

void TestStr(void)
{
    size_t i = 0;
    char *haystack = { "The quick brown fox jumps over the lazy dog" };
    char *needles[] = {"", "ck b", "over thf", "the", "The"};

    char *me = NULL, *them = NULL;

    for(i = 0; i < ArrLen(needles); ++i)
    {
        me = StrStr(haystack, needles[i]);
        them = strstr(haystack, needles[i]);
        if(me != them)
        {
            printf("StrStr failed [%lu], needle '%s', with '%p' against %p\n"
                , i, needles[i], me, them);
        }
    }

}


void TestTok(void)
{
    size_t i = 0;
    char test_me[] = "titipushitpopispullitfakeittouchitrockitsimtokietit";
    char test_them[] = "titipushitpopispullitfakeittouchitrockitsimtokietit";
    const char *delim = "it";
    char *me = NULL, *them = NULL;


    while(i < 7)
    {
        if(!i)
        {
            me = StrTok(test_me, delim);
            them = strtok(test_them, delim);
        }
        else
        {
            me = StrTok(NULL, delim);
            them = strtok(NULL, delim);
        }
        printf("%s\t%s\n", me, them);
        ++i;
    }

}
