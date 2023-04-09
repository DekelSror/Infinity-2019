/*==============================================================================
Unique Identifier Interface
Tests
Dekel Sror
Review: Erez Wilderman
Version 1
==============================================================================*/
#include <stdio.h>

#include "ilrd_uid.h"

static void UIDPrint(ilrd_uid_t to_print);

int main(void)
{
    size_t total_pass = 0;

    ilrd_uid_t test = UIDGet();
    ilrd_uid_t test_bad = UIDGetBad();

    ilrd_uid_t test_cmp = UIDGet();
    ilrd_uid_t test_bad_cmp = UIDGetBad();

    total_pass += (UIDIsSame(test, test_bad) == 0);
    total_pass += (UIDIsSame(test, test_cmp) == 0);
    total_pass += (UIDIsSame(test_bad, test_bad_cmp) == 1);

    total_pass += (UIDIsBad(test) == 0);
    total_pass += (UIDIsBad(test_bad) == 1);

    UIDPrint(test);
    UIDPrint(test_cmp);

    printf("total_pass: %lu\n", total_pass);

    return 0;
}

static void UIDPrint(ilrd_uid_t to_print)
{
    printf("\n==========================\n");

    printf("pid: %d\n", to_print.pid);
    printf("counter: %ld\n", to_print.counter);
    printf("tv_sec: %ld\n", to_print.time.tv_sec);
    printf("tv_usec: %ld\n", to_print.time.tv_usec);

    printf("\n==========================\n");
}
