
/*========================================================================*/
/* WorkSheet 8 exercise 1                                                 */
/* Array with various data types                                          */
/* Dekel Sror */
/* Review - Maor Alankri                                                  */
/*========================================================================*/

#include <stdio.h> /* printf */
#include <stdlib.h>  /* malloc, realloc, free, NULL, size_t */
#include <string.h> /* strlen, strcpy, strcat */
#include <assert.h>

#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))
#define UNUSED(x) (void)(x)

typedef struct  element_t element_t;

struct element_t
{
    void  *data;
    void (*print_func)(element_t *);
    void (*add_func)  (element_t *, int);
    void (*clean_func)(element_t *);
};

/* functions to work with entire array */
static void ArrInit    (void);
static void ArrToStdout(void);
static void ArrAddToAll(void);
static void ArrCleanAll(void);

/* individual struct's print_func, add_func, clean_func for all valid types */
static void IntPrint   (element_t *);
static void FltPrint   (element_t *);
static void StrPrint   (element_t *);
static void IntAdd     (element_t *, int);
static void FltAdd     (element_t *, int);
static void StrAdd     (element_t *, int);
static void NoClean    (element_t *);
static void StrClean   (element_t *);

/* service function */
static char *ParseIntToStr(int);

/* test data */
static const char *test_elems_str[] = { "michelle", "my belle", "tres bien ensemble" };
static const int   test_elems_int[] = { -400002, 6965, 151, 0 };
static const float test_elems_flt[] = { 3.1415E-3, 1.618 };
static const int   test_add         = -777;

/* declare and initialize the struct array */
#define N_ELEMENTS (ARR_LEN(test_elems_flt) + \
                    ARR_LEN(test_elems_int) + \
                    ARR_LEN(test_elems_str))


int main()
{
    static element_t elements[N_ELEMENTS] = { NULL };
    ArrInit();
    ArrToStdout();
    ArrAddToAll();
    ArrToStdout();
    ArrCleanAll();

    return 0;
}

/* Implementations */

/* functions to work with entire array */
static void ArrInit(void)
{
    size_t num_t_int = ARR_LEN(test_elems_int);
    size_t num_t_str = ARR_LEN(test_elems_str);
    size_t num_t_flt = ARR_LEN(test_elems_flt);
    size_t i         = 0;
    size_t count_int = 0;
    size_t count_flt = 0;
    size_t count_str = 0;

    while(i < N_ELEMENTS)
    {
        char *malloc_validator = NULL;

        if (num_t_flt > count_flt)
        {
            *(float*)&(elements[i].data) = test_elems_flt[count_flt];
            elements[i].print_func = FltPrint;
            elements[i].add_func = FltAdd;
            elements[i].clean_func = NoClean;

            ++count_flt;
            ++i;
        }

        if (num_t_int > count_int)
        {
            *(int*)&(elements[i].data) = test_elems_int[count_int];
            elements[i].print_func = IntPrint;
            elements[i].add_func = IntAdd;
            elements[i].clean_func = NoClean;

            ++count_int;
            ++i;
        }

        if (num_t_str > count_str)
        {
            malloc_validator = (char*)malloc(strlen(test_elems_str[count_str]) + 1);

            if(!malloc_validator)
            {
                printf("malloc failed to allocate %lu bytes\n"
                        ,strlen(test_elems_str[count_str]) + 1);
            }

            elements[i].data = (void*)malloc_validator;
            elements[i].data = strcpy((char*)elements[i].data, test_elems_str[count_str]);
            elements[i].print_func = StrPrint;
            elements[i].add_func = StrAdd;
            elements[i].clean_func = StrClean;

            ++count_str;
            ++i;
        }
    }
}

static void ArrToStdout(void)
{
    size_t i = 0;

    for (i = 0; i < N_ELEMENTS; ++i)
    {
        elements[i].print_func(&elements[i]);
    }
    printf("\n\n");
}

static void ArrAddToAll(void)
{
    size_t i = 0;

    for (i = 0; i < N_ELEMENTS; ++i)
    {
        elements[i].add_func(&elements[i], test_add);
    }
}

static void ArrCleanAll(void)
{
    size_t i = 0;

    for (i = 0; i < N_ELEMENTS; ++i)
    {
        elements[i].clean_func(&elements[i]);
    }
}

/* individual struct's print_func, add_func, clean_func for all valid types */
static void IntPrint(element_t *elem)
{
    assert(elem);
    printf("%d\n", *(int*)&elem->data);
}

static void FltPrint(element_t *elem)
{
    assert(elem);
    printf("%f\n", *(float*)&elem->data);
}

static void StrPrint(element_t *elem)
{
    assert(elem);
    printf("%s\n", (char*)elem->data);
}

static void IntAdd(element_t *elem, int to_add)
{
    *(int *) &elem->data += to_add;
}

static void FltAdd(element_t *elem, int to_add)
{
    *(float*) &elem->data += (float)to_add;
}

/* this doesn't handle a minus sign */
static void StrAdd(element_t *elem, int to_add)
{
    char *parsed = ParseIntToStr(to_add);
    char *cpy_parsed = parsed;
    char *realloc_validator = NULL;

    assert(elem);

    realloc_validator = realloc(elem->data ,strlen((char*)elem->data) + strlen(parsed) + 1);

    if(!realloc_validator)
    {
        printf("realloc failed! original buffer returning...\n");
    }

    elem->data = realloc_validator;
    strcat((char*) elem->data, parsed);

    free(cpy_parsed);
}

static void NoClean(element_t *elem)
{
        UNUSED(elem);
}

static void StrClean(element_t *elem)
{
    assert(elem);

    free(elem->data);

}

/* service function */
/* WARNING: allocates memory, up to caller to free returned pointer */
static char *ParseIntToStr(int to_parse)
{
    int val_save = 0;
    size_t chars = 0;
    char *res = NULL;
    int is_nega = 0;

/* check for negative values */
    if (0 > to_parse)
    {
        to_parse *= -1;
        is_nega = 1;
    }

    val_save = to_parse;

/* count digits */
    while (to_parse)
    {
        ++chars;
        to_parse /= 10;
    }

    res = (char*) malloc(chars + 1 + is_nega);

    if (!res)
    {
        printf("could not allocate %lu bytes\n", chars + 1 + is_nega);
        return NULL;
    }
/* terminate string */
    res += chars + is_nega;
    *res = 0;

/* convert to ASCII and write */
    while (val_save)
    {
        --res;
        *res = (val_save % 10) + 48;
        val_save /= 10;
    }

    if (is_nega)
    {
        --res;
        *res = '-';
    }

    return res;
}
