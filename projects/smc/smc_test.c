/*==============================================================================
State Machine - Calculator
Tests
Dekel Sror
Review - Moti Zamir
RC 1
==============================================================================*/
#include <stdio.h>

#include "useful.h"
#include "smc.h"

int main(void)
{

    double test = Calculate("-10+(-5-(+6*(-5+0)))");

    printf(GRN_BOLD);
    printf("\nmachine has: %f\n", test);

    test = Calculate("-8+6/(4*(3-1))");
    printf("\nmachine has: %f\n", test);

    test = Calculate("-3.0*-3+(1/3)/(3*1.5)");
    printf("\nmachine has: %f\n", test);

    test = Calculate("(6+(5/2*0))");
    printf("\nmachine has: %f\n", test);

    printf(RESET);

    return 0;
}
