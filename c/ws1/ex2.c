#include <math.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "ws1.h"


int Reverse(int source)
{
    size_t digits = 0;
    int final = 0;
    int src = source >= 0 ? source : -1 * source;
    size_t i = 1, j = 0;
    int *hold = NULL;
    /*get source length*/
    while(pow(10, digits) <= src){
        ++digits;
    }
    if(digits == 0) return 0;

    hold = (int*) malloc(sizeof(int*)*digits);
    
    for(i=0; i<=digits; ++i){
        *(hold + digits - 1 - i) = src % 10;
        src /= 10;
    }
    /* shorten traverse and be rid of prefix zeros */
    while(*(hold + j) == 0) ++j;
    /*i starts at first non zero digit*/
    for(i=0; i < digits - j; ++i){
        final += *(hold + i) * (int)Pow_10(i);
    }
    return source >= 0 ? final : -final;
}

/*cases - 0, trailing zeros, negative values, zeros in between*/
int main(int argc, char const *argv[]) {
    int test_vals[] = { 0, 5050000, -6, -60010, -4009 };
    int test_expected_results[] = { 0, 505 , -6, -1006, -9004 };
    size_t i = 0;
    int test = 0;
    for (i=0; i<5; ++i) {
        test = Reverse(test_vals[i]);
        if(test != test_expected_results[i]){
            printf("failed for input %d with return %d insted of %d\n",\
            test_vals[i], test, test_expected_results[i]);
        }
    }
    return 0;
}
