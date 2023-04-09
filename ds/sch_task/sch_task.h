/*==============================================================================
Op Scheduler - Task
Header
Dekel Sror
Review: Yakov Gorochovsky
OL66
Version 1
==============================================================================*/
#ifndef SCH_TASK_H
#define SCH_TASK_H

#include "ilrd_uid.h"

typedef struct sch_task_s sch_task_t;

/* conforms to opt_t of scheduler */
typedef int (*task_op_t)(void *arg);

/* make a new task instance

    func: task op
    interval: milliseconds between calls to op
    arg: anything or NULL;

    return pointer to the new task
*/
sch_task_t *TaskCreate(task_op_t func, size_t interval, void *arg);

/*
    free all memory associated with task_to_del
*/
void TaskDelete(sch_task_t *task_to_del);

/*
    call active_task's op with its arg
*/
int TaskExec(sch_task_t *active_task);

/*
    returns UID of task
*/
ilrd_uid_t TaskGetId(sch_task_t *task);

/*
    returns interval of task
*/
size_t TaskGetInterval(sch_task_t *task);

/*
    returns total time of task
*/
size_t TaskGetTime(sch_task_t *task);

/*
    updates task after execution
*/
void TaskTick(sch_task_t *task);

#endif /* SCH_TASK_H */
