#include <stdlib.h> /* size_t, NULL */
#include <stdio.h> /* printf, getc */


/*========================================================================*/
/* WorkSheet 4 exercises 2                                                */
/* LUT of functions                                                       */
/* switch case implementations                                            */
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

    printf("switch case implementation\n");

    status = system("stty -icanon -echo");

    if(status < 0)
    {
        printf("system function failed\n");
    }

    while(TRUE)
    {
        input = (unsigned char)getc(stdin);
        switch(input)
        {
            case ASCII_A:
                Apressed();
                break;
            case ASCII_T:
                Tpressed();
                break;
            case ASCII_ESC:
                Escape();
            default:
                NoOp();
                break;
        }
    }
    
    status = system("stty icanon echo");

    if(status < 0)
    {
        printf("system function failed\n");
    }
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
