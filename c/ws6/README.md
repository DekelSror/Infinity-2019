##ex. 10 - bit count w/o loop - implemented in CountSetBits

**the following link contains the original algorithm -**

[https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel]

where its origins are also being debated.
says it runs in 12 instructions for 32bit types.

here I adopted it to chars in order to simplify it.

example - 17 - 0x11 - 00010001. expected 2

[un = un - (un >> 1 & 0x55u)]

00010001 =
          00010001
        -
        ( 00001000
        & 01010101
        = 00000000 )

no change

[un = (un & 0x33u) + (un >> 2 & 0x33u)]


00010001 =
        ( 00010001
        & 00110011
        = 00010001 )

        +

        ( 00000100
        & 00110011
        = 00000000 )

no change

[return ((((un + (un >> 4)) & 0x0fu) * 0x01u))]

00010001 = 00010001
         + 00000001
         = 00010010

         & 00001111
         = 00000010

         * 00000001 = 2

         **amazing**

 ***
