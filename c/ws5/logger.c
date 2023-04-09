#include <stdio.h> /* fopen, fclose, fputc, fputs, fgetc */
#include <string.h> /* strcmp, strlen */
#include <stdlib.h>  /* exit, NULL */
#include <assert.h>

/*========================================================================*/
/* WorkSheet 5 exercise                                                   */
/* Logger Application                                                     */
/*                                                                        */
/* Dekel Sror */
/*========================================================================*/


#define ARR_LEN(x) (sizeof(x) / sizeof(x[0]))
/* TODO: random and/or date related temp log file names */
#define TMP_LOG (".temp-log.f547d53a993a4577877c3a6e9cf646c5.logger")
#define NEW_LINE (10)
#define BUF_SIZE (80)

#define UNUSED(x) (void)(x)

/* types */
typedef enum  { OK,
                NO_ARGS,  /* fatal   */
                NO_RM,    /* fatal   */
                NO_OPEN,  /* fatal   */
                NO_CLOSE, /* fatal   */
                NO_READ,  /* fatal   */
                NO_WRITE, /* fatal   */
                NO_ALOC,  /* fatal   */
                NO_INPUT, /* ignored */
                BUF_OVER, /* ignored */
                ERROR,    /* signal  */
                EXIT      /* signal  */
              } opcodes;

/* forward decleration to be able to pass as member in struct definition */
/* which currently doesn't happen */
typedef struct logger_ log_op;

struct logger_
{
    char    *command;
    int     (*IsOpRequested)(const char *, const char *);
    opcodes (*HandleOpRequest)(const char *, const char *);
};

opcodes LogRequestHandler (log_op *, const char *, const char *);
opcodes ValidateInput     (const char *);
opcodes LogErr            (opcodes);

/* comparison functions - for log_op.IsOpRequested */
int IsCommandRequest (const char *, const char *);
int IsPrependRequest (const char *, const char *);
int IsAppendRequest  (const char *, const char *);

/* actions - for log_op.HandleOpRequest */
opcodes LogAppend    (const char *, const char *);
opcodes LogPrepend   (const char *, const char *);
opcodes LogRemoveFile(const char *, const char *);
opcodes LogCount     (const char *, const char *);
opcodes LogExit      (const char *, const char *);

static log_op log_ops[] =
{
    { "-remove\n", IsCommandRequest, LogRemoveFile },
    { "-count\n" , IsCommandRequest, LogCount },
    { "-exit\n"  , IsCommandRequest, LogExit },
    { "<"        , IsPrependRequest, LogPrepend },
    { "Always Last Index!", IsAppendRequest, LogAppend }
};

static char input_buffer[81] = { 0 };


/* main - run the logger with argv[1] as log_file */
int main(int argc, char const *argv[])
{
    const char *log_file = NULL;
    opcodes app_status = OK;

    /* pre-loop check */
    if(argc == 1)
    {
        app_status = LogErr(NO_ARGS);
    }
    log_file = argv[1];
    /* main loop */
    while(app_status != EXIT)
    {
        fgets(input_buffer, BUF_SIZE, stdin); /* failure ("") is ignored */
        app_status = LogRequestHandler(log_ops, log_file, input_buffer);
        /* OK and ERROR continues, EXIT terminates */
    }

    return 0;
}

/* funtions implementation */
/* general */
opcodes ValidateInput(const char *str)
{

    assert(str);

    if(!str || !*str)
    {
        return LogErr(NO_INPUT);
    }

    else if (str[BUF_SIZE])
    {
        return LogErr(BUF_OVER);
    }

    else
    {
        return OK;
    }
}


/* lm => log_machine from main */
opcodes LogRequestHandler(log_op *lm, const char *path, const char *entry)
{
    size_t i = 0;
    opcodes input_status = ValidateInput(entry);
    opcodes request_status = OK;

    assert(path);
    assert(entry);

    if(ERROR == input_status)
    {
        return ERROR;
    }

    for(i = 0; i < ARR_LEN(log_ops); ++i)
    {

        if(lm[i].IsOpRequested(lm[i].command, entry))
        {
            request_status = lm[i].HandleOpRequest(path ,entry);

            request_status = LogErr(request_status);
            if(ERROR == request_status)
            {
                printf("your last action erred the fragile app.\nIt was not proccessed :\\");
                return ERROR;
            }

            if(EXIT == request_status)
            {
                return EXIT;
            }
            break;
        }
    }
    
    return OK;
}

