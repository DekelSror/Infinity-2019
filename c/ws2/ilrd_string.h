#ifndef __ILRD_STRING_H
#define  __ILRD_STRING_H
#include <stddef.h> /* size_t */

/*=======================================================*/
/* WorkSheet 2 exercises 1 - 10 						 */
/* Implement standard string(s).h functions 		     */
/* Header                                                */
/* Dekel Sror */
/*=======================================================*/

size_t StrLen(const char*);
int StrCmp(const char*, const char*);
int StrCaseCmp(const char *, const char *);
int StrnCaseCmp(const char *, const char *, size_t);
char *StrCpy(char *, const char *);
char *StrnCpy(char *, const char *, size_t);
char *StrDup(const char *);
char *StrChr(const char *, char);
char *StrCat(char *, const char *);
char *StrnCat(char *, const char *, size_t);
size_t StrSpn(const char *, const char *);
char *StrStr(const char *, const char *);
char *StrTok(char *, const char *);

#endif /* __ILRD_STRING_H */
