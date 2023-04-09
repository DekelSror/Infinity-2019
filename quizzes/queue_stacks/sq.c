

struct sq_s
{
    istack_t *enq_st;
    istack_t *deq_st;
};


sq_t *SQCreate(size_t num_of_elems)
{
    sq_t *new_sq = malloc(sizeof(sq_t));

    new_sq->enq_st = IntStackCreate(num_of_elems);
    new_sq->deq = IntStackCreate(num_of_elems);

    return new_sq;
}

void SQDestroy(sq_t *q)
{
    IntStackDestroy(q->enq_st);
    IntStackDestroy(q->deq_st);

    free(q);

    q = NULL;
}

void SQEnqueue(sq_t *q, int element)
{
    IntStackPush(q->enq_st, element);
}

void SQDequeue(sq_t *q)
{

    MoveStacks(q);

    IntStackPop(q->deq_st);
}

int SQPeek(sq_t *q)
{
    MoveStacks(q);

    return IntStackPeek(q->deq_st);
}

static void MoveStacks(sq_t *q)
{
    if (0 == InstStackSize(q->deq_st))
    {
        while (0 < InstStackSize(q->enq_st))
        {
            IntStackPush(q->deq_st, IntStackPeek(q->enq_st));
            IntStackPop(q->enq_st);
        }
    }
}