opcodes LogErr(opcodes err)
{
    switch(err)
    {
        case NO_OPEN :
        case NO_ARGS :
        case NO_RM   :
        case NO_WRITE:
        case NO_READ :
        case NO_CLOSE:
        case NO_ALOC :
        case EXIT    :
            return EXIT;

        case OK      :
            return OK;

        case NO_INPUT:
        case BUF_OVER:
        case ERROR   :
        default      :
            return ERROR;
    }
}

/* Warning: a string "-command XXX" will NOT be treated as a command */
int IsCommandRequest(const char *cmd, const char *entry)
{
    assert(cmd);
    assert(entry);

    if(0 == strcmp(cmd, entry))
    {
        return 1;
    }

    return 0;
}

/* checks if the user requests to prepend an entry */
int IsPrependRequest(const char *cmd, const char *entry)
{
    assert(cmd);
    assert(entry);
    UNUSED(cmd);

    return ('<' == entry[0]);
}

int IsAppendRequest(const char *cmd, const char *entry)
{
    assert(cmd);
    assert(entry);
    UNUSED(cmd);

    return 1;
}

/* .act members of log_op */
opcodes LogAppend(const char *path, const char *entry)
{
    FILE *f = NULL; /* common name fp */
    int io_status = 0;

    assert(path);
    assert(entry);

    f = fopen(path, "a");

    if(!f)
    {
        return NO_OPEN;
    }

    io_status = fputs(entry, f);

    if(EOF == io_status)
    {
        return NO_WRITE;
    }

    io_status = fclose(f);

    if(EOF == io_status)
    {
        return NO_CLOSE;
    }

    return OK;
}

opcodes LogExit(const char *path, const char *entry)
{
    UNUSED(path);
    UNUSED(entry);

    printf("terminating...\n");
    return EXIT;
}

opcodes LogCount(const char *path, const char *entry)
{
    FILE *f = NULL;
    unsigned char letter = 0;
    size_t line_count = 0;
    int io_status = 0;

    assert(path);
    UNUSED(entry);

    f = fopen(path, "a+");

    if(!f)
    {
        return NO_OPEN;
    }

    while(!feof(f))
    {
        letter = fgetc(f);

        if(NEW_LINE == letter)
        {
            ++line_count;
        }
    }

    printf("count finished, %lu lines\n", line_count);

    io_status = fclose(f);

    if(-1 == io_status)
    {
        return NO_CLOSE;
    }

    return OK;
}

opcodes LogRemoveFile(const char *path, const char *entry)
{
    int io_status = 0;

    assert(path);
    UNUSED(entry);

    io_status = remove(path);

    if(-1 == io_status)
    {
        return NO_RM;
    }

    return OK;
}

opcodes LogPrepend(const char *path, const char *entry)
{
    FILE *f = NULL;
    FILE *tmp = NULL;
    int io_status = 0;
    opcodes op_code = OK;
    char c_tmp = 0;

    assert(path);
    assert(entry);

    f = fopen(path, "a+");

    if(!f)
    {
        return NO_OPEN;
    }

    op_code = LogAppend(TMP_LOG, entry + 1);

    if(OK != op_code)
    {
        return op_code;
    }

    tmp = fopen(TMP_LOG, "a");

    if(!tmp)
    {
        return NO_OPEN;
    }

    while(1)
    {
        c_tmp = fgetc(f);

        if(feof(f) || c_tmp < 0)
        {
            break;
        }
        fputc(c_tmp, tmp);
    }

    io_status = fclose(f);

    if(!f)
    {
        return NO_CLOSE;
    }

    io_status = fclose(tmp);

    if(!tmp)
    {
        return NO_CLOSE;
    }

    op_code = LogRemoveFile(path, NULL);

    if(OK != op_code)
    {
        return op_code;
    }

    io_status = rename(TMP_LOG, path);

    if(-1 == io_status)
    {
        return NO_READ;
    }

    return OK;
}
