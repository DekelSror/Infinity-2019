/*==============================================================================
Data Structures - Circular Buffer
Tests
Dekel Sror
Review - Ruben Gershon
RC 1
==============================================================================*/
#include <stdio.h>  /* printf                 */
#include <string.h> /* strlen, memcmp, memset */

#include "circbuff.h"

#define MAX2(a,b) (((a) >= (b)) ? (a) : (b))

#define FAST_PACE        (200lu)
#define SLOW_PACE        (100lu)
#define DATA_BUF_SIZE    (50000lu)
#define CIR_BUF_BUF_SIZE (3)
#define TEST_CHAR         'G'

#define RED_BOLD "\033[1;31m"
#define GRN_BOLD "\033[1;32m"
#define RESET    "\033[0m"

static size_t TestRun (size_t write_pace, size_t read_pace);
static void   ErrPrint(const char *function, size_t index, size_t w_bytes,
                     size_t r_bytes, size_t w_offset, size_t r_offset,
                     size_t free_space);

int main(void)
{
    double wr_success = 0.0;
    double rw_success = 0.0;

    printf("test config:\nFAST_PACE %lu\nSLOW_PACE %lu\nCIR_BUF_BUF_SIZE %d\
            \nDATA_BUF_SIZE %lu\nTEST_CHAR '%c'\n\n"
            ,FAST_PACE, SLOW_PACE, CIR_BUF_BUF_SIZE, DATA_BUF_SIZE, TEST_CHAR);

    wr_success += TestRun(FAST_PACE, SLOW_PACE);
    printf("writing faster: %5.f%% success\n", wr_success);
    rw_success += TestRun(SLOW_PACE, FAST_PACE);
    printf("reading faster: %5.f%% success\n", rw_success);

    printf(GRN_BOLD);
    printf("\n\tTOTAL:\t %5.f%% success\n\n\n", (wr_success + rw_success) / 2);
    printf(RESET);

    return 0;
}

/* this test attempts to fill dest with data from src using test */
static size_t TestRun(size_t write_pace, size_t read_pace)
{
    cir_buf_t *test = CirBufCreate(CIR_BUF_BUF_SIZE);

    char src[DATA_BUF_SIZE] = { 0 };
    char dest[DATA_BUF_SIZE] = { 0 };
    char *src_p = src;
    char *dest_p = dest;

    size_t written_bytes = 0;
    size_t read_bytes = 0;
    size_t quick_op = MAX2(read_pace, write_pace);

    double good_buf = 0.0;
    size_t i = 0;

    memset(src, TEST_CHAR, DATA_BUF_SIZE);
    printf(RED_BOLD);

/* zero-filling dest is crucial for this loop to end */
    while (strlen(dest) < DATA_BUF_SIZE - quick_op)
    {
        written_bytes = CirBufWrite(test, src_p, write_pace);
        read_bytes = CirBufRead(test, dest_p, read_pace);
        src_p += written_bytes;
        dest_p += read_bytes;
/* check for read from empty */
        if ((dest_p - dest) > (src_p - src))
        {
            ErrPrint("read from empty buffer" ,i, read_bytes, written_bytes
                    , (src_p - src), (dest_p - dest), CirBufFreeSpace(test));
        }
        else
        {
            ++good_buf;
        }
/* check for write over full */
        if ((src_p - src) >= (dest_p - dest + CIR_BUF_BUF_SIZE))
        {
            ErrPrint("write to full buffer" ,i, read_bytes, written_bytes
                    , (src_p - src), (dest_p - dest), CirBufFreeSpace(test));
        }
        else
        {
            ++good_buf;
        }
/* check correctness of read / write operations */
        if (0 != memcmp(src, dest, (dest_p - dest)))
        {
            ErrPrint("incorrect read / write (memcmp)" ,i, read_bytes,
                     written_bytes, (src_p - src), (dest_p - dest),
                     CirBufFreeSpace(test));
        }
        else
        {
            ++good_buf;
        }
        ++i;
    }

    printf(RESET);
    CirBufDestroy(test);
/* return precentage of success with respect to three tests per iteration */
    return ((good_buf / ((double)i * 3.0) * 100.0));
}


static void ErrPrint(const char *function, size_t index, size_t w_bytes,
                     size_t r_bytes, size_t w_offset, size_t r_offset,
                     size_t free_space)
{
    printf("failure! %s. test#%lu, read_bytes: %lu,\
            written_bytes: %lu, total_write: %lu, total_read: %lu, \
            free_space %lu\n"
            , function ,index, r_bytes, w_bytes, w_offset, r_offset, free_space);
}
