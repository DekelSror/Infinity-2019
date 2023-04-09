#include <assert.h>
#include "ws1.h"


double Pow_10(int exp)
{
    int base = 10;
    double result = 1;

    if(0 == exp)
    {
        return result;
    }

    int uns_exp = exp > 0 ? exp : -exp;

    while(0 != uns_exp)
    {
        if(uns_exp % 2 == 1){
            result *= base;
            uns_exp--;
        }
        else
        {
            uns_exp /= 2;
            result *= Pow_10(uns_exp);
        }
    }
    
    return exp > 0 ? result : 1.0 / result;
}

int main(int argc, char const *argv[]) {
    /*five cases - 0, negative/positive and odd/even */
    assert(Pow_10(6) == 1000000.0 && "failed for 6");
    assert(Pow_10(9) == 1000000000.0 && "failed for 9");
    assert(Pow_10(0) == 1.0 && "failed for 0");
    assert(Pow_10(-7) == 0.0000001 && "failed for -7");
    assert(Pow_10(-2) == 0.01 && "failed for -2");
    return 0;
}
