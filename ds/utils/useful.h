

#ifndef LIL_UTILS_
#define  LIL_UTILS_

#define ARR_LEN(x) (sizeof(x) / sizeof(x[0]))
#define UNUSED(x) (void)(x)


#define MIN2(a, b) (((a) < (b)) ? (a) : (b))
#define MAX2(a,b) (((a) >= (b)) ? (a) : (b))
#define ABS(x) (((x) < 0) ? (-x) : (x))








/*
#define DBG(line)
#ifdef NDEBUG
line
#else
#endif
*/
#define RED_BOLD "\033[1;31m"
#define GRN_BOLD "\033[1;32m"
#define PRP_BOLD "\033[1;35m"
#define RESET    "\033[0m"


#endif /* LIL_UTILS_ */
