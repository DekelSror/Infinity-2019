#include <stdlib.h> /* size_t, NULL */
#include <stdio.h> /* printf, getc */


/*========================================================================*/
/* WorkSheet 4 exercises 3                                                */
/* LUT of functions                                                       */
/* pointer array implementation                                           */
/* Dekel Sror */
/*========================================================================*/
#define ASCII_A (65)
#define ASCII_T (84)
#define ASCII_ESC (27)
#define TRUE (1)

void NoOp(void);
void Escape(void);
void Apressed(void);
void Tpressed(void);

static void (*fptr[256])(void) = { NULL };

int main(void)
{
    unsigned char input = 0;
    size_t i = 0;
    int status = 0;

    /* initialize ptr array */
    for (i; i < 256; ++i)
    {
        fptr[i] = NoOp;
    }

    fptr[ASCII_A] = Apressed;
    fptr[ASCII_T] = Tpressed;
    fptr[ASCII_ESC] = Escape;

    printf("pointer array implementation\n");

/* turn off input echo to terminal */
/* input flows straight with no need to ENTER */
    status = system("stty -icanon -echo");

    if(status < 0)
    {
        printf("system function failed\n");
    }

    while(TRUE)
    {
        input = (unsigned char)(getc(stdin));
        fptr[input]();
    }

    status = ystem("stty icanon echo");

    if(status < 0)
    {
        printf("system function failed\n");
    }
    
    return 0;
}


void NoOp(void)
{

}

void Escape(void)
{
    system("stty icanon echo");
    exit(EXIT_SUCCESS);
}

void Apressed(void)
{
    printf("A pressed\n");
}

void Tpressed(void)
{
    printf("T pressed\n");
}
