/*==============================================================================
Op Scheduler
Tests
Dekel Sror
Review: Yakov Gorochovsky
OL66
Version 1
==============================================================================*/
#include <stdio.h> /* printf */
#include "useful.h" /* UNUSED, colors */

#include "scheduler.h"

struct removal_task_s
{
    sch_t *scheduler;
    ilrd_uid_t uid_to_del;
};
struct addition_task_s
{
    sch_t *scheduler;
    opt_t operation;
    size_t interval;
    void *arg;
};

struct dou_count_s
{
    void *count1;
    void *count2;
};

static int StopOp(void *arg);
static int DoublerOp(void *arg);
static int ConditionalOp(void *arg);
static int RunningOp(void *arg);
static int BlackOp(void *arg);

static int RunTimeRemove(void *arg);
static int RunTimeAdd(void *arg);

/*
this is an integration test.
    - running and conditional increment two counters
    - DoublerOp doubles those counters
    - create a scheduler with 6 tasks - running, conditional, stop,
        adder for DoublerOp, remover for RunningOp, and a BlackOp
    - remove the BlackOp before calling SchRun
    - call SchRun

    - expected output to terminal :
                        conditional:1
                        running:1
                        conditional:2
                        RunTimeAdd size before: 4. after: 5.
                        I was added. Doubled your counters, bye-bye
                        conditional:5
                        running:3
                        conditional:6
                        running:4
                        conditional:7
                        conditional:8
                        running:5
                        RunTimeRemove size before: 3.	after: 2
                        conditional:9
                        conditional op out: 9

*/
int main(void)
{
/* task arguments */
    int conditional_counter = 0;
    int running_counter = 0;
    struct dou_count_s double_op_arg = { 0 };
    struct removal_task_s running_remover = { 0 };
    struct addition_task_s doubler_adder = { 0 };

/* tasks */

    ilrd_uid_t task_stop  = { 0 }; /* stops the run */
    ilrd_uid_t task_running = { 0 }; /* unconditional. to be removed at runtime */
    ilrd_uid_t task_conditional = { 0 }; /* stops at a certain count */
    ilrd_uid_t task_doubler_putter = { 0 }; /* puts the DoublerOp in a new task */
    ilrd_uid_t task_running_remover = { 0 }; /* removes task_running */
    ilrd_uid_t task_to_remove = { 0 }; /* to test SchRemove before runtime */

    ilrd_uid_t run_ret = { 0 };

    sch_t *test = SchCreate();

/* add trivial tasks  - conditional, running, stop and BlackOp */
    task_conditional = SchAdd(test, 2, ConditionalOp, &conditional_counter);
    task_running = SchAdd(test, 3, RunningOp, &running_counter);
    task_stop =  SchAdd(test, 20, StopOp, test);
    task_to_remove = SchAdd(test, 2, BlackOp, NULL);

/* define complex arguments - remove, add, double */
    double_op_arg.count1 = &conditional_counter;
    double_op_arg.count2 = &running_counter;

    doubler_adder.scheduler = test;
    doubler_adder.operation = DoublerOp;
    doubler_adder.interval =  4;
    doubler_adder.arg = &double_op_arg;

    running_remover.scheduler = test;
    running_remover.uid_to_del = task_running;

/* add complex tasks */
    task_doubler_putter = SchAdd(test, 5, RunTimeAdd, &doubler_adder);
    task_running_remover = SchAdd(test, 12, RunTimeRemove, &running_remover);

    SchRemove(test, task_to_remove);

    UNUSED(task_conditional);
    UNUSED(task_running);
    UNUSED(task_running_remover);
    UNUSED(task_doubler_putter);

    run_ret = SchRun(test);

    if (!UIDIsSame(run_ret, task_stop))
    {
        printf("last op isn't what it should be!\n");
    }
    if (9 != conditional_counter)
    {
        printf("conditional_counter is: %d shoud be 9\n", conditional_counter);
    }
    if (5 != running_counter)
    {
        printf("running_counter is: %d, should be 5\n", running_counter);
    }

    SchDestroy(test);

    return 0;
}

static int RunTimeRemove(void *arg)
{
    struct removal_task_s r = *(struct removal_task_s *)arg;

    printf("RunTimeRemove size before: %lu.\t",SchSize(r.scheduler));

    SchRemove(r.scheduler, r.uid_to_del);

    printf("after: %lu\n",SchSize(r.scheduler));

    return 1;

}

static int RunTimeAdd(void *arg)
{
    struct addition_task_s a = *(struct addition_task_s *)arg;

    printf("RunTimeAdd size before: %lu. ",SchSize(a.scheduler));

    SchAdd(a.scheduler, a.interval, a.operation, a.arg);

    printf("after: %lu.\n",SchSize(a.scheduler));

    return 1;
}

static int StopOp(void *arg)
{
    printf(PRP_BOLD);
    printf("StopOp says: I am StopOp\n");
    SchStop((sch_t *)arg);
    printf(RESET);

    return 1;
}

static int DoublerOp(void *arg)
{
    struct dou_count_s *doubler = (struct dou_count_s *)arg;

    *(int *)doubler->count1 *= 2;
    *(int *)doubler->count2 *= 2;

    printf("I was added. Doubled your counters, bye-bye\n");

    return 1;
}

static int ConditionalOp(void *arg)
{
    int *num_p = (int *)arg;

    if (*num_p < 9)
    {
        ++*num_p;
        printf("conditional:%d\n", *num_p);
        return 0;
    }

    printf("conditional op out: %d\n", *num_p);

    return 1;
}

static int RunningOp(void *arg)
{
    int *num_p = (int *)arg;

    ++*num_p;
    printf("running:%d\n", *num_p);

    return 0;
}

static int BlackOp(void *arg)
{
    UNUSED(arg);

    printf(RED_BOLD);
    printf("BlackOp says: I should've been removed!\n");
    printf(RESET);

    return 0;
}
