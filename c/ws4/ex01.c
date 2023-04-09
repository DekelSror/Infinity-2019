#include <stdlib.h> /* size_t, NULL */
#include <stdio.h> /* printf, getc */


/*========================================================================*/
/* WorkSheet 4 exercises 1                                                */
/* LUT of functions                                                       */
/* if / else implementation                                               */
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


int main(void)
{
    unsigned char input = 0;
    int status = 0;

    printf("if / else implementation\n");
    status = system("stty -icanon -echo");
    

    if(status < 0)
    {
        printf("system function failed\n");
    }

    while(TRUE)
    {
        input = (unsigned char)getc(stdin);
        if (ASCII_A == input)
        {
            Apressed();
        }
        else if (ASCII_T == input)
        {
            Tpressed();
        }
        else if (ASCII_ESC == input)
        {
            Escape();
        }
        else
        {
            NoOp();
        }
    }

    status = system("stty icanon echo");

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
    int status = 0;

    status = system("stty icanon echo");

    if(status < 0)
    {
        printf("system function failed\n");
    }

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
