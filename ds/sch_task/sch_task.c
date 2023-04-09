/*==============================================================================
Op Scheduler - Task
Module
Dekel Sror
Review: Yakov Gorochovsky
OL66
Version 1
==============================================================================*/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */

#include "sch_task.h"

struct sch_task_s
{
    task_op_t task_op;
    size_t interval;
    size_t total_time;
    void *arg;
    ilrd_uid_t task_uid;
};

sch_task_t *TaskCreate(task_op_t func, size_t interval, void *arg)
{
    sch_task_t *new_task = (sch_task_t *)malloc(sizeof(sch_task_t));

    if (NULL == new_task)
    {
        return NULL;
    }

    new_task->task_op = func;
    new_task->interval = interval;
    new_task->total_time = interval;
    new_task->task_uid = UIDGet();
    new_task->arg = arg;

    return new_task;
}

void TaskDelete(sch_task_t *task_to_del)
{
    assert(task_to_del);

    free(task_to_del);
    task_to_del = NULL;
}

int TaskExec(sch_task_t *active_task)
{
    assert(active_task);

    return active_task->task_op(active_task->arg);
}

/* getters */
ilrd_uid_t TaskGetId(sch_task_t *task)
{
    assert(task);

    return task->task_uid;
}

size_t TaskGetInterval(sch_task_t *task)
{
    assert(task);

    return task->interval;
}

size_t TaskGetTime(sch_task_t *task)
{
    assert(task);

    return task->total_time;
}

void TaskTick(sch_task_t *task)
{
    assert(task);

    task->total_time += task->interval;
}
