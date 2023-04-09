/*==============================================================================
Op Scheduler
Module
Dekel Sror
Review: Yakov Gorochovsky
OL66
Version 1
==============================================================================*/
#include <stdlib.h> /* malloc, free */
#include <unistd.h> /* sleep */
#include <assert.h> /* assert       */

#include "priority_q.h" /* pq_t, priority_q API */
#include "sch_task.h" /* sch_task_t, Task API */
#include "scheduler.h"

struct sch_s
{
    pq_t *queue;
};

/*
    scheduler event loop.
    valid ways out -
        scheduler ran out of tasks
        a task calls SchStop
*/
ilrd_uid_t SchRun(sch_t *sch)
{
    sch_task_t *current_task = NULL;
    ilrd_uid_t last_task_uid = UIDGetBad();
    size_t runtime = 0;

    while (!SchIsEmpty(sch))
    {
        int task_op_ret = 0;
        int to_sleep = 0;

        current_task = (sch_task_t *)PriorityQPeek(sch->queue);
        PriorityQDequeue(sch->queue);
        last_task_uid = TaskGetId(current_task);

        to_sleep = (TaskGetTime(current_task) - runtime);

        if (0 < to_sleep)
        {
            sleep(to_sleep);
            runtime += to_sleep;
        }

        task_op_ret = TaskExec(current_task);

        if (0 == task_op_ret)
        {
            TaskTick(current_task);
            PriorityQEnqueue(sch->queue, current_task);
        }
        else
        {
            TaskDelete(current_task);
        }
    }

    return last_task_uid;
}

/* sorting function - conforms to is_prior_t from priority_q */
static int SchedulingMethod(const void *data, const void *to_compare)
{
    return ((TaskGetTime((sch_task_t *)data))
            <= TaskGetTime((sch_task_t *)to_compare));
}

ilrd_uid_t SchAdd(sch_t *sch, size_t interval, opt_t operation, void *arg)
{
    sch_task_t *new_task = TaskCreate(operation, interval, arg);

    assert(sch);

    PriorityQEnqueue(sch->queue, new_task);

    return TaskGetId(new_task);
}

/* removal function - conforms to criteria_func_t from priority_q */
static int SchTaskRemove(const void *data, void *arg)
{
    sch_task_t *del_candid = (sch_task_t *)data;
    ilrd_uid_t uid_to_del = *(ilrd_uid_t *)arg;

    if (UIDIsSame(TaskGetId(del_candid), uid_to_del))
    {
        TaskDelete(del_candid);

        return 1;
    }

    return 0;
}

void SchRemove(sch_t *sch, ilrd_uid_t uid)
{
    assert(sch);

    PriorityQErase(sch->queue, SchTaskRemove, &uid);
}

sch_t *SchCreate(void)
{
    sch_t *new_scheduler = (sch_t *)malloc(sizeof(sch_t));

    if (NULL == new_scheduler)
    {
        return NULL;
    }

    new_scheduler->queue = PriorityQCreate(SchedulingMethod);

    return new_scheduler;
}

void SchDestroy(sch_t *sch)
{
    assert(sch);

    SchStop(sch);

    PriorityQDestroy(sch->queue);

    free(sch);

    sch = NULL;
}

void SchStop(sch_t *sch)
{
    assert(sch);

    while (!PriorityQIsEmpty(sch->queue))
    {
        sch_task_t *task = (sch_task_t *)PriorityQPeek(sch->queue);
        PriorityQDequeue(sch->queue);
        TaskDelete(task);
    }
}

size_t SchSize(const sch_t *sch)
{
    assert(sch);

    return PriorityQSize(sch->queue);
}

int SchIsEmpty(const sch_t *sch)
{
    assert(sch);

    return PriorityQIsEmpty(sch->queue);
}
